#ifndef DRIVE_H_INCLUDED
#define DRIVE_H_INCLUDED

#include "../Core/motorControl.c"

//Array for all motors and sensors for the drivetrain
//Indices 0-5 are motors
//Indices 6-9 are quads
//Indices 10-13 are IME's
void* driveBundle[13];

//Drives for time in ms
void driveTime(const int leftPower, const int rightPower, const int timeMs);

//Drives for distance in ticks (Quad based)
void driveQuad(const int power, const int ticks);

//Drives for distance in ticks (Quad based) using PID control
void driveQuad_PID(const int ticks);

//Drives for distance in ticks (IME based)
void driveIME(const int power, const int ticks);

//Drives for distance in ticks (IME based) using PID control
void driveIME_PID(const int ticks);

//Turns for time in ms
void turnTime(const int leftPower, const int rightPower, const int timeMs);

//Turns for distance in ticks (Quad based)
void turnQuad(const int power, const int ticks);

//Turns for distance in ticks (Quad based) using PID control
void turnQuad_PID(const int ticks);

//Turns for distance in ticks (IME based)
void turnIME(const int power, const int ticks);

//Turns for distance in ticks (IME based) using PID control
void turnIME_PID(const int ticks);

//Turns for distance in ticks (Gyro based)
void turnGyro(const int power, const int ticks);

//Turns for distance in ticks (Gyro based) using PID control
void turnGyro_PID(const int ticks);

#endif //DRIVE_H_INCLUDED
