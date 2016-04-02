#ifndef BANGBANG_C_INCLUDED
#define BANGBANG_C_INCLUDED

#include "bangBang.h"

void bangBang_InitController(bangBang *bb, const tSensors sensor, const int highPower, const int lowPower, const int targetVelocity)
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
	bb->targetVelocity = targetVelocity;

	filter_Init_DEMA(&bb->filter);

	bb->outVal = 0.0;
}

void bangBang_InitController(bangBang *bb, const tMotor motor, const int highPower, const int lowPower, const int targetVelocity)
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
	bb->targetVelocity = targetVelocity;

	filter_Init_DEMA(&bb->filter);

	bb->outVal = 0.0;
}

void bangBang_SetTargetVelocity(bangBang *bb, const int targetVelocity)
{
	bb->targetVelocity = targetVelocity;
}

int bangBang_GetError(bangBang *bb)
{
	return bb->error;
}

int bangBang_GetVelocity(bangBang *bb)
{
	return (int)bb->currentVelocity;
}

int bangBang_GetTargetVelocity(bangBang *bb)
{
	return bb->targetVelocity;
}

int bangBang_GetOutput(bangBang *bb)
{
	return bb->outVal;
}

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
		bb->currentVelocity = (1000.0 / bb->dt) * (bb->currentPosition - bb->prevPosition) * 60.0 / 627.2; //627.2 IME ticks per 393 torque config revolution
		bb->prevPosition = bb->currentPosition;
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
		bb->currentVelocity = (1000.0 / bb->dt) * (SensorValue[bb->sensor] - bb->prevPosition) * 60.0 / 360; //360 quad encoder ticks per revolution
		bb->prevPosition = SensorValue[bb->sensor];
	}

	//Use a EMA filter to smooth data
	bb->currentVelocity = filter_DEMA(&(bb->filter), bb->currentVelocity, 0.19, 0.0526);

	return bb->currentVelocity;
}

int bangBang_StepController(bangBang *bb)
{
	//Calculate current velocity
	bangBang_StepVelocity(bb);

	//Calculate error
	bb->error = bb->targetVelocity - bb->currentVelocity;

	//Calculate new outVal
	bb->outVal = bb->error > 0 ? 127 : 60;

	//Return outVal
	return bb->outVal;
}

#endif //BANGBANG_C_INCLUDED
