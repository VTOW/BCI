#ifndef DRIVE_H_INCLUDED
#define DRIVE_H_INCLUDED

#include "../Core/motorControl.c"

//Two motor tank drive
typedef struct driveBundle_t
{
  //Left side
  tMotor leftMotor;

  //Right side
  tMotor rightMotor;
} twoMotorTankDrive;

//Four motor tank drive
typedef struct driveBundle_t
{
  //Left side
  tMotor leftTopMotor, leftBottomMotor;

  //Right side
  tMotor rightTopMotor, rightBottomMotor;
} fourMotorTankDrive;

//Six motor tank drive
typedef struct driveBundle_t
{
  //Left side
  tMotor leftTopMotor, leftMiddleMotor, leftBottomMotor;

  //Right side
  tMotor rightTopMotor, rightMiddleMotor, rightBottomMotor;
} sixMotorTankDrive;

//Eight motor tank drive
typedef struct driveBundle_t
{
  //Left side
  tMotor leftTopMotor, leftUpperMiddleMotor, leftLowerMiddleMotor, leftBottomMotor;

  //Right side
  tMotor rightTopMotor, rightUpperMiddleMotor, rightLowerMiddleMotor, rightBottomMotor;
} eightMotorTankDrive;

//Five motor h drive
typedef struct driveBundle_t
{
  //Left side
  tMotor leftTopMotor, leftBottomMotor;

  //Right side
  tMotor rightTopMotor, rightBottomMotor;

  //Middle
  tMotor middleMotor;
} fiveMotorHDrive;

//Four motor x drive
typedef struct driveBundle_t
{
  //Left side
  tMotor leftTopMotor, leftBottomMotor;

  //Right side
  tMotor rightTopMotor, rightBottomMotor;
} fourMotorXDrive;

//Four motor mecanum drive
typedef struct driveBundle_t
{
  //Left side
  tMotor leftTopMotor, leftBottomMotor;

  //Right side
  tMotor rightTopMotor, rightBottomMotor;
} fourMotorMecanumDrive;

//Eight motor mecanum drive
typedef struct driveBundle_t
{
  //Left side
  tMotor leftTopMotor, leftBottomMotor;

  //Right side
  tMotor rightTopMotor, rightBottomMotor;
} eightMotorMecanumDrive;

#endif //DRIVE_H_INCLUDED
