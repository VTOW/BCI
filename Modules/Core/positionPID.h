#ifndef POSITIONPID_H_INCLUDED
#define POSITIONPID_H_INCLUDED

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
void pos_PID_InitController(pos_PID *pid, const tSensors sensor, const float kP, const float kI, const float kD, const float kBias = 0.0, const int errorThreshold = 0, const int integralLimit = 1000);

//Sets the target position
void pos_PID_SetTargetPosition(pos_PID *pid, const int targetPos);

//Gets the current error
int pos_PID_GetError(pos_PID *pid);

//Gets the current output
int pos_PID_GetOutput(pos_PID *pid);

//Steps the controller's calculations
int pos_PID_StepController(pos_PID *pid);

#endif //POSITIONPID_H_INCLUDED
