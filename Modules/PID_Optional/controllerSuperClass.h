#ifndef CONTROLLERSUPERCLASS_H_INCLUED
#define CONTROLLERSUPERCLASS_H_INCLUED

#include "..\Core\positionPID.c"
#include "..\Core\velocityPID.c"
#include "..\Core\velocityTBH.c"

typedef struct controllerSC_t
{
	#ifdef CSC_USING_POSPID
		pos_PID pid;
	#elif CSC_USING_VELPID //CSC_USING_POSPID
		vel_PID pid;
	#elif CSC_USING_VELTBH //CSC_USING_VELPID
		vel_TBH pid;
	#endif //CSC_USING_VELTBH
} controllerSC;

//Initializes the controller
#ifdef CSC_USING_POSPID
	void csc_InitController(controllerSC *csc, const tSensors sensor, const float kP, const float kI, const float kD, const float kBias = 0.0, const int errorThreshold = 0, const int integralLimit = 1000000);
	void csc_InitController(controllerSC *csc, const tMotor imeMotor, const float kP, const float kI, const float kD, const float kBias = 0.0, const int errorThreshold = 0, const int integralLimit = 1000000);
	void csc_InitController(controllerSC *csc, const float *var, const float kP, const float kI, const float kD, const float kBias = 0.0, const int errorThreshold = 0, const int integralLimit = 1000000);
#elif CSC_USING_VELPID //CSC_USING_POSPID
	void csc_InitController(controllerSC *csc, const tSensors sensor, const float kP, const float kD, const float ticksPerRev = UTIL_QUAD_TPR);
	void csc_InitController(controllerSC *csc, const tMotor imeMotor, const float kP, const float kD, const float ticksPerRev = UTIL_IME_HT_TPR);
	void csc_InitController(controllerSC *csc, const float kP, const float kD, const float ticksPerRev = UTIL_QUAD_TPR);
#elif CSC_USING_VELTBH //CSC_USING_VELPID
	void csc_InitController(controllerSC *csc, const tSensors sensor, const float gain, const int outValApprox, const int targetVelocity = 0.0, const float ticksPerRev = UTIL_QUAD_TPR);
	void csc_InitController(controllerSC *csc, const tMotor imeMotor, const float gain, const int outValApprox, const int targetVelocity = 0.0, const float ticksPerRev = UTIL_IME_HT_TPR);
	void csc_InitController(controllerSC *csc, const float *var, const float gain, const int outValApprox, const int targetVelocity = 0.0, const float ticksPerRev = UTIL_QUAD_TPR);
#endif //CSC_USING_VELTBH

//Sets the target of the controller
void csc_SetTarget(controllerSC *csc, const int target);

//Gets the current error
int csc_GetError(controllerSC *csc);

//Gets the current output
int csc_GetOutput(controllerSC *csc);

//Steps the controller
void csc_StepController(controllerSC *csc);

#endif //CONTROLLERSUPERCLASS_H_INCLUED
