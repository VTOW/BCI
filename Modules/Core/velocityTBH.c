#ifndef VELOCITYTBH_C_INCLUDED
#define VELOCITYTBH_C_INCLUDED

#include "velocityTBH.h"

void vel_TBH_InitController(vel_TBH *tbh, const tSensors sensor, const float gain, const int outValApprox)
{
	tbh->gain = gain;

	tbh->currentVelocity = 0.0;
	tbh->currentPosition = 0;
	tbh->prevPosition = 0;
	tbh->error = 0;
	tbh->prevError = 0;
	tbh->firstCross = true;
	tbh->outValApprox = outValApprox;
	tbh->outValAtZero = 0.0;

	tbh->dt = 0.0;
	tbh->currentTime = 0;
	tbh->prevTime = 0;

	tbh->sensor = sensor;
	tbh->usingIME = false;
	tbh->targetVelocity = 0.0;

	filter_Init_EMA(&tbh->filter);

	tbh->outVal = 0.0;
}

void vel_TBH_InitController(vel_TBH *tbh, const tMotor imeMotor, const float gain, const int outValApprox)
{
	tbh->gain = gain;

	tbh->currentVelocity = 0.0;
	tbh->currentPosition = 0;
	tbh->prevPosition = 0;
	tbh->error = 0;
	tbh->prevError = 0;
	tbh->firstCross = true;
	tbh->outValApprox = outValApprox;
	tbh->outValAtZero = 0.0;

	tbh->dt = 0.0;
	tbh->currentTime = 0;
	tbh->prevTime = 0;

	tbh->imeMotor = imeMotor;
	tbh->usingIME = true;
	tbh->targetVelocity = 0.0;

	filter_Init_EMA(&tbh->filter);

	tbh->outVal = 0.0;
}

void vel_TBH_ReInitController(vel_TBH *tbh)
{
	tbh->currentVelocity = 0.0;
	tbh->currentPosition = 0;
	tbh->prevPosition = 0;
	tbh->error = 0;
	tbh->prevError = 0;
	tbh->firstCross = true;
	tbh->outValAtZero = 0.0;

	tbh->dt = 0.0;
	tbh->currentTime = 0;
	tbh->prevTime = 0;

	tbh->targetVelocity = 0.0;

	tbh->outVal = 0.0;
}

void vel_TBH_SetTargetVelocity(vel_TBH *tbh, const int targetVelocity, const int outValApprox)
{
	tbh->targetVelocity = targetVelocity;
	tbh->firstCross = true;

	//Set outValApprox if it is not the default value
	if (outValApprox != -1010)
	{
		tbh->outValApprox = outValApprox;
	}
}

int vel_TBH_GetError(vel_TBH *tbh)
{
	return tbh->error;
}

int vel_TBH_GetVelocity(vel_TBH *tbh)
{
	return (int)tbh->currentVelocity;
}

int vel_TBH_GetTargetVelocity(vel_TBH *tbh)
{
	return tbh->targetVelocity;
}

int vel_TBH_GetOutput(vel_TBH *tbh)
{
	return tbh->outVal;
}

void vel_TBH_SetOpenLoopApprox(vel_TBH *tbh, const int outValApprox)
{
	tbh->outValApprox = outValApprox;
}

int vel_TBH_GetOpenLoopApprox(vel_TBH *tbh)
{
	return tbh->outValApprox;
}

int vel_TBH_StepVelocity(vel_TBH *tbh)
{
	if (tbh->usingIME)
	{
		//Calculate timestep
		getEncoderAndTimeStamp(tbh->imeMotor, tbh->currentPosition, tbh->currentTime);
		tbh->dt = tbh->currentTime - tbh->prevTime;
		tbh->prevTime = tbh->currentTime;

		//Scrap dt if zero
		if (tbh->dt == 0)
		{
			return 0;
		}

		//Calculate current velcoity
		tbh->currentVelocity = (1000.0 / tbh->dt) * (tbh->currentPosition - tbh->prevPosition) * 60.0 / 627.2; //627.2 IME ticks per 393 torque config revolution
		tbh->prevPosition = tbh->currentPosition;
	}
	else
	{
		//Calculate timestep
		tbh->dt = nSysTime - tbh->prevTime;
		tbh->prevTime = time1[T1];

		//Scrap dt if zero
		if (tbh->dt == 0)
		{
			return 0;
		}

		//Calculate current velocity
		tbh->currentVelocity = (1000.0 / tbh->dt) * (SensorValue[tbh->sensor] - tbh->prevPosition) * 60.0 / 360; //360 quad encoder ticks per revolution
		tbh->prevPosition = SensorValue[tbh->sensor];
	}

	//Use a EMA filter to smooth data
	tbh->currentVelocity = filter_EMA(&(tbh->filter), tbh->currentVelocity, 0.8);

	return tbh->currentVelocity;
}

int vel_TBH_StepController(vel_TBH *tbh)
{
	//Calculate current velocity
	vel_TBH_StepVelocity(tbh);

	//Calculate error
	tbh->error = tbh->targetVelocity - tbh->currentVelocity;

	//Calculate new outVal
	tbh->outVal = tbh->outVal + (tbh->error * tbh->gain);

	//Bound outVal
	tbh->outVal = tbh->outVal > 127 ? 127 : tbh->outVal;
	tbh->outVal = tbh->outVal < -127 ? -127 : tbh->outVal;

	//Check for zero crossing on error term
	if (sgn(tbh->error) != sgn(tbh->prevError))
	{
		//If first zero crossing since new target velocity
		if (tbh->firstCross)
		{
			//Set drive to an open loop approximation
			tbh->outVal = tbh->outValApprox;
			tbh->firstCross = false;
		}
		else
		{
			//tbh->outVal = 0.5 * (tbh->outVal + tbh->outValAtZero);
			tbh->outVal = 0.4 * (tbh->outVal + tbh->outValAtZero) + 0.2 * tbh->outVal;
		}

		//Save this outVal as the new zero base value
		tbh->outValAtZero = tbh->outVal;
	}

	//Save error
	tbh->prevError = tbh->error;

	return tbh->outVal;
}

#endif //VELOCITYTBH_C_INCLUDED
