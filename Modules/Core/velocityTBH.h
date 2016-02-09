#ifndef VELOCITYTBH_H_INCLUDED
#define VELOCITYTBH_H_INCLUDED

#include "filter.c"

//This scale relates degrees per millisecond to rpm
#define TBH_DEGPMS_TO_RPM 166.7

//A velocity TBH controller
typedef struct vel_TBH
{
	//TBH constants
	float gain;

	//TBH calculations
	float currentVelocity;
	int currentPosition;
	int prevPosition;
	int error;
	int prevError;
	bool firstCross;
	int outValApprox; //Output value at zero error for a given target velocity
	int outValAtZero;

	//Timestep
	float dt;
	int currentTime;
	int prevTime;

	//Input
	tSensors sensor;
	tMotor imeMotor;
	bool usingIME;
	float targetVelocity;

	//Filtering
	EMAFilter filter;

	//Output
	float outVal;
} vel_TBH;

//Initializes a velocity TBH controller
void vel_TBH_InitController(vel_TBH *tbh, const tSensors sensor, const float gain, const int outValApprox);
void vel_TBH_InitController(vel_TBH *tbh, const tMotor imeMotor, const float gain, const int outValApprox);

//Sets the target velocity
void vel_TBH_SetTargetVelocity(vel_TBH *tbh, const int targetVelocity, const int outValApprox = -1010);

//Gets the current error
int vel_TBH_GetError(vel_TBH *tbh);

//Gets the current (filtered) velocity
int vel_TBH_GetVelocity(vel_TBH *tbh);

//Gets the current target velocity
int vel_TBH_GetTargetVelocity(vel_TBH *tbh);

//Gets the current output
int vel_TBH_GetOutput(vel_TBH *tbh);

//Gets the current open-loop approximation
int vel_TBH_GetOpenLoopApprox(vel_TBH *tbh);

//Steps the controller's velocity calculation (separate from the main step function)
//Can be used to maintain velocity calculation when a full on math step isn't wanted
int vel_TBH_StepVelocity(vel_TBH *tbh);

//Steps the controller calculations
int vel_TBH_StepController(vel_TBH *tbh);

#endif //VELOCITYTBH_H_INCLUDED
