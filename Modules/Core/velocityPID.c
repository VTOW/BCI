#ifndef VELOCITYPID_C_INCLUDED
#define VELOCITYPID_C_INCLUDED

#include "velocityPID.h"

void vel_PID_InitController(vel_PID *pid, const tSensors sensor, const float kP, const float kD)
{
	pid->kP = kP;
	pid->kD = kD;

	pid->error = 0;
	pid->currentVelocity = 0.0;
	pid->prevError = 0;
	pid->prevPosition = 0;
	pid->prevTime = 0;
	pid->dt = 0.0;
	pid->derivative = 0;

	pid->sensor = sensor;
	pid->currentPosition = 0;
	pid->targetVelocity = 0.0;

	pid->outVal = 0.0;
}

void vel_PID_SetTargetVelocity(vel_PID *pid, const int targetVelocity)
{
	pid->targetVelocity = targetVelocity;
}

int vel_PID_StepVelocity(vel_PID *pid)
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
	pid->currentVelocity = (SensorValue[pid->sensor] - pid->prevPosition) * (DEGPMS_TO_RPM / (pid->dt * 1000));
	pid->prevPosition = SensorValue[pid->sensor];

	return pid->currentVelocity;
}

int vel_PID_StepController(vel_PID *pid)
{
	//Calculate current velocity
	vel_PID_StepVelocity(pid);

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

#endif //VELOCITYPID_C_INCLUDED
