#ifndef VELOCITYPID_C_INCLUDED
#define VELOCITYPID_C_INCLUDED

#include "VelocityPID.h"

void vel_PID_InitController(vel_PID *pid, tSensors sensor, float kP, float kI, float kD, int errorSumThreshold, int integralCap)
{
	pid->kP = kP;
	pid->kI = kI;
	pid->kD = kD;
	pid->upperBound = 1.2;
	pid->lowerBound = 0.8;

	pid->error = 0;
	pid->currentVelocity = 0.0;
	pid->prevError = 0;
	pid->prevPosition = 0;
	pid->prevTime = 0;
	pid->dt = 0.0;
	pid->integral = 0;
	pid->derivative = 0;

	pid->errorSumThreshold = errorSumThreshold;
	pid->integralCap = integralCap;

	pid->sensor = sensor;
	pid->currentPosition = 0;
	pid->targetVelocity = 0.0;

	pid->outVal = 0.0;
}

int vel_PID_StepController(vel_PID *pid)
{
	//Calculate timestep
	pid->dt = (time1[T1] - pid->prevTime);
	pid->prevTime = time1[T1];

	//Calculate current velocity
	pid->currentVelocity = (SensorValue[pid->sensor] - pid->prevPosition) * (DEGPMS_TO_RPM / (pid->dt * 1000));
	pid->prevPosition = SensorValue[pid->sensor];

	//Calculate error
	pid->error = pid->targetVelocity - pid->currentVelocity;

	//If error is larger than the error sum threshold, calculate integral
	if (abs(pid->error) < pid->errorSumThreshold)
	{
		pid->integral += pid->error * pid->dt;
	}

	//Limit integral to avoid windup
	if (abs(pid->integral) > pid->integralCap)
	{
		pid->integral = pid->integralCap;
	}

	//Calculate derivative
	pid->derivative = (pid->error - pid->prevError) / pid->dt;
	pid->prevError = pid->error;

	//Sum outVal to instead compute the change in velocity
	//pid->outVal += (pid->error * pid->kP) + (pid->integral * pid->kI) + (pid->derivative * pid->kD);
	pid->outVal = (pid->targetVelocity / PID_SCALE) + (pid->error * pid->kP);

	return pid->outVal;
}

int vel_PID_StepController(vel_PID *pid, int currentVelocity)
{
	//Calculate timestep
	pid->dt = (time1[T1] - pid->prevTime);
	pid->prevTime = time1[T1];

	//Use given velocity
	pid->currentVelocity = currentVelocity;

	//Calculate error
	pid->error = pid->targetVelocity - pid->currentVelocity;

	//If error is larger than the error sum threshold, calculate integral
	if (abs(pid->error) < pid->errorSumThreshold)
	{
		pid->integral += pid->error * pid->dt;
	}

	//Limit integral to avoid windup
	if (abs(pid->integral) > pid->integralCap)
	{
		pid->integral = pid->integralCap;
	}

	//Calculate derivative
	pid->derivative = (pid->error - pid->prevError) / pid->dt;
	pid->prevError = pid->error;

	//Sum outVal to instead compute the change in velocity
	//pid->outVal += (pid->error * pid->kP) + (pid->integral * pid->kI) + (pid->derivative * pid->kD);
	pid->outVal = (pid->targetVelocity / PID_SCALE) + (pid->error * pid->kP);

	return pid->outVal;
}

#endif
