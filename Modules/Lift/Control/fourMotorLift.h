#ifndef FOURMOTORLIFT_H_INCLUDED
#define FOURMOTORLIFT_H_INCLUDED

#ifdef FOUR_MOTOR_LIFT

//Sets the motors and the sensors for the drive
#if defined(LIFT_USING_QUADRATURE_ENCODERS)

void setLift(driveMotor *leftTop, driveMotor *leftBottom, driveMotor *rightTop, driveMotor *rightBottom, tSensors leftQuad, tSensors rightQuad, short upVal, short downVal, short holdVal);

#elif defined(LIFT_USING_POTENTIOMETERS) //#if defined(LIFT_USING_QUADRATURE_ENCODERS)

void setLift(driveMotor *leftTop, driveMotor *leftBottom, driveMotor *rightTop, driveMotor *rightBottom, tSensors leftPot, tSensors rightPot, short upVal, short downVal, short holdVal);

#elif defined(LIFT_USING_INTEGRATED_MOTOR_ENCODERS) //#if defined(LIFT_USING_QUADRATURE_ENCODERS)

void setLift(driveMotor *leftTop, driveMotor *leftBottom, driveMotor *rightTop, driveMotor *rightBottom, short upVal, short downVal, short holdVal);

#else //#if defined(LIFT_USING_QUADRATURE_ENCODERS)

void setLift(driveMotor *leftTop, driveMotor *leftBottom, driveMotor *rightTop, driveMotor *rightBottom, short upVal, short downVal, short holdVal);

#endif //#if defined(LIFT_USING_QUADRATURE_ENCODERS)

//Lift for time in milliseconds
void liftTime(const int leftPower, const int rightPower, const int timeMs);

#ifdef LIFT_USING_QUADRATURE_ENCODERS

//Lift for degrees in units (default: quadrature encoder units)
void liftQuad(const int power, const int ticks);

#endif //#ifdef LIFT_USING_QUADRATURE_ENCODERS

#ifdef LIFT_USING_POTENTIOMETERS

//Lift for degrees in units (default: potentiometer ticks)
void liftPot(const int power, const int ticks);

#endif //#ifdef LIFT_USING_POTENTIOMETERS

#ifdef LIFT_USING_INTEGRATED_MOTOR_ENCODERS

//Lift for degrees in units (default: integrated motor encoder ticks)
void liftIME(const int power, const int ticks);

#endif //#ifdef LIFT_USING_INTEGRATED_MOTOR_ENCODERS

//Gives the driver control over the lift via a joystick
task liftJoystickControl();

#endif //#ifdef FOUR_MOTOR_LIFT
#endif //#ifndef FOURMOTORLIFT_H_INCLUDED
