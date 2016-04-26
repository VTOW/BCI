#ifndef BANGBANG_H_INCLUDED
#define BANGBANG_H_INCLUDED

#include "filter.c"
#include "util.c"

//Bang bang controller type
typedef struct bangBang_t
{
	//Power levels
	int highPower;
	int lowPower;

	//Bangbang calculations
	float currentVelocity;
	int currentPosition;
	int prevPosition;
	int error;

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
	int outVal;
} bangBang;

//Initializes a bangbang controller
void bangBang_InitController(bangBang *bb, const tSensors sensor, const int highPower, const int lowPower, const int targetVelocity = 0, const float ticksPerRev = UTIL_QUAD_TPR);
void bangBang_InitController(bangBang *bb, const tMotor imeMotor, const int highPower, const int lowPower, const int targetVelocity = 0, const float ticksPerRev = UTIL_IME_HT_TPR);
void bangBang_InitController(bangBang *bb, const float *var, const int highPower, const int lowPower, const int targetVelocity = 0, const float ticksPerRev = UTIL_QUAD_TPR);

//Sets new filter constants
void bangBang_SetFilterConstants(bangBang *bb, const float alpha, const float beta);

//Sets the target velocity
void bangBang_SetTargetVelocity(bangBang *bb, const int targetVelocity);

//Gets the current error
int bangBang_GetError(bangBang *bb);

//Gets the current (filtered) velocity
int bangBang_GetVelocity(bangBang *bb);

//Gets the current target velocity
int bangBang_GetTargetVelocity(bangBang *bb);

//Gets the current output
int bangBang_GetOutput(bangBang *bb);

//Steps the controller's velocity calculation (separate from the main step function)
//Can be used to maintain velocity calculation when a full on math step isn't wanted
int bangBang_StepVelocity(bangBang *bb);

//Steps the controller calculations
int bangBang_StepController(bangBang *bb);

#endif //BANGBANG_H_INCLUDED
