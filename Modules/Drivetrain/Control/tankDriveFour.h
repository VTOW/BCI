#ifndef TANKDRIVEFOUR_H_INCLUDED
#define TANKDRIVEFOUR_H_INCLUDED

#ifdef FOUR_MOTOR_TANK_DRIVE

//Sets the motors and the sensors for the drive
#if defined(DRIVE_USING_QUADRATURE_ENCODERS)
#ifdef DRIVE_USING_GYRO

void setDrive(driveMotor *leftTop, driveMotor *leftBottom, driveMotor *rightTop, driveMotor *rightBottom, tSensors leftQuad, tSensors rightQuad, tSensors gyro, int joyThreshold);

#else //#ifdef DRIVE_USING_GYRO

void setDrive(driveMotor *leftTop, driveMotor *leftBottom, driveMotor *rightTop, driveMotor *rightBottom, tSensors leftQuad, tSensors rightQuad, int joyThreshold);

#endif DRIVE_USING_GYRO //#ifdef DRIVE_USING_GYRO
#elif defined(DRIVE_USING_INTEGRATED_MOTOR_ENCODERS) //#if defined(DRIVE_USING_QUADRATURE_ENCODERS)
#ifdef DRIVE_USING_GYRO

void setDrive(driveMotor *leftTop, driveMotor *leftBottom, driveMotor *rightTop, driveMotor *rightBottom, tSensors gyro, int joyThreshold);

#else //#ifdef DRIVE_USING_GYRO

void setDrive(driveMotor *leftTop, driveMotor *leftBottom, driveMotor *rightTop, driveMotor *rightBottom, int joyThreshold);

#endif //#ifdef DRIVE_USING_GYRO
#else //#if defined(DRIVE_USING_QUADRATURE_ENCODERS)
#ifdef DRIVE_USING_GYRO

void setDrive(driveMotor *leftTop, driveMotor *leftBottom, driveMotor *rightTop, driveMotor *rightBottom, tSensors gyro, int joyThreshold);

#else //#ifdef DRIVE_USING_GYRO

void setDrive(driveMotor *leftTop, driveMotor *leftBottom, driveMotor *rightTop, driveMotor *rightBottom, int joyThreshold);

#endif //#ifdef DRIVE_USING_GYRO
#endif //#if defined(DRIVE_USING_QUADRATURE_ENCODERS)

//Drives for time in milliseconds
void driveTime(const int leftPower, const int rightPower, const int timeMs);

#ifdef DRIVE_USING_QUADRATURE_ENCODERS

//Drives for distance in units (default: inches)
void driveQuad(const int power, const int dist);

#endif //#ifdef DRIVE_USING_QUADRATURE_ENCODERS

#ifdef DRIVE_USING_INTEGRATED_MOTOR_ENCODERS

//Drives for distance in units (default: inches)
void driveIME(const int power, const int dist);

#endif //#ifdef DRIVE_USING_INTEGRATED_MOTOR_ENCODERS

//Turns for time in milliseconds
void turnTime(const int power, const int timeMs);

#ifdef DRIVE_USING_QUADRATURE_ENCODERS

//Turns for distance in units (default: inches)
void turnQuad(const int power, const int deg);

#endif //#ifdef DRIVE_USING_QUADRATURE_ENCODERS

#ifdef DRIVE_USING_INTEGRATED_MOTOR_ENCODERS

//Turns for distance in units (default: inches)
void turnIME(const int power, const int deg);

#endif //#ifdef DRIVE_USING_INTEGRATED_MOTOR_ENCODERS

#ifdef DRIVE_USING_GYRO

//Turns for distance in degrees
void turnGyro(const int power, const int deg);

#endif //#ifdef DRIVE_USING_GYRO

//Gives the driver control over the base via a joystick
task driveJoystickControl();

#endif //#ifdef FOUR_MOTOR_TANK_DRIVE

#endif //#ifndef TANKDRIVEFOUR_H_INCLUDED
