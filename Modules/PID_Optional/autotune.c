#ifndef AUTOTUNE_C_INCLUDED
#define AUTOTUNE_C_INCLUDED

#include "autotune.h"
#include "..\Core\motorControl.c"

static autotune_pos_PID *apid_s;
static bool monitorPlantFinishedRunning = false;
static bool plantFinishedRunning = false;

void autotune_Init(autotune_pos_PID *apid, const tSensors sensor, const float kP_Initial, const float kI_Initial, const float kD_Initial)
{
  pos_PID_InitController(&(apid->pid), sensor, kP_Initial, kI_Initial, kD_Initial);
  apid->sensor = sensor;
  apid->didOvershootLastCorrection = false;
  apid->adjustmentAmount = 0.1;
  apid->decimalPlaces = 1;
  apid->pAdjustment = 0;
  apid->pAdjustment_prev = 0;
  apid->iAdjustment = 0;
  apid->dAdjustment = 0;
  apid->iterationCount = 0;
}

void autotune_Run(autotune_pos_PID *apid)
{
  while (true)
  {
    //Initialize controller with new parameters
    pos_PID_InitController(&(apid->pid), apid->sensor, apid->pid.kP + apid->pAdjustment, apid->pid.kI + apid->iAdjustment, apid->pid.kD + apid->dAdjustment);

    //Print out new parameters
    apid->iterationCount++;
    writeDebugStreamLine("#%d- kP: %1.2f, kI: %1.2f, kD: %1.2f", apid->iterationCount, apid->pid.kP, apid->pid.kI, apid->pid.kD);

    //Start monitor task
    apid_s = apid;
    monitorPlantFinishedRunning = false;
    startTask(monitorPlant);

    //Run plant using wrapper
    plantFinishedRunning = false;
    startTask(runPlantWrapper);

    //Wait until monitor has stopped
    while (!monitorPlantFinishedRunning) { EndTimeSlice(); }

    //Let things settle
    wait1Msec(10000);
    stopAllMotorsRaw();
  }
}

task monitorPlant()
{
  //The maximum number of times error can increase in a row before the plant is stopped
  const int errorIncreasedCountMax = 5;

  //The current number of times error has increased in a row
  int errorIncreasedCount = 0;

  //Flag if error increased last loop
  bool errorDidIncreaseLastLoop = false;

  while (true)
  {
    //Stop plant if error increases too many times in a row
    if (apid_s->pid.error > apid_s->pid.prevError)
    {
      //Increase counter if this error increase is contiguous
      if (errorDidIncreaseLastLoop)
      {
        errorIncreasedCount++;
      }

      //Error has increased this loop, set flag
      errorDidIncreaseLastLoop = true;

      //Stop plant if error has increased too many times in a row
      if (errorIncreasedCount >= errorIncreasedCountMax)
      {
        stopTask(runPlantWrapper);
        stopAllMotorsRaw();

        //Decrease kP
        apid_s->pAdjustment = -1 * apid_s->adjustmentAmount;

        writeDebugStreamLine("monitorPlant exited: error increased too many times in a row");
        plantFinishedRunning = true;

        break;
      }
    }
    //Clear count if series is not contiguous
    else
    {
      errorIncreasedCount = 0;
      errorDidIncreaseLastLoop = false;
    }

    //Stop plant if overshot
    if (sgn(apid_s->pid.error) != sgn(apid_s->pid.prevError))
    {
      stopTask(runPlantWrapper);
      stopAllMotorsRaw();

      //Set flag
      apid_s->didOvershootLastCorrection = true;

      //Decrease kP
      apid_s->pAdjustment = -1 * apid_s->adjustmentAmount;

      writeDebugStreamLine("monitorPlant exited: plant overshot");
      plantFinishedRunning = true;

      break;
    }

    //Adjust kP based on final error and exit
    if (plantFinishedRunning)
    {
      //Half adjustment resolution if overshot last iteration and undershot this time
      if (apid_s->didOvershootLastCorrection && apid_s->pid.error > 0)
      {
        apid_s->adjustmentAmount /= 10.0;
        apid_s->decimalPlaces++;

        //Only adjust to three decimal places
        if (apid_s->decimalPlaces > 3)
        {
          break;
        }
      }

      //If overshot this iteration, set flag
      if (apid_s->pid.error < 0)
      {
        apid_s->didOvershootLastCorrection = true;
      }
      //Otherwise, clear flag
      else
      {
        apid_s->didOvershootLastCorrection = false;
      }

      //Adjust kP based on current residual error
      apid_s->pAdjustment = apid_s->adjustmentAmount * sgn(apid_s->pid.error);

      writeDebugStreamLine("monitorPlant exited: plant finished");
      monitorPlantFinishedRunning = true;
      break;
    }
  }
}

task runPlantWrapper()
{
  runPlant();
  stopAllMotorsRaw();
  writeDebugStreamLine("plant stopped");
  plantFinishedRunning = true;
}

#endif //AUTOTUNE_C_INCLUDED
