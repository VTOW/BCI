//Note: This library does not work with with Natural Language enabled

#ifndef MOTORCONTROL_H_INCLUDED
#define MOTORCONTROL_H_INCLUDED

//Motor general
#define MOTOR_NUM               10     //Used to be kNumbOfTotalMotors, changed for now because
                                       //that could result in a bug where a motor is not accessible
#define MOTOR_MIN_VALUE         (-127) //Minimum power
#define MOTOR_MAX_VALUE         127    //Maximum power
#define MOTOR_DEFAULT_SLEW_RATE 10     //Feels like nearly no slewing to a driver
#define MOTOR_FAST_SLEW_RATE    256    //No slewing in output
#define MOTOR_TASK_DELAY        15     //Wait 15ms between batch motor power updates

//Motor control
#define setMotorSpeed(index, power) driveMotors[index].reqSpeed = (power)
#define setMotorSlew(index, rate) driveMotors[index].slew = (rate)
#define getMotor(index) driveMotors[index]
#define getMotorSpeed(index) driveMotors[index].reqSpeed
#define setMotorActive(index) driveMotors[index].active = true
#define setMotorInactive(index) driveMotors[index].active = false

//Raw motor control
#define setMotorSpeedRaw(index, power) motor[index] = (power)
#define getMotorSpeedRaw(index) motor[index]

//Motor representation
typedef struct driveMotor
{
	int reqSpeed;   //Input speed
	float artSpeed; //Artificial speed (the exact speed as governed by the slew rate)
	float slew;     //Slew rate
	bool active;    //Whether or not to handle this motor
} driveMotor;

//Adds and initializes a motor (by name) to the motor array
driveMotor* addMotor(const tMotor name, float slewRate = MOTOR_DEFAULT_SLEW_RATE);

//Updates the power of each motor to best meet the requested power
task motorSlewRateTask();

#endif //#ifndef MOTORCONTROL_H_INCLUDED
