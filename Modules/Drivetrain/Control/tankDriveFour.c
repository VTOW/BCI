#pragma systemFile

#ifndef TANKDRIVEFOUR_C_INCLUDED
#define TANKDRIVEFOUR_C_INCLUDED

#ifdef FOUR_MOTOR_TANK_DRIVE

#include "tankDriveFour.h"
#include "..\..\Core\motorControl.c"
#include "..\..\Core\joystickDefinitions.h"

#define setAllDriveMotors(power) setMotorSpeed(drive.leftTop, power); setMotorSpeed(drive.leftBottom, power); setMotorSpeed(drive.rightTop, power); setMotorSpeed(drive.rightBottom, power)
#define setLeftDriveMotors(power) setMotorSpeed(drive.leftTop, power); setMotorSpeed(drive.leftBottom, power)
#define setRightDriveMotors(power) setMotorSpeed(drive.rightTop, power); setMotorSpeed(drive.rightBottom, power)

#define setAllDriveMotorsRaw(power) motor[drive.leftTop] = power; motor[drive.leftBottom] = power; motor[drive.rightTop] = power; motor[drive.rightBottom] = power
#define setLeftDriveMotorsRaw(power) motor[drive.leftTop] = power; motor[drive.leftBottom] = power
#define setRightDriveMotorsRaw(power) motor[drive.rightTop] = power; motor[drive.rightBottom] = power

#if defined(DRIVE_USING_QUADRATURE_ENCODERS)
#ifdef DRIVE_USING_GYRO

//Drive representation
typedef struct fourMotorTankDrive
{
	driveMotor *leftTop;
	driveMotor *leftBottom;
	driveMotor *rightTop;
	driveMotor *rightBottom;
	tSensors leftQuad;
	tSensors rightQuad;
	tSensors gyro;
	int joyThreshold;
} fourMotorTankDrive;

//Drive representation allocation
static fourMotorTankDrive drive;

#else //#ifdef DRIVE_USING_GYRO

//Drive representation
typedef struct fourMotorTankDrive
{
	driveMotor *leftTop;
	driveMotor *leftBottom;
	driveMotor *rightTop;
	driveMotor *rightBottom;
	tSensors leftQuad;
	tSensors rightQuad;
	int joyThreshold;
} fourMotorTankDrive;

//Drive representation allocation
static fourMotorTankDrive drive;

#endif //#ifdef DRIVE_USING_GYRO

#elif defined(DRIVE_USING_INTEGRATED_MOTOR_ENCODERS) //#if defined(DRIVE_USING_QUADRATURE_ENCODERS)
#ifdef DRIVE_USING_GYRO

//Drive representation
typedef struct fourMotorTankDrive
{
	driveMotor *leftTop;
	driveMotor *leftBottom;
	driveMotor *rightTop;
	driveMotor *rightBottom;
	tSensors gyro;
	int joyThreshold;
} fourMotorTankDrive;

//Drive representation allocation
static fourMotorTankDrive drive;

#else //#ifdef DRIVE_USING_GYRO

//Drive representation
typedef struct fourMotorTankDrive
{
	driveMotor *leftTop;
	driveMotor *leftBottom;
	driveMotor *rightTop;
	driveMotor *rightBottom;
	int joyThreshold;
} fourMotorTankDrive;

//Drive representation allocation
static fourMotorTankDrive drive;

#endif //#ifdef DRIVE_USING_GYRO

#else //#if defined(DRIVE_USING_QUADRATURE_ENCODERS)
#ifdef DRIVE_USING_GYRO

//Drive representation
typedef struct fourMotorTankDrive
{
	driveMotor *leftTop;
	driveMotor *leftBottom;
	driveMotor *rightTop;
	driveMotor *rightBottom;
	tSensors gyro;
	int joyThreshold;
} fourMotorTankDrive;

//Drive representation allocation
static fourMotorTankDrive drive;

#else //#ifdef DRIVE_USING_GYRO

