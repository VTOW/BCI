#ifndef BCI_POSITIONPID_C_INCLUDED
#define BCI_POSITIONPID_C_INCLUDED

#include "positionPID.h"

void pos_PID_InitController(pos_PID *pid, const tSensors sensor, const float kP, const float kI, const float kD, float kBias, int errorThreshold, int integralLimit)
{
	pid->kP = kP;
	pid->kI = kI;
	pid->kD = kD;
	pid->kBias = kBias;

	pid->error = 0;
	pid->prevError = 0;
	pid->integral = 0;
	pid->derivative = 0;

	pid->errorThreshold = errorThreshold;
	pid->integralLimit = integralLimit;
	pid->upperBound = 127;
	pid->lowerBound = -127;

	pid->dt = 0;
	pid->currentTime = 0;
	pid->prevTime = 0;

	pid->sensor = sensor;
	pid->usingIME = false;
	pid->usingVar = false;
	pid->targetPos = SensorValue[sensor];
	pid->currentPos = 0;

	pid->outVal = 0;
}

void pos_PID_InitController(pos_PID *pid, const tMotor imeMotor, const float kP, const float kI, const float kD, float kBias, int errorThreshold, int integralLimit)
{
	pid->kP = kP;
	pid->kI = kI;
	pid->kD = kD;
	pid->kBias = kBias;

	pid->error = 0;
	pid->prevError = 0;
	pid->integral = 0;
	pid->derivative = 0;

	pid->errorThreshold = errorThreshold;
	pid->integralLimit = integralLimit;
	pid->upperBound = 127;
	pid->lowerBound = -127;

	pid->dt = 0;
	pid->prevTime = 0;

	pid->imeMotor = imeMotor;
	pid->usingIME = true;
	pid->usingVar = false;
	pid->targetPos = nMotorEncoder[imeMotor];

	pid->outVal = 0;
}

void pos_PID_InitController(pos_PID *pid, const float *var, const float kP, const float kI, const float kD, float kBias, int errorThreshold, int integralLimit)
{
	pid->kP = kP;
	pid->kI = kI;
	pid->kD = kD;
	pid->kBias = kBias;

	pid->error = 0;
	pid->prevError = 0;
	pid->integral = 0;
	pid->derivative = 0;

	pid->errorThreshold = errorThreshold;
	pid->integralLimit = integralLimit;
	pid->upperBound = 127;
	pid->lowerBound = -127;

	pid->dt = 0;
	pid->prevTime = 0;

	pid->var = var;
	pid->usingIME = false;
	pid->usingVar = true;
	pid->targetPos = *var;

	pid->outVal = 0;
}

void pos_PID_ChangeBias(pos_PID *pid, const float kBias)
{
	pid->kBias = kBias;
}

void pos_PID_ChangeBounds(pos_PID *pid, const int upper, const int lower)
{
	pid->upperBound = upper;
	pid->lowerBound = lower;
}

void pos_PID_ChangeSensor(pos_PID *pid, const tSensors sensor)
{
	pid->sensor = sensor;
	pid->usingIME = false;
	pid->usingVar = false;
}

void pos_PID_ChangeSensor(pos_PID *pid, const tMotor imeMotor)
{
	pid->imeMotor = imeMotor;
	pid->usingIME = true;
	pid->usingVar = false;
}

void pos_PID_ChangeSensor(pos_PID *pid, const float *var)
{
	pid->var = var;
	pid->usingVar = true;
	pid->usingIME = false;
}

void pos_PID_SetTargetPosition(pos_PID *pid, const int targetPos)
{
	pid->targetPos = targetPos;
}

int pos_PID_GetError(pos_PID *pid)
{
	return pid->error;
}

int pos_PID_GetPosition(pos_PID *pid)
{
	return pid->currentPos;
}

int pos_PID_GetOutput(pos_PID *pid)
{
	return pid->outVal;
}

int pos_PID_StepController(pos_PID *pid)
{
	//Calculate error
	if (pid->usingIME)
	{
		//Calculate timestep
		getEncoderAndTimeStamp(pid->imeMotor, pid->currentPos, pid->currentTime);
		pid->dt = (pid->currentTime - pid->prevTime) / 1000.0;
		pid->prevTime = pid->currentTime;

		//Scrap dt if zero
		if (pid->dt == 0)
		{
			return 0;
		}

		pid->error = pid->targetPos - pid->currentPos;
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

		pid->currentPos = *(pid->var);
		pid->error = pid->targetPos - pid->currentPos;
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

		pid->currentPos = SensorValue[pid->sensor];
		pid->error = pid->targetPos - pid->currentPos;
	}

	//If error is large enough, calculate integral and limit to avoid windup
	if (abs(pid->error) > pid->errorThreshold && abs(pid->integral) < pid->integralLimit)
	{
		pid->integral = pid->integral + pid->error * pid->dt;

		//Reset integral if reached target or overshot
		if (pid->error == 0 || sgn(pid->error) != sgn(pid->prevError))
		{
			pid->integral = 0;
		}
		//Bound integral
		else
		{
			pid->integral = pid->integral * pid->kI > 127 ? 127.0 / pid->kI : pid->integral;
			pid->integral = pid->integral * pid->kI < -127 ? -127.0 / pid->kI : pid->integral;
		}
	}

	//Calculate derivative
	pid->derivative = (pid->error - pid->prevError) / pid->dt;
	pid->prevError = pid->error;

	//Calculate output
	pid->outVal = (pid->error * pid->kP) + (pid->integral * pid->kI) + (pid->derivative * pid->kD) + pid->kBias;

	//Bound output
	if (pid->outVal > pid->upperBound)
	{
		pid->outVal = pid->upperBound;
	}
	else if (pid->outVal < pid->lowerBound)
	{
		pid->outVal = pid->lowerBound;
	}

	return pid->outVal;
}

int pos_PID_StepController(pos_PID *pid, const float val)
{
	//Calculate timestep
	pid->dt = (nSysTime - pid->prevTime) / 1000.0;
	pid->prevTime = nSysTime;

	//Scrap dt if zero
	if (pid->dt == 0)
	{
		return 0;
	}

	//Calculate error
	pid->error = pid->targetPos - val;

	//If error is large enough, calculate integral and limit to avoid windup
	if (abs(pid->error) > pid->errorThreshold && abs(pid->integral) < pid->integralLimit)
	{
		pid->integral = pid->integral + pid->error * pid->dt;

		//Reset integral if reached target or overshot
		if (pid->error == 0 || sgn(pid->error) != sgn(pid->prevError))
		{
			pid->integral = 0;
		}
		//Bound integral
		else
		{
			pid->integral = pid->integral * pid->kI > 127 ? 127.0 / pid->kI : pid->integral;
			pid->integral = pid->integral * pid->kI < -127 ? -127.0 / pid->kI : pid->integral;
		}
	}

	//Calculate derivative
	pid->derivative = (pid->error - pid->prevError) / pid->dt;
	pid->prevError = pid->error;

	//Calculate output
	pid->outVal = (pid->error * pid->kP) + (pid->integral * pid->kI) + (pid->derivative * pid->kD) + pid->kBias;

	//Bound output
	if (pid->outVal > pid->upperBound)
	{
		pid->outVal = pid->upperBound;
	}
	else if (pid->outVal < pid->lowerBound)
	{
		pid->outVal = pid->lowerBound;
	}

	return pid->outVal;
}

#endif //BCI_POSITIONPID_C_INCLUDED
