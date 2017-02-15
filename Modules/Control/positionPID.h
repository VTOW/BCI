#ifndef BCI_POSITIONPID_H_INCLUDED
#define BCI_POSITIONPID_H_INCLUDED

//PID Controller representation
typedef struct pos_PID_t
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
	int upperBound;
	int lowerBound;

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
	int targetPos;
	int currentPos;

	//Output
	int outVal;
} pos_PID;

/**
 * Initializes a position PID controller
 * @param pid            PID controller to initialize
 * @param sensor         Analog or digital sensor to read from
 * @param kP             Proportional gain
 * @param kI             Integral gain
 * @param kD             Derivative gain
 * @param kBias          Controller bias (Constant force applied)
 * @param errorThreshold Minimum error to sum for integral
 * @param integralLimit  Upper limit of integral term
 */
void pos_PID_InitController(pos_PID *pid, const tSensors sensor, const float kP, const float kI, const float kD, float kBias = 0.0, int errorThreshold = 0, int integralLimit = 1000000);

/**
 * Initializes a position PID controller
 * @param pid            PID controller to initialize
 * @param imeMotor       Name of motor with IME attached
 * @param kP             Proportional gain
 * @param kI             Integral gain
 * @param kD             Derivative gain
 * @param kBias          Controller bias (Constant force applied)
 * @param errorThreshold Minimum error to sum for integral
 * @param integralLimit  Upper limit of integral term
 */
void pos_PID_InitController(pos_PID *pid, const tMotor imeMotor, const float kP, const float kI, const float kD, float kBias = 0.0, const int errorThreshold = 0, int integralLimit = 1000000);

/**
 * Initializes a position PID controller
 * @param pid            PID controller to initialize
 * @param var            Float to read from
 * @param kP             Proportional gain
 * @param kI             Integral gain
 * @param kD             Derivative gain
 * @param kBias          Controller bias (Constant force applied)
 * @param errorThreshold Minimum error to sum for integral
 * @param integralLimit  Upper limit of integral term
 */
void pos_PID_InitController(pos_PID *pid, const float *var, const float kP, const float kI, const float kD, float kBias = 0.0, int errorThreshold = 0, int integralLimit = 1000000);

/**
 * Sets a new kBias term
 * @param pid   PID controller to use
 * @param kBias New kBias term
 */
void pos_PID_ChangeBias(pos_PID *pid, const float kBias);

/**
 * Sets new upper and lower bounds for the ouput of the controller
 * @param pid   PID controller to use
 * @param upper Upper bound
 * @param lower Lower bound
 */
void pos_PID_ChangeBounds(pos_PID *pid, const int upper, const int lower);

/**
 * Changes the sensor
 * @param pid    PID controller to use
 * @param sensor New sensor
 */
void pos_PID_ChangeSensor(pos_PID *pid, const tSensors sensor);

/**
 * Changes the sensor
 * @param pid      PID controller to use
 * @param imeMotor New IME motor
 */
void pos_PID_ChangeSensor(pos_PID *pid, const tMotor imeMotor);

/**
 * Changes the sensor
 * @param pid PID controller to use
 * @param var New float to read from
 */
void pos_PID_ChangeSensor(pos_PID *pid, const float *var);

/**
 * Sets the target position
 * @param pid       PID controller to use
 * @param targetPos New target position
 */
void pos_PID_SetTargetPosition(pos_PID *pid, const int targetPos);

/**
 * Returns the current error
 * @param  pid PID controller to use
 * @return     Current error
 */
int pos_PID_GetError(pos_PID *pid);

/**
 * Returns the current position
 * @param  pid PID controller to use
 * @return     Current position
 */
int pos_PID_GetPosition(pos_PID *pid);

/**
 * Returns the current output
 * @param  pid PID controller to use
 * @return     Current output
 */
int pos_PID_GetOutput(pos_PID *pid);

/**
 * Steps the controller's calculations
 * @param  pid PID controller to use
 * @return     New output
 */
int pos_PID_StepController(pos_PID *pid);

/**
 * Steps the controller's calculations
 * @param  pid PID controller to use
 * @param  val Current position
 * @return     New output
 */
int pos_PID_StepController(pos_PID *pid, const float val);

#endif //BCI_POSITIONPID_H_INCLUDED
