#ifndef BCI_MOTORCONTROL_H_INCLUDED
#define BCI_MOTORCONTROL_H_INCLUDED

//Note: This library does not work with with Natural Language enabled

//Motor general
#define MOTOR_NUM               10     //Used to be kNumbOfTotalMotors, changed for now because
                                       //that could result in a bug where a motor is not accessible
#define MOTOR_MIN_VALUE         (-127) //Minimum speed
#define MOTOR_MAX_VALUE         127    //Maximum speed
#define MOTOR_DEFAULT_SLEW_RATE 10     //Feels like nearly no slewing to a driver
#define MOTOR_FAST_SLEW_RATE    256    //No slewing in output
#define MOTOR_TASK_DELAY        15     //Wait 15ms between batch motor speed updates

/**
 * Sets the speed of a motor
 * @param  index Motor to use (as named in Motors and Sensors Setup)
 * @param  speed New speed
 */
#define setMotorSpeed(index, speed) driveMotors[index].reqSpeed = (speed)

/**
 * Sets the powr of a motor instantly (bypassing any slewing)
 * @param  index Motor to use (as named in Motors and Sensors Setup)
 * @param  speed New speed
 */
#define setMotorSpeed_Bypass(index, speed) driveMotors[index].reqSpeed = (speed); driveMotors[index].artSpeed = (speed)

/**
 * Sets the slew rate of a motor
 * @param  index Motor to use (as named in Motors and Sensors Setup)
 * @param  rate  New slew rate
 */
#define setMotorSlew(index, rate) driveMotors[index].slew = (rate)

/**
 * Returns the driveMotor representation of a motor
 * @param  index Motor to use (as named in Motors and Sensors Setup)
 * @return       driveMotor representation of the motor
 */
#define getMotor(index) driveMotors[index]

/**
 * Returns the motor speed of a motor (target speed, not current speed)
 * @param  index Motor to use (as named in Motors and Sensors Setup)
 * @return       Motor speed
 */
#define getMotorSpeed(index) driveMotors[index].reqSpeed

/**
 * Enables slewing of a motor (slewing enabled by default)
 * @param  index Motor to use (as named in Motors and Sensors Setup)
 */
#define setMotorActive(index) driveMotors[index].active = true

/**
 * Disables slewing of a motor
 * @param  index Motor to use (as named in Motors and Sensors Setup)
 */
#define setMotorInactive(index) driveMotors[index].active = false

/**
 * Sets the raw speed of a motor. The slew rate controller will fight this value
 * unless the motor has been disabled with setMotorInactive()
 * @param  index Motor to use (as named in Motors and Sensors Setup)
 * @param  speed New speed
 */
#define setMotorSpeedRaw(index, speed) motor[index] = (speed)

/**
 * Returns the speed of a motor (true current speed, not target speed)
 * @param  index Motor to use (as named in Motors and Sensors Setup)
 * @return       Motor speed
 */
#define getMotorSpeedRaw(index) motor[index]

//Motor representation
typedef struct driveMotor_t
{
	int reqSpeed;   //Input speed
	float artSpeed; //Artificial speed (the exact speed as governed by the slew rate)
	float slew;     //Slew rate
	bool active;    //Whether or not to update this motor
} driveMotor;

/**
 * Initializes a driveMotor
 * @param  name     Motor to use (as named in Motor and Sensors Setup)
 * @param  slewRate Slew rate
 * @return          Initialized driveMotor
 */
driveMotor* addMotor(const tMotor name, float slewRate = MOTOR_DEFAULT_SLEW_RATE);

/**
 * Loops through all driveMotors, slewing active ones to meet their target
 */
task motorSlewRateTask();

#endif //BCI_MOTORCONTROL_H_INCLUDED