//Drive representation
typedef struct fourMotorTankDrive
{
	driveMotor *leftTop;
	driveMotor *leftBottom;
	driveMotor *rightTop;
	driveMotor *rightBottom;
	int joyThreshold;
} fourMotorTankDrive;

//Drive representation allocation
static fourMotorTankDrive drive;

#endif //#ifdef DRIVE_USING_GYRO
#endif //#if defined(DRIVE_USING_QUADRATURE_ENCODERS)

/*
* Sets the motors for the drive
*/
#if defined(DRIVE_USING_QUADRATURE_ENCODERS)
#ifdef DRIVE_USING_GYRO

void setDrive(driveMotor *leftTop, driveMotor *leftBottom, driveMotor *rightTop, driveMotor *rightBottom, tSensors leftQuad, tSensors rightQuad, tSensors gyro, int joyThreshold)
{
	drive.leftTop = leftTop;
	drive.leftBottom = leftBottom;
	drive.rightTop = rightTop;
	drive.rightBottom = rightBottom;
	drive.leftQuad = leftQuad;
	drive.rightQuad = rightQuad;
	drive.gyro = gyro;
	drive.joyThreshold = joyThreshold;
}

#else //#ifdef DRIVE_USING_GYRO

void setDrive(driveMotor *leftTop, driveMotor *leftBottom, driveMotor *rightTop, driveMotor *rightBottom, tSensors leftQuad, tSensors rightQuad, int joyThreshold)
{
	drive.leftTop = leftTop;
	drive.leftBottom = leftBottom;
	drive.rightTop = rightTop;
	drive.rightBottom = rightBottom;
	drive.leftQuad = leftQuad;
	drive.rightQuad = rightQuad;
	drive.joyThreshold = joyThreshold;
}

#endif DRIVE_USING_GYRO //#ifdef DRIVE_USING_GYRO
#elif defined(DRIVE_USING_INTEGRATED_MOTOR_ENCODERS) //#if defined(DRIVE_USING_QUADRATURE_ENCODERS)
#ifdef DRIVE_USING_GYRO

void setDrive(driveMotor *leftTop, driveMotor *leftBottom, driveMotor *rightTop, driveMotor *rightBottom, tSensors gyro, int joyThreshold)
{
	drive.leftTop = leftTop;
	drive.leftBottom = leftBottom;
	drive.rightTop = rightTop;
	drive.rightBottom = rightBottom;
	drive.gyro = gyro;
	drive.joyThreshold = joyThreshold;
}

#else //#ifdef DRIVE_USING_GYRO

void setDrive(driveMotor *leftTop, driveMotor *leftBottom, driveMotor *rightTop, driveMotor *rightBottom, int joyThreshold)
{
	drive.leftTop = leftTop;
	drive.leftBottom = leftBottom;
	drive.rightTop = rightTop;
	drive.rightBottom = rightBottom;
	drive.joyThreshold = joyThreshold;
}

#endif //#ifdef DRIVE_USING_GYRO
#else //#if defined(DRIVE_USING_QUADRATURE_ENCODERS)
#ifdef DRIVE_USING_GYRO

void setDrive(driveMotor *leftTop, driveMotor *leftBottom, driveMotor *rightTop, driveMotor *rightBottom, tSensors gyro, int joyThreshold)
{
	drive.leftTop = leftTop;
	drive.leftBottom = leftBottom;
	drive.rightTop = rightTop;
	drive.rightBottom = rightBottom;
	drive.gyro = gyro;
	drive.joyThreshold = joyThreshold;
}

#else //#ifdef DRIVE_USING_GYRO

void setDrive(driveMotor *leftTop, driveMotor *leftBottom, driveMotor *rightTop, driveMotor *rightBottom, int joyThreshold)
{
	drive.leftTop = leftTop;
	drive.leftBottom = leftBottom;
	drive.rightTop = rightTop;
	drive.rightBottom = rightBottom;
	drive.joyThreshold = joyThreshold;
}

