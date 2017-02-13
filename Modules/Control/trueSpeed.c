#ifndef BCI_TRUESPEED_C_INCLUDED
#define BCI_TRUESPEED_C_INCLUDED

#include "trueSpeed.h"

#ifdef BCI_USE_CUSTOM_TRUESPEED
  float rpmForward[128], rpmBackward[128];
  float powerForward[128], powerBackward[128];
  void trueSpeed_Measure(tMotor *leftMotors, const int leftLen, tMotor *rightMotors, const int rightLen, tSensors leftQuad, tSensors rightQuad)
  {
    DEMAFilter df;
    filter_Init_DEMA(&df, 0.19, 0.0526);

    long dt = 15, prevTime = nSysTime;

    const long leftQuadStart = SensorValue[leftQuad],
               rightQuadStart = SensorValue[rightQuad];
    float avgQuads = 0, prevAvgQuads = 0;

    while (true)
    {
      for (int i = 0; i < 128; i++)
      {
        //Power motors
        for (int m = 0; m < leftLen; m++)
        {
          leftMotors[m] = i;
        }

        for (int m = 0; m < rightLen; m++)
        {
          rightMotors[m] = i;
        }

        //Wait for rpm to increase
        wait1Msec(23);

        dt = (nSysTime - prevTime) / 1000.0;
        prevTime = nSysTime;

        if (dt == 0)
        {
          continue;
        }

        //Filter rpm
        avgQuads = ((SensorValue[leftQuad] - leftQuadStart) + (SensorValue[rightQuad] - rightQuadStart)) / 2.0;
        rpmForward[i] = filter_DEMA(&df, dt * (avgQuads - prevAvgQuads) * 60.0 / UTIL_QUAD_TPR);
        prevAvgQuads = avgQuads;
      }
    }
  }
#endif //BCI_USE_CUSTOM_TRUESPEED
#endif //BCI_TRUESPEED_C_INCLUDED
