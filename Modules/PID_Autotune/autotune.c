#ifndef BCI_AUTOTUNE_C_INCLUDED
#define BCI_AUTOTUNE_C_INCLUDED

#include "autotune.h"

void autotune_Run(tMotor *leftMotors, const int numLeftMotors, tMotor *rightMotors, const int numRightMotors, const tSensors leftQuad, const tSensors rightQuad, const long target)
{
	float kP = 0.1;

  while (true)
  {
    const long leftQuadStart = SensorValue[leftQuad], rightQuadStart = SensorValue[rightQuad];

    pos_PID pid;
    float quadAvg = 0, lastQuadAvg = 0;
    writeDebugStreamLine("kP: %1.1f", kP);
    pos_PID_InitController(&pid, &quadAvg, kP, 0, 0);
    pos_PID_SetTargetPosition(&pid, target);

    //Local maximums and minimums
    const int numExtremesRequired = 10;
    long extremes[numExtremesRequired], times[numExtremesRequired];
    bool lastExtremeWasPeak = false;
    int extremeCounter = 0;

    //Find extremes
    while (extremeCounter < numExtremesRequired)
    {
    	lastQuadAvg = quadAvg;
      quadAvg = ((SensorValue[leftQuad] - leftQuadStart) + (SensorValue[rightQuad] - rightQuadStart)) / 2.0;

      //Power motors
      for (int m = 0; m < numLeftMotors; m++)
      {
        motor[leftMotors[m]] = pos_PID_GetOutput(&pid);
      }

      for (int m = 0; m < numRightMotors; m++)
      {
        motor[rightMotors[m]] = pos_PID_GetOutput(&pid);
      }

      //Check for peak
      if (!lastExtremeWasPeak)
      {
        if (quadAvg >= lastQuadAvg)
        {
          extremes[extremeCounter] = quadAvg;
          times[extremeCounter] = nSysTime;
        }
        else
        {
        	writeDebugStreamLine("found peak");
          extremeCounter++;
          lastExtremeWasPeak = !lastExtremeWasPeak;
        }
      }
      //Check for valley
      else
      {
        if (quadAvg <= lastQuadAvg)
        {
          extremes[extremeCounter] = quadAvg;
          times[extremeCounter] = nSysTime;
        }
        else
        {
        	writeDebugStreamLine("found valley");
          extremeCounter++;
          lastExtremeWasPeak = !lastExtremeWasPeak;
        }
      }

      wait1Msec(15);
    }

    //Stop motors
    for (int m = 0; m < numLeftMotors; m++)
    {
      motor[leftMotors[m]] = 0;
    }

    for (int m = 0; m < numRightMotors; m++)
    {
      motor[rightMotors[m]] = 0;
    }

    bool didPassInspection = true;
    for (int index = 0; index < numExtremesRequired; index++)
    {
	    //Get lowest and highest extremes
	    int lowestExtreme = extremes[0], highestExtreme = extremes[0];
	    int nextLowestExtreme = extremes[0], nextHighestExtreme = extremes[0];
	    for (int i = index; i < numExtremesRequired; i++)
	    {
	      if (extremes[i] > highestExtreme)
	    		highestExtreme = extremes[i];
	    	else if (extremes[i] < highestExtreme && extremes[i] > nextHighestExtreme)
	    		nextHighestExtreme = extremes[i];
	      else if (extremes[i] < lowestExtreme)
	        lowestExtreme = extremes[i];
	      else if (extremes[i] > lowestExtreme && extremes[i] < nextLowestExtreme)
	      	nextLowestExtreme = extremes[i];
	    }

	    if (abs(highestExtreme - nextHighestExtreme) > 50 || abs(lowestExtreme - nextLowestExtreme) > 50)
	    	didPassInspection = false;
	 	}

    //If the extreme extremes are too different, increase kP because we are not
    //oscillating consistently enough
    if (!didPassInspection)
    {
      kP += 0.1;
      writeDebugStreamLine("Reset robot position! Four seconds before next iteration...");
      wait1Msec(4000);
    }
    //Else we found the correct kP
    else
    {
      //Get average oscillation period tU
      float tU = 0;
      for (int i = 0; i < numExtremesRequired - 1; i++)
      {
        tU += times[i+1] - times[i];
      }
      tU /= numExtremesRequired - 1;

      writeDebugStreamLine("Ultimate gain Ku: %1.1f", kP);
      writeDebugStreamLine("Oscillation period Tu: %1.3f", tU);
      writeDebugStreamLine("kP: %1.3f, kI: %1.3f, kD: %1.3f", 0.33 * kP, tU / 2, tU / 3);
      return;
    }
  }
}

#endif //BCI_AUTOTUNE_C_INCLUDED
