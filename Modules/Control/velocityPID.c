#ifndef BCI_VELOCITYPID_C_INCLUDED
#define BCI_VELOCITYPID_C_INCLUDED

#include "velocityPID.h"

void vel_PID_InitController(vel_PID *pid, const tSensors sensor, const float kP, const float kD, float ticksPerRev)
{
	pid->kP = kP;
	pid->kD = kD;

	pid->error = 0;
	pid->currentVelocity = 0.0;
	pid->prevError = 0;
	pid->prevPosition = 0;
	pid->currentTime = 0;
	pid->prevTime = 0;
	pid->dt = 0.0;
	pid->derivative = 0;

	pid->sensor = sensor;
	pid->usingIME = false;
	pid->usingVar = false;
	pid->ticksPerRev = ticksPerRev;
	pid->currentPosition = 0;
	pid->targetVelocity = 0.0;

	filter_Init_DEMA(&pid->filter, 0.19, 0.0526);

	pid->outVal = 0.0;
}
void vel_PID_InitController(vel_PID *pid, const tMotor imeMotor, const float kP, const float kD, float ticksPerRev)
{
	pid->kP = kP;
	pid->kD = kD;

	pid->error = 0;
	pid->currentVelocity = 0.0;
	pid->prevError = 0;
	pid->prevPosition = 0;
	pid->currentTime = 0;
	pid->prevTime = 0;
	pid->dt = 0.0;
	pid->derivative = 0;

	pid->imeMotor = imeMotor;
	pid->usingIME = true;
	pid->usingVar = false;
	pid->ticksPerRev = ticksPerRev;
	pid->currentPosition = 0;
	pid->targetVelocity = 0.0;

	filter_Init_DEMA(&pid->filter, 0.19, 0.0526);

	pid->outVal = 0.0;
}

void vel_PID_InitController(vel_PID *pid, const float *var, const float kP, const float kD, float ticksPerRev)
{
	pid->kP = kP;
	pid->kD = kD;

	pid->error = 0;
	pid->currentVelocity = 0.0;
	pid->prevError = 0;
	pid->prevPosition = 0;
	pid->currentTime = 0;
	pid->prevTime = 0;
	pid->dt = 0.0;
	pid->derivative = 0;

	pid->var = var;
	pid->usingIME = false;
	pid->usingVar = true;
	pid->ticksPerRev = ticksPerRev;
	pid->currentPosition = 0;
	pid->targetVelocity = 0.0;

	filter_Init_DEMA(&pid->filter, 0.19, 0.0526);

	pid->outVal = 0.0;
}

/*
* Sets new filter constants
*/
void vel_PID_SetFilterConstants(vel_PID *pid, const float alpha, const float beta)
{
	pid->alpha = alpha;
	pid->beta = beta;
}

void vel_PID_SetTargetVelocity(vel_PID *pid, const int targetVelocity)
{
	pid->targetVelocity = targetVelocity;
}

int vel_PID_GetError(vel_PID *pid)
{
	return pid->error;
}

int vel_PID_GetVelocity(vel_PID *pid)
{
	return pid->currentVelocity;
}

int vel_PID_GetOutput(vel_PID *pid)
{
	return pid->outVal;
}

int vel_PID_StepVelocity(vel_PID *pid)
{
	if (pid->usingIME)
	{
		//Calculate timestep
		getEncoderAndTimeStamp(pid->imeMotor, pid->currentPosition, pid->currentTime);
		pid->dt = (pid->currentTime - pid->prevTime) / 1000.0;
		pid->prevTime = pid->currentTime;

		//Scrap dt if zero
		if (pid->dt == 0)
		{
			return 0;
		}

		//Calculate current velocity
		pid->currentVelocity = pid->dt * (pid->currentPosition - pid->prevPosition) * 60.0 / pid->ticksPerRev;
		pid->prevPosition = pid->currentPosition;
	}
	else if (pid->usingVar)
	{
		//Calculate timestep
		pid->dt = (nSysTime - pid->prevTime) / 1000.0;
		pid->prevTime = nSysTime;

		//Scrap dt if zero
		if (pid->dt == 0)
		{
			return 0;
		}

		//Calculate current velocity
		pid->currentVelocity = pid->dt * (*(pid->var) - pid->prevPosition) * 60.0 / pid->ticksPerRev;
		pid->prevPosition = *(pid->var);
	}
	else
	{
		//Calculate timestep
		pid->dt = (nSysTime - pid->prevTime) / 1000.0;
		pid->prevTime = nSysTime;

		//Scrap dt if zero
		if (pid->dt == 0)
		{
			return 0;
		}

		//Calculate current velocity
		pid->currentVelocity = pid->dt * (SensorValue[pid->sensor] - pid->prevPosition) * 60.0 / pid->ticksPerRev;
		pid->prevPosition = SensorValue[pid->sensor];
	}

	//Use a DEMA filter to smooth data
	pid->currentVelocity = filter_DEMA(&(pid->filter), pid->currentVelocity, pid->alpha, pid->beta);

	return pid->currentVelocity;
}

int vel_PID_StepController(vel_PID *pid)
{
	//Calculate current velocity
	vel_PID_StepVelocity(pid);

	//Scrap dt if zero
	if (pid->dt == 0)
	{
		return 0;
	}

	//Calculate error
	pid->error = pid->targetVelocity - pid->currentVelocity;

	//Calculate derivative
	pid->derivative = (pid->error - pid->prevError) / pid->dt;
	pid->prevError = pid->error;

	//Sum outVal to instead compute the change in velocity
	pid->outVal += (pid->error * pid->kP) + (pid->derivative * pid->kD);

	return pid->outVal;
}

int vel_PID_StepController(vel_PID *pid, const int currentVelocity)
{
	//Calculate timestep
	pid->dt = (nSysTime - pid->prevTime) / 1000.0;
	pid->prevTime = nSysTime;

	//Scrap dt if zero
	if (pid->dt == 0)
	{
		return 0;
	}

	//Use given velocity
	pid->currentVelocity = currentVelocity;

	//Calculate error
	pid->error = pid->targetVelocity - pid->currentVelocity;

	//Calculate derivative
	pid->derivative = (pid->error - pid->prevError) / pid->dt;
	pid->prevError = pid->error;

	//Sum outVal to instead compute the change in velocity
	pid->outVal += (pid->error * pid->kP) + (pid->derivative * pid->kD);

	return pid->outVal;
}

#endif //BCI_VELOCITYPID_C_INCLUDED
