#ifndef AUTOTUNE_C_INCLUDED
#define AUTOTUNE_C_INCLUDED

#include "..\Core\positionPID.c"

static autotune_pos_PID *apid_s;
static bool plantFinishedRunning = false;

void autotune_Init(autotune_pos_PID *apid, const tSensors sensor)
{
  pos_PID_InitController(&(apid->pid), sensor, 1, 0, 0);
  apid->sensor = sensor;
  apid->didOvershootLastCorrection = false;
  apid->adjustmentAmount = 0.1;
  apid->pAdjustment = 0;
  apid->pAdjustment_prev = 0;
  apid->iAdjustment = 0;
  apid->dAdjustment = 0;
  apid->iterationCount = 0;
}

void autotune_StepRoutine(autotune_pos_PID *apid)
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
    startTask(monitorPlant);

    //Run plant using wrapper
    plantFinishedRunning = false;
    startTask(runPlantWrapper);
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

        //Decrease kP
        apid_s->pAdjustment -= adjustmentAmount;
      }

      continue;
    }

    //Stop plant if overshot
    if (sgn(apid_s->pid.error) != sgn(apid_s->pid.prevError))
    {
      stopTask(runPlantWrapper);

      //Decrease kP
      apid_s->pAdjustment -= adjustmentAmount;

      continue;
    }

    //Adjust kP based on final error and exit
    if (plantFinishedRunning)
    {
      //Half adjustment resolution if overshot last iteration
      if (apid_s->didOvershootLastCorrection)
      {
        apid_S->adjustmentAmount /= 2.0;
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
      apid_s->pAdjustment += adjustmentAmount * sgn(apid_s->pid.error);

      break;
    }
  }
}

task runPlantWrapper()
{
  runPlant();
  plantFinishedRunning = true;
  while (true) { EndTimeSlice(); }
}

#endif //AUTOTUNE_C_INCLUDED
