#ifndef VELOCITYTBH_H_INCLUDED
#define VELOCITYTBH_H_INCLUDED

//A velocity TBH controller
typedef struct vel_TBH_t
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
	float outValAtZero;
	float outValChange;

	//Timestep
	float dt;
	int currentTime;
	int prevTime;

	//Input
	tSensors sensor;
	tMotor imeMotor;
	float *var;
	bool usingIME;
	bool usingVar;
	float ticksPerRev;
	float targetVelocity;

	//Filtering
	DEMAFilter filter;
	float alpha;
	float beta;

	//Output
	float outVal;
} vel_TBH;

//Initializes a velocity TBH controller
void vel_TBH_InitController(vel_TBH *tbh, const tSensors sensor, const float gain, const int outValApprox, const int targetVelocity = 0.0, const float ticksPerRev = UTIL_QUAD_TPR);
void vel_TBH_InitController(vel_TBH *tbh, const tMotor imeMotor, const float gain, const int outValApprox, const int targetVelocity = 0.0, const float ticksPerRev = UTIL_IME_HT_TPR);
void vel_TBH_InitController(vel_TBH *tbh, const float *var, const float gain, const int outValApprox, const int targetVelocity = 0.0, const float ticksPerRev = UTIL_QUAD_TPR);

//Reinitializes a velocity TBH controller with previous sensor, gain, open-loop approx, and filter
void vel_TBH_ReInitController(vel_TBH *tbh);

//Sets new filter constants
void vel_TBH_SetFilterConstants(vel_TBH *tbh, const float alpha, const float beta);

//Sets the target velocity
//This should (generally) be used when the target velocity has changed
void vel_TBH_SetTargetVelocity(vel_TBH *tbh, const int targetVelocity, const int outValApprox = -1010);

//Gets the current error
int vel_TBH_GetError(vel_TBH *tbh);

//Gets the current (filtered) velocity
int vel_TBH_GetVelocity(vel_TBH *tbh);

//Gets the current target velocity
int vel_TBH_GetTargetVelocity(vel_TBH *tbh);

//Gets the current output
int vel_TBH_GetOutput(vel_TBH *tbh);

//Sets the open-loop approximation
void vel_TBH_SetOpenLoopApprox(vel_TBH *tbh, const int outValApprox);

//Gets the current open-loop approximation
int vel_TBH_GetOpenLoopApprox(vel_TBH *tbh);

//Steps the controller's velocity calculation (separate from the main step function)
//Can be used to maintain velocity calculation when a full on math step isn't wanted
int vel_TBH_StepVelocity(vel_TBH *tbh);

//Steps the controller calculations
int vel_TBH_StepController(vel_TBH *tbh);

#endif //VELOCITYTBH_H_INCLUDED