#endif //#ifdef DRIVE_USING_GYRO
#endif //#if defined(DRIVE_USING_QUADRATURE_ENCODERS)

/*
* Drives for time in milliseconds
*/
void driveTime(const int leftPower, const int rightPower, const int timeMs)
{
	setLeftDriveMotorsRaw(leftPower);      //Set left side to its power
	setRightDriveMotorsRaw(rightPower);    //Set right side to its power
	wait1Msec(timeMs);                     //Wait
	setAllDriveMotorsRaw(0);               //Stop
}

#ifdef DRIVE_USING_QUADRATURE_ENCODERS

/*
* Drives for distance in units (default: inches)
*/
void driveQuad(const int power, const int dist)
{
	SensorValue[drive.leftQuad] = 0;                          //Clear left encoder
	SensorValue[drive.rightQuad] = 0;                         //Clear right encoder

	int ticks = dist / (wheelDiameter * PI) * eDriveTicks;    //Convert distance to encoder ticks
	int rDiff;                                                //Distance between sides
	int rMod;                                                 //10% of power in the direction of rDiff

	//Full power for 60% of ticks
	while (abs(SensorValue[drive.leftQuad]) < ticks * 0.6)
	{
		rDiff = abs(SensorValue[drive.leftQuad]) - abs(SensorValue[drive.rightQuad]);    //Difference between sides
		rMod = sgn(rDiff) * power * 0.1;                                                 //10% of power in the direction of rDiff
		setLeftDriveMotorsRaw(power);                                                    //Directly control left side
		setRightDriveMotorsRaw(power + rMod);                                            //Have right side adjust to keep in tune with left side
	}

	//1/3 power for last 40% of ticks
	while (abs(SensorValue[drive.leftQuad]) < ticks)
	{
		rDiff = abs(SensorValue[drive.leftQuad]) - abs(SensorValue[drive.rightQuad]);    //Difference between sides
		rMod = sgn(rDiff) * power * 0.1;                                                 //10% of power in the direction of rDiff
		setLeftDriveMotorsRaw(power / 3);                                                //Directly control left side
		setRightDriveMotorsRaw((power / 3) + rMod);                                      //Have right side adjust to keep in tune with left side
	}

	driveTime(-1 * (power / 2), -1 * (power / 2), 50);    //Brake at -50% power for a short time to eliminate momentum
	setAllDriveMotorsRaw(0);                              //Stop
}

#endif //#ifdef DRIVE_USING_QUADRATURE_ENCODERS

#ifdef DRIVE_USING_INTEGRATED_MOTOR_ENCODERS

/*
* Drives for distance in units (default: inches)
*/
void driveIME(const int power, const int dist)
{
	nMotorEncoder[drive.leftTop] = 0;                         //Clear left IME
	nMotorEncoder[drive.rightTop] = 0;                        //Clear right IME

	int ticks = dist / (wheelDiameter * PI) * eDriveTicks;    //Convert distance to encoder ticks
	int rDiff;                                                //Distance between sides
	int rMod;                                                 //10% of power in the direction of rDiff

	//Full power for 60% of ticks
	while (abs(nMotorEncoder[drive.leftTop]) < ticks * 0.6)
	{
		rDiff = abs(nMotorEncoder[drive.leftTop]) - abs(nMotorEncoder[drive.rightTop]);    //Difference between sides
		rMod = sgn(rDiff) * power * 0.1;                                                   //10% of power in the direction of rDiff
		setLeftDriveMotorsRaw(power);                                                      //Directly control left side
		setRightDriveMotorsRaw(power + rMod);                                              //Have right side adjust to keep in tune with left side
	}

	//1/3 power for last 40% of ticks
	while (abs(nMotorEncoder[drive.leftTop]) < ticks)
	{
		rDiff = abs(nMotorEncoder[drive.leftTop]) - abs(nMotorEncoder[drive.rightTop]);    //Difference between sides
		rMod = sgn(rDiff) * power * 0.1;                                                   //10% of power in the direction of rDiff
		setLeftDriveMotorsRaw(power / 3);                                                  //Directly control left side
		setRightDriveMotorsRaw((power / 3) + rMod);                                        //Have right side adjust to keep in tune with left side
	}

	driveTime(-1 * (power / 2), -1 * (power / 2), 50);    //Brake at -50% power for a short time to eliminate momentum
	setAllDriveMotorsRaw(0);                              //Stop
}

