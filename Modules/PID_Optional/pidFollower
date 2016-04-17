#ifndef PIDFOLLOWER_H_INCLUDED
#define PIDFOLLOWER_H_INCLUDED

#include "..\positionPID.c"

pos_PID_Follower_t
{
  //Follower pos_PID controller
  pos_PID pid;

  //Input
  float *var;

  //Output
  int outVal;
} pos_PID_Follower;

void pos_PID_Follower_InitController(pos_PID_Follower *ppf, const float *var, const float kP, const float kI, const float kD, const float kBias = 0.0, const int errorThreshold = 0, const int integralLimit = 1000000);

//Sets the target position


#endif //PIDFOLLOWER_H_INCLUDED
