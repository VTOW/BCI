#ifndef VELOCITYPID_H_INCLUDED
#define VELOCITYPID_H_INCLUDED

//This scale constant relates mesured ticks per second to motor power
#define PID_SCALE 2.67

//This scale relates degrees per millisecond to rpm
#define DEGPMS_TO_RPM 166.7

//A velocity PID controller
typedef struct vel_PID
{
	//PID constants
	float kP;
	float kI;
	float kD;
	float upperBound;
	float lowerBound;

	//PID calculations
	float currentVelocity;
	int prevPosition;
	int error;
	int prevError;
	int integral;
	int derivative;

	//Timestep
	float dt;
	int prevTime;

	//PID limits
	int errorSumThreshold;
	int integralCap;

	//Input
	tSensors sensor;
	int currentPosition;
	float targetVelocity;

	//Output
	float outVal;
} vel_PID;

//Initializes a velocity PID controller
void vel_PID_InitController(vel_PID* pid, tSensors sensor, float kP, float kI, float kD, int errorSumThreshold, int integralCap);

//Steps the controller's calculations (position based)
int vel_PID_StepController_POS(vel_PID* pid);

//Steps the controller's calculations (velocity based)
int vel_PID_StepController_VEL(vel_PID* pid);

//Steps the controller's calculations (velocity based)
int vel_PID_StepController_VEL(vel_PID* pid, int currentVelocity);

//Steps the controller's calculations (acceleration based)
int vel_PID_StepController_ACCEL(vel_PID *pid);

#endif
