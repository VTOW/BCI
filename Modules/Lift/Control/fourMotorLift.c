#ifndef FOURMOTORLIFT_C_INCLUDED
#define FOURMOTORLIFT_C_INCLUDED

#ifdef FOUR_MOTOR_LIFT

#define setAllLiftMotors(power) setMotorSpeed(lift.leftTop, power); setMotorSpeed(lift.leftBottom, power); setMotorSpeed(lift.rightTop, power); setMotorSpeed(lift.rightBottom, power)
#define setLeftLiftMotors(power) setMotorSpeed(lift.leftTop, power); setMotorSpeed(lift.leftBottom, power)
#define setRightLiftMotors(power) setMotorSpeed(lift.rightTop, power); setMotorSpeed(lift.rightBottom, power)

#include "fourMotorLift.h"
#include "..\..\Core\motorControl.c"
#include "..\..\Core\joystickDefinitions.h"

#if defined(LIFT_USING_QUADRATURE_ENCODERS)

typedef struct fourMotorLift
{
	driveMotor *leftTop;
	driveMotor *leftBottom;
	driveMotor *rightTop;
	driveMotor *rightBottom;
	tSensors leftQuad;
	tSensors rightQuad;
	short upVal;
	short downVal;
	short holdVal;
} fourMotorLift;

//Lift representation allocation
static fourMotorLift lift;

#elif defined(LIFT_USING_POTENTIOMETERS) //#if defined(LIFT_USING_QUADRATURE_ENCODERS)

typedef struct fourMotorLift
{
	driveMotor *leftTop;
	driveMotor *leftBottom;
	driveMotor *rightTop;
	driveMotor *rightBottom;
	tSensors leftPot;
	tSensors rightPot;
	short upVal;
	short downVal;
	short holdVal;
} fourMotorLift;

//Lift representation allocation
static fourMotorLift lift;

#elif defined(LIFT_USING_INTEGRATED_MOTOR_ENCODERS) //#if defined(LIFT_USING_QUADRATURE_ENCODERS)

typedef struct fourMotorLift
{
	driveMotor *leftTop;
	driveMotor *leftBottom;
	driveMotor *rightTop;
	driveMotor *rightBottom;
	short upVal;
	short downVal;
	short holdVal;
} fourMotorLift;

//Lift representation allocation
static fourMotorLift lift;

#else //#if defined(LIFT_USING_QUADRATURE_ENCODERS)

typedef struct fourMotorLift
{
	driveMotor *leftTop;
	driveMotor *leftBottom;
	driveMotor *rightTop;
	driveMotor *rightBottom;
	short upVal;
	short downVal;
	short holdVal;
} fourMotorLift;

//Lift representation allocation
static fourMotorLift lift;

#endif //#if defined(LIFT_USING_QUADRATURE_ENCODERS)

/*
* Sets the motors and the sensors for the drive
*/
#if defined(LIFT_USING_QUADRATURE_ENCODERS)

void setLift(driveMotor *leftTop, driveMotor *leftBottom, driveMotor *rightTop, driveMotor *rightBottom, tSensors leftQuad, tSensors rightQuad, short upVal, short downVal, short holdVal)
{
	lift.leftTop = leftTop;
	lift.leftBottom = leftBottom;
	lift.rightTop = rightTop;
	lift.rightBottom = rightBottom;
	lift.leftQuad = leftQuad;
	lift.rightQuad = rightQuad;
	lift.upVal = upVal;
	lift.downVal = downVal;
	lift.holdVal = holdVal;
}

#elif defined(LIFT_USING_POTENTIOMETERS) //#if defined(LIFT_USING_QUADRATURE_ENCODERS)

void setLift(driveMotor *leftTop, driveMotor *leftBottom, driveMotor *rightTop, driveMotor *rightBottom, tSensors leftPot, tSensors rightPot, short upVal, short downVal, short holdVal)
{
	lift.leftTop = leftTop;
	lift.leftBottom = leftBottom;
	lift.rightTop = rightTop;
	lift.rightBottom = rightBottom;
	lift.leftPot = leftPot;
	lift.rightPot = rightPot;
	lift.upVal = upVal;
	lift.downVal = downVal;
	lift.holdVal = holdVal;
}

