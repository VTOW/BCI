#ifndef PVPID_H_INCLUDED
#define PVPID_H_INCLUDED

#include "..\Core\positionPID.h"
#include "..\Core\velocityPID.h"

typedef struct pvPID_t
{
	//Velocity feed forward
	float vff;


} pvPID;

//Initializes a pvPID controller
void pvPID_InitController(pvPID *pid, const tSensors sensor, const float *mp);
void pvPID_InitController(pvPID *pid, const tMotor imeMotor, const float *mp);
void pvPID_InitController(pvPID *pid, const float *var, const float *mp);

#endif //PVPID_H_INCLUDED
