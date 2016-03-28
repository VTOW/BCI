#ifndef VELOCITYPID_H_INCLUDED
#define VELOCITYPID_H_INCLUDED

//This scale constant relates mesured ticks per second to motor power
#define PID_SCALE 2.67

//This scale relates degrees per millisecond to rpm
#define DEGPMS_TO_RPM 166.7

//A velocity PID controller
typedef struct vel_PID_t
{
	//PID constants
	float kP;
	float kI;
	float kD;

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
void vel_PID_InitController(vel_PID *pid, const tSensors sensor, const float kP, const float kI, const float kD, const int errorSumThreshold, const int integralCap);

//Sets the controller's target velocity
void vel_PID_SetTargetVelocity(vel_PID *pid, const int targetVelocity);

//Steps the controller's velocity calculations with out stepping math
int vel_PID_StepVelocity(vel_PID *pid);

//Steps the controller's calculations
int vel_PID_StepController(vel_PID *pid);

//Steps the controller's calculations with a given current velocity
int vel_PID_StepController(vel_PID *pid, const int currentVelocity);

#endif //VELOCITYPID_H_INCLUDED