#elif defined(LIFT_USING_INTEGRATED_MOTOR_ENCODERS) //#if defined(LIFT_USING_QUADRATURE_ENCODERS)

void setLift(driveMotor *leftTop, driveMotor *leftBottom, driveMotor *rightTop, driveMotor *rightBottom, short upVal, short downVal, short holdVal)
{
	lift.leftTop = leftTop;
	lift.leftBottom = leftBottom;
	lift.rightTop = rightTop;
	lift.rightBottom = rightBottom;
	lift.upVal = upVal;
	lift.downVal = downVal;
	lift.holdVal = holdVal;
}

#else //#if defined(LIFT_USING_QUADRATURE_ENCODERS)

void setLift(driveMotor *leftTop, driveMotor *leftBottom, driveMotor *rightTop, driveMotor *rightBottom, short upVal, short downVal, short holdVal)
{
	lift.leftTop = leftTop;
	lift.leftBottom = leftBottom;
	lift.rightTop = rightTop;
	lift.rightBottom = rightBottom;
	lift.upVal = upVal;
	lift.downVal = downVal;
	lift.holdVal = holdVal;
}

#endif //#if defined(LIFT_USING_QUADRATURE_ENCODERS)

/*
* Lift for time in milliseconds
*/
void liftTime(const int leftPower, const int rightPower, const int timeMs)
{
    setLeftLiftMotors(power);
    setRightLiftMotors(power);
}

#ifdef LIFT_USING_QUADRATURE_ENCODERS

/*
* Lift for degrees in units (default: quadrature encoder units)
*/
void liftQuad(const int power, const int ticks)
{
    int rDiff;    //Distance between sides
    int rMod;     //10% of power in the direction of rDiff
    
    //Full power for 60% of ticks
    while (SensorValue[lift.rightPot] < ticks * 0.6)
    {
        rDiff = SensorValue[lift.rightPot] - SensorValue[lift.leftPot];    //Difference between sides
        rMod = sgn(rDiff) * power * 0.1;                                   //10% of power in the direction of rDiff
        setLeftLiftMotors(power);                                          //Directly control left side
        setRightLiftMotors(power + rMod);                                  //Have right side adjust to keep in tune with left side
    }
    
    //1/3 power for last 40% of ticks
    while (SensorValue[lift.rightPot] < ticks)
    {
        rDiff = SensorValue[lift.rightPot] - SensorValue[lift.leftPot];    //Difference between sides
        rMod = sgn(rDiff) * power * 0.1;                                   //10% of power in the direction of rDiff
        setLeftLiftMotors(power / 3);                                      //Directly control left side
        setRightLiftMotors((power / 3) + rMod);                            //Have right side adjust to keep in tune with left side
    }
    
    liftTime(-1 * (power / 2), -1 * (power / 2), 50);    //Brake at -50% power for a short time to eliminate momentum
    setAllLiftMotors(0);                                 //Stop
}

#endif //#ifdef LIFT_USING_QUADRATURE_ENCODERS

#ifdef LIFT_USING_POTENTIOMETERS

