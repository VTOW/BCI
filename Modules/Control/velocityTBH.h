#ifndef BCI_VELOCITYTBH_H_INCLUDED
#define BCI_VELOCITYTBH_H_INCLUDED

//A velocity TBH controller
typedef struct vel_TBH_t
{
	//TBH constants
	float gain;

	//TBH calculations
	float currentVelocity;
	int currentPosition;
	int prevPosition;
	int error;
	int prevError;
	bool firstCross;
	int outValApprox; //Output value at zero error for a given target velocity
	float outValAtZero;
	float outValChange;

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
	float targetVelocity;

	//Filtering
	DEMAFilter filter;
	float alpha;
	float beta;

	//Output
	float outVal;
} vel_TBH;

/**
 * Initializes a velocity TBH controller
 * @param tbh            TBH controller to initialize
 * @param sensor         Analog or digital senseor to read from
 * @param gain           Controller gain
 * @param outValApprox   Approximate controller output at zero error for a given
 *                       target velocity
 * @param targetVelocity Target velocity
 * @param ticksPerRev    Sensor ticks per revolution
 */
void vel_TBH_InitController(vel_TBH *tbh, const tSensors sensor, const float gain, const int outValApprox, int targetVelocity = 0.0, float ticksPerRev = UTIL_QUAD_TPR);

/**
 * Initializes a velocity TBH controller
 * @param tbh            TBH controller to initialize
 * @param imeMotor       Motor with IME attached
 * @param gain           Controller gain
 * @param outValApprox   Approximate controller output at zero error for a given
 *                       target velocity
 * @param targetVelocity Target velocity
 * @param ticksPerRev    Sensor ticks per revolution
 */
void vel_TBH_InitController(vel_TBH *tbh, const tMotor imeMotor, const float gain, const int outValApprox, int targetVelocity = 0.0, float ticksPerRev = UTIL_IME_HT_TPR);

/**
 * Initializes a velocity TBH controller
 * @param tbh            TBH controller to initialize
 * @param var            Float to read from
 * @param gain           Controller gain
 * @param outValApprox   Approximate controller output at zero error for a given
 *                       target velocity
 * @param targetVelocity Target velocity
 * @param ticksPerRev    Sensor ticks per revolution
 */
void vel_TBH_InitController(vel_TBH *tbh, const float *var, const float gain, const int outValApprox, int targetVelocity = 0.0, float ticksPerRev = UTIL_QUAD_TPR);

/**
 * Reinitializes a velocity TBH controller with previous sensor, gain, open-loop
 * approx, and filter
 * @param tbh TBH controller to use
 */
void vel_TBH_ReInitController(vel_TBH *tbh);

/**
 * Sets new filter constants
 * @param tbh   TBH controller to use
 * @param alpha New alpha term
 * @param beta  New beta term
 */
void vel_TBH_SetFilterConstants(vel_TBH *tbh, const float alpha, const float beta);

/**
 * Sets the target velocity. This should (normally) only be used when the target
 * velocity has changed
 * @param tbh            TBH controller to use
 * @param targetVelocity Target velocity
 * @param outValApprox   Approximate controller output at zero error for a given
 *                       target velocity
 */
void vel_TBH_SetTargetVelocity(vel_TBH *tbh, const int targetVelocity, const int outValApprox = -1010);

/**
 * Returns the current error
 * @param  tbh TBH controller to use
 * @return     Current error
 */
int vel_TBH_GetError(vel_TBH *tbh);

/**
 * Returns the current velocity
 * @param  tbh TBH controller to use
 * @return     Current velocity
 */
int vel_TBH_GetVelocity(vel_TBH *tbh);

/**
 * Returns the current target velocity
 * @param  tbh TBH controller to use
 * @return     Target velocity
 */
int vel_TBH_GetTargetVelocity(vel_TBH *tbh);

/**
 * Returns the current output
 * @param  tbh TBH controller to use
 * @return     Current output
 */
int vel_TBH_GetOutput(vel_TBH *tbh);

/**
 * Sets the open-loop approximation
 * @param tbh          TBH controller to use
 * @param outValApprox Approximate controller output at zero error for a given
 *                     target velocity
 */
void vel_TBH_SetOpenLoopApprox(vel_TBH *tbh, const int outValApprox);

/**
 * Returns the current open-loop approximation
 * @param  tbh TBH controller to use
 * @return     Current open-loop approximation
 */
int vel_TBH_GetOpenLoopApprox(vel_TBH *tbh);

/**
 * Steps the controller's velocity math only (does not compute a new output)
 * @param  tbh TBH controller to use
 * @return     Current velocity
 */
int vel_TBH_StepVelocity(vel_TBH *tbh);

/**
 * Steps the controller
 * @param  tbh TBH controller to use
 * @return     New output value
 */
int vel_TBH_StepController(vel_TBH *tbh);

/**
 * Steps the controller
 * @param  tbh             TBH controller to use
 * @param  currentVelocity Current velocity
 * @return                 New output value
 */
int vel_TBH_StepController(vel_TBH *tbh, const int currentVelocity);

#endif //BCI_VELOCITYTBH_H_INCLUDED
