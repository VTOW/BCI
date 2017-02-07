#ifndef BCI_ODOMETRY_C_INCLUDED
#define BCI_ODOMETRY_C_INCLUDED

#include "odometry.h"

void odometry_Initialize(const tSensors leftQuad, const tSensors rightQuad, const long start_x, const long start_y, const long start_theta)
{
  bci_internal_odom.pos_x = start_x;
  bci_internal_odom.pos_y = start_y;
  bci_internal_odom.pos_theta = start_theta;

  bci_internal_odom.leftQuad = leftQuad;
  bci_internal_odom.rightQuad = rightQuad;
}

void odometry_SetScales(const float scale, const float turnScale)
{
  bci_internal_odom.scale = scale;
  bci_internal_odom.turnScale = turnScale;
}

void odometry_GuessScales(const float chassisDiameter, const float wheelDiameter)
{
  bci_internal_odom.scale = wheelDiameter * PI * UTIL_IN_TO_MM; //1 in = 25.4 mm
  bci_internal_odom.turnScale = chassisDiameter / wheelDiameter;
}

task trackOdometry()
{
  SensorValue[bci_internal_odom.leftQuad] = 0;
  SensorValue[bci_internal_odom.rightQuad] = 0;

  long lastLeft, lastRight, leftTicks, rightTicks;

  float leftMM, rightMM, mm;

  int leftSample, rightSample;

  while (true)
  {
    //Save quads
    leftSample = SensorValue[bci_internal_odom.leftQuad];
    rightSample = SensorValue[bci_internal_odom.rightQuad];

    //Get delta
    leftTicks = leftSample - lastLeft;
    rightTicks = rightSample - lastRight;

    //Save last vals
    lastLeft = leftSample;
    lastRight = rightSample;

    //Convert to mm
    leftMM = (float)leftTicks / bci_internal_odom.scale;
    rightMM = (float)rightTicks / bci_internal_odom.scale;

    //Get avg delta
    mm = (leftMM + rightMM) / 2.0;

    //Get theta
    theta += (rightTicks - leftTicks) / bci_internal_odom.turnScale;

    //Wrap theta
    if(theta > 180)
      theta = theta - 360;
    if(theta < -180)
      theta = 360 + theta;

    //Do the odom math
    bci_internal_odom.pos_x += mm * cosDegrees(theta);
    bci_internal_odom.pos_y += mm * sinDegrees(theta);

    //Save to global
    BCI_Odometry_X = bci_internal_odom.pos_x;
    BCI_Odometry_Y = bci_internal_odom.pos_y;
    BCI_Odometry_Theta = bci_internal_odom.pos_theta;

    //Task wait
    wait1Msec(5);
  }
}

#endif //BCI_ODOMETRY_C_INCLUDED