#endif //#ifdef DRIVE_USING_INTEGRATED_MOTOR_ENCODERS

/*
* Turns for time in milliseconds
*/
void turnTime(const int power, const int timeMs)
{
	setLeftDriveMotorsRaw(power);       //Set left side to its power
	setRightDriveMotorsRaw(-1 * power); //Set right side to its power
	wait1Msec(timeMs);                  //Wait
	setAllDriveMotorsRaw(0);            //Stop
}

#ifdef DRIVE_USING_QUADRATURE_ENCODERS

/*
* Turns for distance in units (default: inches)
*/
void turnQuad(const int power, const int deg)
{
	SensorValue[drive.leftTop] = 0;     //Clear left encoder
	SensorValue[drive.rightTop] = 0;    //Clear right encoder

	int ticks = deg * eDriveTicks;      //Convert degrees to encoder ticks
	int rDiff;                          //Distance between sides
	int rMod;                           //10% of power in the direction of rDiff

	//Full power for 60% of ticks
	while (abs(SensorValue[drive.leftTop]) < ticks * 0.6)
	{
		rDiff = abs(SensorValue[drive.leftTop]) - abs(SensorValue[drive.rightTop]);    //Difference between sides
		rMod = sgn(rDiff) * power * 0.1;                                               //10% of power in the direction of rDiff
		setLeftDriveMotorsRaw(power);                                                  //Directly control left side
		setRightDriveMotorsRaw((-1 * power) - rMod);                                   //Have right side adjust to keep in tune with left side
	}

	//1/3 power for last 40% of ticks
	while (abs(SensorValue[drive.leftQuad]) < ticks)
	{
		rDiff = abs(SensorValue[drive.leftTop]) - abs(SensorValue[drive.rightTop]);    //Difference between sides
		rMod = sgn(rDiff) * power * 0.1;                                               //10% of power in the direction of rDiff
		setLeftDriveMotorsRaw(power / 3);                                              //Directly control left side
		setRightDriveMotorsRaw((-1 * (power * 0.8)) - rMod);                           //Have right side adjust to keep in tune with left side
	}

	turnTime(-1 * (power / 2), 50);    //Brake at -50% power for a short time to eliminate momentum
	setAllDriveMotorsRaw(0);           //Stop
}

#endif //#ifdef DRIVE_USING_QUADRATURE_ENCODERS

#ifdef DRIVE_USING_INTEGRATED_MOTOR_ENCODERS

/*
* Turns for distance in units (default: inches)
*/
void turnIME(const int power, const int deg)
{
	nMotorEncoder[drive.leftTop] = 0;     //Clear left IME
	nMotorEncoder[drive.rightTop] = 0;    //Clear right IME

	int ticks = deg * eDriveTicks;        //Convert degrees to encoder ticks
	int rDiff;                            //Distance between sides
	int rMod;                             //10% of power in the direction of rDiff

	//Full power for 60% of ticks
	while (abs(nMotorEncoder[drive.leftTop]) < ticks * 0.6)
	{
		rDiff = abs(nMotorEncoder[drive.leftTop]) - abs(nMotorEncoder[drive.rightTop]);    //Difference between sides
		rMod = sgn(rDiff) * power * 0.1;                                                   //10% of power in the direction of rDiff
		setLeftDriveMotorsRaw(power);                                                      //Directly control left side
		setRightDriveMotorsRaw((-1 * power) - rMod);                                       //Have right side adjust to keep in tune with left side
	}

	//1/3 power for last 40% of ticks
	while (abs(nMotorEncoder[leftQuad]) < ticks)
	{
		rDiff = abs(nMotorEncoder[drive.leftTop]) - abs(nMotorEncoder[drive.rightTop]);    //Difference between sides
		rMod = sgn(rDiff) * power * 0.1;                                                   //10% of power in the direction of rDiff
		setLeftDriveMotorsRaw(power / 3);                                                  //Directly control left side
		setRightDriveMotorsRaw((-1 * (power * 0.8)) - rMod);                               //Have right side adjust to keep in tune with left side
	}

	turnTime(-1 * (power / 2), 50);    //Brake at -50% power for a short time to eliminate momentum
	setAllDriveMotorsRaw(0);           //Stop
}

