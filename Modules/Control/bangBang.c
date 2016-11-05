#ifndef BCI_BANGBANG_C_INCLUDED
#define BCI_BANGBANG_C_INCLUDED

#include "bangBang.h"

/*
* Initializes a bangbang controller with a sensor
*/
void bangBang_InitController(bangBang *bb, const tSensors sensor, const int highPower, const int lowPower, int targetVelocity, float ticksPerRev)
{
	bb->highPower = highPower;
	bb->lowPower = lowPower;

	bb->currentVelocity = 0.0;
	bb->currentPosition = 0;
	bb->prevPosition = 0;
	bb->error = 0;

	bb->dt = 0.0;
	bb->currentTime = 0;
	bb->prevTime = 0;

	bb->sensor = sensor;
	bb->usingIME = false;
	bb->usingVar = false;
	bb->ticksPerRev = ticksPerRev;
	bb->targetVelocity = targetVelocity;

	filter_Init_DEMA(&bb->filter, 0.19, 0.0526);

	bb->outVal = 0;
}

/*
* Initializes a bangbang controller with an IME
*/
void bangBang_InitController(bangBang *bb, const tMotor imeMotor, const int highPower, const int lowPower, int targetVelocity, float ticksPerRev)
{
	bb->highPower = highPower;
	bb->lowPower = lowPower;

	bb->currentVelocity = 0.0;
	bb->currentPosition = 0;
	bb->prevPosition = 0;
	bb->error = 0;

	bb->dt = 0.0;
	bb->currentTime = 0;
	bb->prevTime = 0;

	bb->imeMotor = imeMotor;
	bb->usingIME = true;
	bb->usingVar = false;
	bb->ticksPerRev = ticksPerRev;
	bb->targetVelocity = targetVelocity;

	filter_Init_DEMA(&bb->filter, 0.19, 0.0526);

	bb->outVal = 0;
}

/*
* Initializes a bangbang controller with a float reference
*/
void bangBang_InitController(bangBang *bb, const float *var, const int highPower, const int lowPower, int targetVelocity, float ticksPerRev)
{
	bb->highPower = highPower;
	bb->lowPower = lowPower;

	bb->currentVelocity = 0.0;
	bb->currentPosition = 0;
	bb->prevPosition = 0;
	bb->error = 0;

	bb->dt = 0.0;
	bb->currentTime = 0;
	bb->prevTime = 0;

	bb->var = var;
	bb->usingIME = false;
	bb->usingVar = true;
	bb->ticksPerRev = ticksPerRev;
	bb->targetVelocity = targetVelocity;

	filter_Init_DEMA(&bb->filter, 0.19, 0.0526);

	bb->outVal = 0;
}

/*
* Sets new filter constants
*/
void bangBang_SetFilterConstants(bangBang *bb, const float alpha, const float beta)
{
	bb->alpha = alpha;
	bb->beta = beta;
}

/*
* Sets the target velocity
*/
void bangBang_SetTargetVelocity(bangBang *bb, const int targetVelocity)
{
	bb->targetVelocity = targetVelocity;
}

/*
* Gets the current error
*/
int bangBang_GetError(const bangBang *bb)
{
	return bb->error;
}

/*
* Gets the current (filtered) velocity
*/
int bangBang_GetVelocity(const bangBang *bb)
{
	return (int)bb->currentVelocity;
}

/*
* Gets the current target velocity
*/
int bangBang_GetTargetVelocity(const bangBang *bb)
{
	return bb->targetVelocity;
}

/*
* Gets the current output
*/
int bangBang_GetOutput(const bangBang *bb)
{
	return bb->outVal;
}

/*
* Steps the controller's velocity calculation (separate from the main step function)
* Can be used to maintain velocity calculation when a full on math step isn't wanted
*/
int bangBang_StepVelocity(bangBang *bb)
{
	if (bb->usingIME)
	{
		//Calculate timestep
		getEncoderAndTimeStamp(bb->imeMotor, bb->currentPosition, bb->currentTime);
		bb->dt = bb->currentTime - bb->prevTime;
		bb->prevTime = bb->currentTime;

		//Scrap dt if zero
		if (bb->dt == 0)
		{
			return 0;
		}

		//Calculate current velcoity
		bb->currentVelocity = (1000.0 / bb->dt) * (bb->currentPosition - bb->prevPosition) * 60.0 / bb->ticksPerRev;
		bb->prevPosition = bb->currentPosition;
	}
	else if (bb->usingVar)
	{
		//Calculate timestep
		bb->dt = nSysTime - bb->prevTime;
		bb->prevTime = nSysTime;

		//Scrap dt if zero
		if (bb->dt == 0)
		{
			return 0;
		}

		//Calculate current velocity
		bb->currentVelocity = (1000.0 / bb->dt) * (*(bb->var) - bb->prevPosition) * 60.0 / bb->ticksPerRev;
		bb->prevPosition = *(bb->var);
	}
	else
	{
		//Calculate timestep
		bb->dt = nSysTime - bb->prevTime;
		bb->prevTime = nSysTime;

		//Scrap dt if zero
		if (bb->dt == 0)
		{
			return 0;
		}

		//Calculate current velocity
		bb->currentVelocity = (1000.0 / bb->dt) * (SensorValue[bb->sensor] - bb->prevPosition) * 60.0 / bb->ticksPerRev;
		bb->prevPosition = SensorValue[bb->sensor];
	}

	//Use a DEMA filter to smooth data
	bb->currentVelocity = filter_DEMA(&(bb->filter), bb->currentVelocity, 0.19, 0.0526);

	return bb->currentVelocity;
}

/*
* Steps the controller calculations
*/
int bangBang_StepController(bangBang *bb)
{
	//Calculate current velocity
	bangBang_StepVelocity(bb);

	//Calculate error
	bb->error = bb->targetVelocity - bb->currentVelocity;

	//Calculate new outVal
	//bb->outVal = bb->error < 0 ? bb->highPower : bb->lowPower;

	if (bb->currentVelocity > bb->targetVelocity)
	{
		bb->outVal = bb->lowPower;
	}
	else if (bb->currentVelocity <= bb->targetVelocity)
	{
		bb->outVal = bb->highPower;
	}

	//Return outVal
	return bb->outVal;
}

#endif //BCI_BANGBANG_C_INCLUDED
