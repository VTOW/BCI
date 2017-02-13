#ifndef BCI_AUTOTUNE_C_INCLUDED
#define BCI_AUTOTUNE_C_INCLUDED

#include "autotune.h"

void autotune_Run(tMotor *leftMotors, const int numLeftMotors, tMotor *rightMotors, const int numRightMotors, const tSensors leftQuad, const tSensors rightQuad)
{
  //poke kp until we get consistent oscillations
  //each iteration, save quad data into array
  //read array and determine if we have consistent oscillations
  //once we do, measure time in seconds between oscillations
  //output gains
}

#endif //BCI_AUTOTUNE_C_INCLUDED
