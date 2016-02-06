#ifndef PIDCONTROL_H_INCLUDED
#define PIDCONTROL_H_INCLUDED

//Do nothing with no PID Controllers
#ifdef PID_NUM
#if PID_NUM > 0

//PID control definitions
#define _SetTargetPosition(controller, pos) controller->targetPos = pos
#define _GetPIDSpeed(controller) controller->outVal
#define _ClearPIDControllers() nextPIDController = 0

//PID Controller representation
typedef struct pidController
{
	//PID constants
	float kP;
	float kI;
	float kD;
	float kBias;

	//PID calculation
	int error;
	int prevError;
	int integral;
	int derivative;

	//PID limits
	int errorThreshold;
	int integralLimit;

	//Input
	tSensors sensor;
	int targetPos;

	//Output
	int outVal;

	//Extra control
	bool isEnabled;
} pidController;

//Adds and initializes a PID Controller
pidController *newPIDController(tSensors sensor, float kP, float kI, float kD, float kBias = 0.0, int errorThreshold = 5, int integralLimit = 1000, bool isEnabled = true);

//Steps all enabled PID Controller's calculations
task updatePIDControllerTask();

#endif //#ifdef PID_NUM
#endif //#if PID_NUM > 0

#endif //#ifndef PIDCONTROL_H_INCLUDED
