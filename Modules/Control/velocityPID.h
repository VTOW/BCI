#ifndef BCI_VELOCITYPID_H_INCLUDED
#define BCI_VELOCITYPID_H_INCLUDED

//A velocity PID controller
typedef struct vel_PID_t
{
	//PID constants
	float kP;
	float kD;

	//PID calculations
	float currentVelocity;
	int prevPosition;
	int error;
	int prevError;
	int derivative;

	//Timestep
	float dt;
	int currentTime;
	int prevTime;

	//Input
	tSensors sensor;
	tMotor imeMotor;
	float *var;
	bool usingIME;
	bool usingVar;
	float ticksPerRev;
	int currentPosition;
	float targetVelocity;

	//Filtering
	DEMAFilter filter;
	float alpha;
	float beta;

	//Output
	float outVal;
} vel_PID;

/**
 * Initializes a velocity PID controller
 * @param pid         PID controller to initialize
 * @param sensor      Analog to digital sensor to read from
 * @param kP          Propotional gain
 * @param kD          Derivative gain
 * @param ticksPerRev Sensor ticks per one revolution
 */
void vel_PID_InitController(vel_PID *pid, const tSensors sensor, const float kP, const float kD, float ticksPerRev = UTIL_QUAD_TPR);

/**
 * Initializes a velocity PID controller
 * @param pid         PID controller to initialize
 * @param imeMotor    Motor with IME attached
 * @param kP          Propotional gain
 * @param kD          Derivative gain
 * @param ticksPerRev Sensor ticks per one revolution
 */
void vel_PID_InitController(vel_PID *pid, const tMotor imeMotor, const float kP, const float kD, float ticksPerRev = UTIL_IME_HT_TPR);

/**
 * Initializes a velocity PID controller
 * @param pid         PID controller to initialize
 * @param var         Float to read from
 * @param kP          Propotional gain
 * @param kD          Derivative gain
 * @param ticksPerRev Sensor ticks per one revolution
 */
void vel_PID_InitController(vel_PID *pid, const float *var, const float kP, const float kD, float ticksPerRev = UTIL_QUAD_TPR);

/**
 * Sets new filter constants
 * @param pid   PID controller to use
 * @param alpha New alpha term
 * @param beta  New beta term
 */
void vel_PID_SetFilterConstants(vel_PID *pid, const float alpha, const float beta);

/**
 * Sets the controller's target velocity
 * @param pid            PID controller to use
 * @param targetVelocity New target velocity
 */
void vel_PID_SetTargetVelocity(vel_PID *pid, const int targetVelocity);

/**
 * Returns the current error
 * @param  pid PID controller to use
 * @return     Current error
 */
int vel_PID_GetError(vel_PID *pid);

/**
 * Returns the current velocity
 * @param  pid PID controller to use
 * @return     Current velocity
 */
int vel_PID_GetVelocity(vel_PID *pid);

/**
 * Returns the current output
 * @param  pid PID controller to use
 * @return     Current output
 */
int vel_PID_GetOutput(vel_PID *pid);

/**
 * Steps the controller's velocity math only (does not compute a new output)
 * @param  pid PID controller to use
 * @return     Current velocity
 */
int vel_PID_StepVelocity(vel_PID *pid);

/**
 * Steps the controller
 * @param  pid PID controller to use
 * @return     New output value
 */
int vel_PID_StepController(vel_PID *pid);

/**
 * Steps the controller
 * @param  pid             PID controller to use
 * @param  currentVelocity Current velocity
 * @return                 New output value
 */
int vel_PID_StepController(vel_PID *pid, const int currentVelocity);

#endif //BCI_VELOCITYPID_H_INCLUDED