#endif //#ifdef DRIVE_USING_INTEGRATED_MOTOR_ENCODERS

#ifdef DRIVE_USING_GYRO

/*
* Turns for distance in degrees
*/
void turnGyro(const int power, const int deg)
{
	SensorValue[drive.gyro] = 0;    //Clear the gyro

	int ticks = deg * 10;           //Scale degrees down to gyro ticks

	//Full power for 60% of ticks
	while (abs(SensorValue[drive.gyro]) < ticks * 0.6)
	{
		setLeftDriveMotorsRaw(power);     //Set the left side to its power
		setRightDriveMotorsRaw(power);    //Set the right side to its power
	}

	//80% power for next 20% of ticks
	while (abs(SensorValue[drive.gyro]) < ticks * 0.8)
	{
		setLeftDriveMotorsRaw(power * 0.8);     //Set the left side to its power
		setRightDriveMotorsRaw(power * 0.8);    //Set the right side to its power
	}

	//40% power for last 20% of ticks
	while (abs(SensorValue[drive.gyro]) < ticks)
	{
		setLeftDriveMotorsRaw(power * 0.4);     //Set the left side to its power
		setRightDriveMotorsRaw(power * 0.4);    //Set the right side to its power
	}

	turnTime(-1 * (power / 2), 50);    //Brake at -50% power for a short time to eliminate momentum
	setAllDriveMotorsRaw(0);           //Stop
}

#endif //#ifdef DRIVE_USING_GYRO

/*
* Gives the driver control over the base via a joystick
*/
task driveJoystickControl()
{
	startTask(motorSlewRateTask);
	
	#ifdef DRIVE_USING_TANK_CONTROL

	int leftV, rightV;

	while (true)
	{
		//Grab values from joystick
		leftV = vexRT[JOY_JOY_LV];
		rightV = vexRT[JOY_JOY_RV];

		//Bound values
		leftV = abs(leftV) < drive.joyThreshold ? 0 : leftV;
		rightV = abs(rightV) < drive.joyThreshold ? 0 : rightV;

		//Assign powers
		setLeftDriveMotors(leftV);
		setRightDriveMotors(rightV);

		wait1Msec(25);
	}

	#endif //#ifdef DRIVE_USING_TANK_CONTROL

	#ifdef DRIVE_USING_ARCADE_CONTROL

	int leftV, leftH;

		while (true)
		{
			//Grab values from joystick
			leftV = vexRT[JOY_JOY_LV];
			leftH = vexRT[JOY_JOY_LH];

			//Bound values
			leftV = abs(leftV) < drive.joyThreshold ? 0 : leftV;
			leftH = abs(leftH) < drive.joyThreshold ? 0 : leftH;

			//Assign powers
			setLeftDriveMotors(leftV - leftH);
			setRightDriveMotors(leftV + leftH);

			wait1Msec(25);
		}

	#endif //#ifdef DRIVE_USING_ARCADE_CONTROL
}

#endif //#ifdef FOUR_MOTOR_TANK_DRIVE

#endif //#ifndef TANKDRIVEFOUR_C_INCLUDED
