#ifndef PIDCONTROL_H_INCLUDED
#define PIDCONTROL_H_INCLUDED

//PID Controller representation
typedef struct pos_PID
{
	//PID constants
	float kP;
	float kI;
	float kD;
	float kBias;

	//PID calculations
	int error;
	int prevError;
	int integral;
	int derivative;

	//PID limits
	int errorThreshold;
	int integralLimit;

	//Timestep
	float dt;
	int prevTime;

	//Input
	tSensors sensor;
	int targetPos;

	//Output
	int outVal;
} pos_PID;

//Initializes a position PID controller
void pos_PID_InitController(pos_PID *pid, const tSensors sensor, const float kP, const float kI, const float kD, const float kBias = 0.0, const int errorThreshold = 5, const int integralLimit = 1000, const bool isEnabled = true);

//Sets the target position
void pos_PID_SetTargetPosition(pos_PID *pid, const int targetPos);

//Steps the controller's calculations
int pos_PID_StepController(pos_PID *pid);

#endif //PIDCONTROL_H_INCLUDED
