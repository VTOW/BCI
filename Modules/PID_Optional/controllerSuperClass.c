#ifndef CONTROLLERSUPERCLASS_C_INCLUDED
#define CONTROLLERSUPERCLASS_C_INCLUDED

#include "controllerSuperClass.h"

//Initializes the controller
#ifdef CSC_USING_POSPID
	void csc_InitController(controllerSC *csc, const tSensors sensor, const float kP, const float kI, const float kD, const float kBias, const int errorThreshold, const int integralLimit)
	{ pos_PID_InitController(csc->pid, sensor, kP, kI, kD, kBias, errorThreshold, integralLimit); }
	
	void csc_InitController(controllerSC *csc, const tMotor imeMotor, const float kP, const float kI, const float kD, const float kBias, const int errorThreshold, const int integralLimit);
	{ pos_PID_InitController(csc->pid, imeMotor, kP, kI, kD, kBias, errorThreshold, integralLimit); }
	
	void csc_InitController(controllerSC *csc, const float *var, const float kP, const float kI, const float kD, const float kBias, const int errorThreshold, const int integralLimit)
	{ pos_PID_InitController(csc->pid, var, kP, kI, kD, kBias, errorThreshold, integralLimit); }
#elif CSC_USING_VELPID //CSC_USING_POSPID
	void csc_InitController(controllerSC *csc, const tSensors sensor, const float kP, const float kD, const float ticksPerRev)
	{ vel_PID_InitController(csc->pid, sensor, kP, kD, ticksPerRev); }

	void csc_InitController(controllerSC *csc, const tMotor imeMotor, const float kP, const float kD, const float ticksPerRev)
	{ vel_PID_InitController(csc->pid, imeMotor, kP, kD, ticksPerRev); }

	void csc_InitController(controllerSC *csc, const float kP, const float kD, const float ticksPerRev)
	{ vel_PID_InitController(csc->pid, kP, kD, ticksPerRev); }
#elif CSC_USING_VELTBH //CSC_USING_VELPID
	void csc_InitController(controllerSC *csc, const tSensors sensor, const float gain, const int outValApprox, const int targetVelocity, const float ticksPerRev)
	{ vel_TBH_InitController(csc->pid, sensor, gain, outValApprox, targetVelocity, ticksPerRev); }

	void csc_InitController(controllerSC *csc, const tMotor imeMotor, const float gain, const int outValApprox, const int targetVelocity, const float ticksPerRev)
	{ vel_TBH_InitController(csc->pid, imeMotor, gain, outValApprox, targetVelocity, ticksPerRev); }

	void csc_InitController(controllerSC *csc, const float *var, const float gain, const int outValApprox, const int targetVelocity, const float ticksPerRev)
	{ vel_TBH_InitController(csc->pid, var, gain, outValApprox, targetVelocity, ticksPerRev); }
#endif //CSC_USING_VELTBH

//Sets the target of the controller
void csc_SetTarget(controllerSC *csc, const int target)
{
	#ifdef CSC_USING_POSPID
		pos_PID_SetTargetPosition(csc->pid, target);
	#elif CSC_USING_VELPID //CSC_USING_POSPID
		vel_PID_SetTargetVelocity(csc->pid, target);
	#elif CSC_USING_VELTBH //CSC_USING_VELPID
		vel_TBH_SetTargetVelocity(csc->pid, target);
	#endif
}

//Gets the current error
int csc_GetError(controllerSC *csc)
{
	#ifdef CSC_USING_POSPID
		return pos_PID_GetError(csc->pid);
	#elif CSC_USING_VELPID //CSC_USING_POSPID
		return vel_PID_GetError(csc->pid);
	#elif CSC_USING_VELTBH //CSC_USING_VELPID
		return vel_TBH_GetError(csc->pid);
	#endif
}

//Gets the current output
int csc_GetOutput(controllerSC *csc)
{
	#ifdef CSC_USING_POSPID
		return pos_PID_GetOutput(csc->pid);
	#elif CSC_USING_VELPID //CSC_USING_POSPID
		return vel_PID_GetOutput(csc->pid);
	#elif CSC_USING_VELTBH //CSC_USING_VELPID
		return vel_TBH_GetOutput(csc->pid);
	#endif
}

//Steps the controller
int csc_StepController(controllerSC *csc)
{
	#ifdef CSC_USING_POSPID
		return pos_PID_StepController(csc->pid);
	#elif CSC_USING_VELPID //CSC_USING_POSPID
		return vel_PID_StepController(csc->pid);
	#elif CSC_USING_VELTBH //CSC_USING_VELPID
		return vel_TBH_StepController(csc->pid);
	#endif
}

#endif //CONTROLLERSUPERCLASS_C_INCLUDED