/*
* Lift for degrees in units (default: potentiometer ticks)
*/
void liftPot(const int power, const int ticks)
{
    int rDiff;    //Distance between sides
    int rMod;     //10% of power in the direction of rDiff
    
    //Full power for 60% of ticks
    while (SensorValue[lift.rightPot] < ticks * 0.6)
    {
        rDiff = SensorValue[lift.rightPot] - SensorValue[lift.leftPot];    //Difference between sides
        rMod = sgn(rDiff) * power * 0.1;                                   //10% of power in the direction of rDiff
        setLeftLiftMotors(power);                                          //Directly control left side
        setRightLiftMotors(power + rMod);                                  //Have right side adjust to keep in tune with left side
    }
    
    //1/3 power for last 40% of ticks
    while (SensorValue[lift.rightPot] < ticks)
    {
        rDiff = SensorValue[lift.rightPot] - SensorValue[lift.leftPot];    //Difference between sides
        rMod = sgn(rDiff) * power * 0.1;                                   //10% of power in the direction of rDiff
        setLeftLiftMotors(power / 3);                                      //Directly control left side
        setRightLiftMotors((power / 3) + rMod);                            //Have right side adjust to keep in tune with left side
    }
    
    liftTime(-1 * (power / 2), -1 * (power / 2), 50);    //Brake at -50% power for a short time to eliminate momentum
    setAllLiftMotors(0);                                 //Stop
}

#endif //#ifdef LIFT_USING_POTENTIOMETERS

#ifdef LIFT_USING_INTEGRATED_MOTOR_ENCODERS

/*
* Lift for degrees in units (default: integrated motor encoder ticks)
*/
void liftIME(const int power, const int ticks)
{
    nMotorEncoder[lift.leftTop] = 0;     //Clear left IME
    nMotorEncoder[lift.rightTop] = 0;    //Clear right IME
    
    int rDiff;                           //Distance between sides
    int rMod;                            //10% of power in the direction of rDiff
    
    //Full power for 60% of ticks
    while (nMotorEncoder[lift.rightPot] < ticks * 0.6)
    {
        rDiff = nMotorEncoder[lift.rightTop] - nMotorEncoder[lift.leftTop];    //Difference between sides
        rMod = sgn(rDiff) * power * 0.1;                                       //10% of power in the direction of rDiff
        setLeftLiftMotors(power);                                              //Directly control left side
        setRightLiftMotors(power + rMod);                                      //Have right side adjust to keep in tune with left side
    }
    
    //1/3 power for last 40% of ticks
    while (nMotorEncoder[lift.rightPot] < ticks)
    {
        rDiff = nMotorEncoder[lift.rightTop] - nMotorEncoder[lift.leftTop];    //Difference between sides
        rMod = sgn(rDiff) * power * 0.1;                                       //10% of power in the direction of rDiff
        setLeftLiftMotors(power / 3);                                          //Directly control left side
        setRightLiftMotors((power / 3) + rMod);                                //Have right side adjust to keep in tune with left side
    }
    
    liftTime(-1 * (power / 2), -1 * (power / 2), 50);    //Brake at -50% power for a short time to eliminate momentum
    setAllLiftMotors(0);                                 //Stop
}

#endif //#ifdef LIFT_USING_INTEGRATED_MOTOR_ENCODERS

/*
* Gives the driver control over the lift via a joystick
*/
task liftJoystickControl()
{
	#ifdef LIFT_USING_LEFT_HANDED_CONTROL

	while (true)
	{
		if (vexRT[JOY_TRIG_LU])
		{
			setAllLiftMotors(lift.upVal);
		}
		else if (vexRT[JOY_TRIG_LD])
		{
			setAllLiftMotors(lift.downVal);
		}
		else
		{
			setAllLiftMotors(lift.holdVal);
		}
		
		wait1Msec(25);
	}

	#endif //#ifdef LIFT_USING_LEFT_HANDED_CONTROL

	#ifdef LIFT_USING_RIGHT_HANDED_CONTROL

	while (true)
	{
		if (vexRT[JOY_TRIG_RU])
		{
			setAllLiftMotors(lift.upVal);
		}
		else if (vexRT[JOY_TRIG_RD])
		{
			setAllLiftMotors(lift.downVal);
		}
		else
		{
			//setAllLiftMotors(lift.holdVal);
			setAllLiftMotors(20);
		}
		
		wait1Msec(25);
	}
	
	#endif //#ifdef LIFT_USING_RIGHT_HANDED_CONTROL
}

#endif //#ifdef FOUR_MOTOR_LIFT
#endif //#ifndef FOURMOTORLIFT_C_INCLUDED
