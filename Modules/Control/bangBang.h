#ifndef BCI_BANGBANG_H_INCLUDED
#define BCI_BANGBANG_H_INCLUDED

//Bang bang controller type
typedef struct bangBang_t
{
	//Power levels
	int highPower;
	int lowPower;

	//Bangbang calculations
	float currentVelocity;
	int currentPosition;
	int prevPosition;
	int error;

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
	int outVal;
} bangBang;

/**
 * Initializes a bangBang controller
 * @param bb             Controller to initialize
 * @param sensor         Sensor to read
 * @param highPower      High power
 * @param lowPower       Low power
 * @param targetVelocity Target velocity (default is zero)
 * @param ticksPerRev    Sensor ticks per revolution (default set for quadrature
 * encoders)
 */
void bangBang_InitController(bangBang *bb, const tSensors sensor, const int highPower, const int lowPower, int targetVelocity = 0, float ticksPerRev = UTIL_QUAD_TPR);

/**
 * Initializes a bangBang controller
 * @param bb             Controller to initialize
 * @param imeMotor       IME to read
 * @param highPower      High power
 * @param lowPower       Low power
 * @param targetVelocity Target velocity (default is zero)
 * @param ticksPerRev    Sensor ticks per revolution (default set for high
 * torque gearing)
 */
void bangBang_InitController(bangBang *bb, const tMotor imeMotor, const int highPower, const int lowPower, int targetVelocity = 0, float ticksPerRev = UTIL_IME_HT_TPR);

/**
 * Initializes a bangBang controller
 * @param bb             Controller to initialize
 * @param var            Pointer to float (acts as sensor reading)
 * @param highPower      High power
 * @param lowPower       Low power
 * @param targetVelocity Target velocity (default is zero)
 * @param ticksPerRev    Sensor ticks per revolution (default set for quadrature
 * encoder)
 */
void bangBang_InitController(bangBang *bb, const float *var, const int highPower, const int lowPower, int targetVelocity = 0, float ticksPerRev = UTIL_QUAD_TPR);

/**
 * Sets new filter constants
 * @param bb    Controller to modify
 * @param alpha New alpha term
 * @param beta  New beta term
 */
void bangBang_SetFilterConstants(bangBang *bb, const float alpha, const float beta);

/**
 * Sets the target velocity
 * @param bb             Controller to modify
 * @param targetVelocity Target velocity
 */
void bangBang_SetTargetVelocity(bangBang *bb, const int targetVelocity);

/**
 * Gets the current error
 * @param  bb Controller to read
 * @return    Error
 */
int bangBang_GetError(const bangBang *bb);

/**
 * Gets the current (filtered) velocity
 * @param  bb Controller to read
 * @return    Filtered velocity
 */
int bangBang_GetVelocity(const bangBang *bb);

/**
 * Gets the current target velocity
 * @param  bb Controller to read
 * @return    Target velocity
 */
int bangBang_GetTargetVelocity(const bangBang *bb);

/**
 * Gets the current output
 * @param  bb Controller to read
 * @return    Control value
 */
int bangBang_GetOutput(const bangBang *bb);

/**
 * Steps the controller's velocity calculation (separate from the main step
 * function). Can be used to maintain velocity calculation when a full on math
 * step isn't wanted
 * @param  bb Controller to step
 * @return    Control value
 */
int bangBang_StepVelocity(bangBang *bb);

/**
 * Steps the controller calculations
 * @param  bb Controller to step
 * @return    Control value
 */
int bangBang_StepController(bangBang *bb);

#endif //BCI_BANGBANG_H_INCLUDED
