#ifndef BCI_MOTORCONTROL_C_INCLUDED
#define BCI_MOTORCONTROL_C_INCLUDED

#include "motorControl.h"

//Array for motors
static driveMotor driveMotors[MOTOR_NUM];

/*
* Adds and initializes a motor (by name) to the motor array
*/
driveMotor* addMotor(const tMotor name, float slewRate)
{
	//Grab a spot in the motor array which
	//corresponds with which port the
	//physical motor is plugged into
	driveMotor *m = &(driveMotors[name]);

	m->reqSpeed = 0;
	m->artSpeed = 0;
	m->slew = slewRate;
	m->active = true;
	return m;
}

/*
* Updates the power of each motor to meet the requested power
*/
task motorSlewRateTask()
{
	//Index of current motor
	unsigned int motorIndex;
	//Requested speed of current motor
	int motorTmpReq;
	//Artificial speed of current motor
	float motorTmpArtSpd;
	//Current motor
	driveMotor *currentMotor;

	while (true)
	{
		//Batch motor power update
		for (motorIndex = 0; motorIndex < MOTOR_NUM; motorIndex++)
		{
			//Assign the driveMotor at motorIndex to currentMotor and
			//check the active flag: if the motor is not active,
		  //do not let the controller update the motor's power by
		  //skipping that motor's update cycle
			if (!(currentMotor = &(driveMotors[motorIndex]))->active)
			{
				continue;
			}

			//Keep internal memory access to a minimum
			motorTmpArtSpd = currentMotor->artSpeed;
			motorTmpReq = currentMotor->reqSpeed;

			//If the motor value needs to change
			if (motorTmpArtSpd != motorTmpReq)
			{
				//Increase motor value
				if (motorTmpReq > motorTmpArtSpd)
				{
					motorTmpArtSpd += currentMotor->slew;

					//Limit speed
					motorTmpArtSpd = motorTmpArtSpd > motorTmpReq ? motorTmpReq : motorTmpArtSpd;
				}

				//Decrease motor value
				if (motorTmpReq < motorTmpArtSpd)
				{
					motorTmpArtSpd -= currentMotor->slew;

					//Limit speed
					motorTmpArtSpd = motorTmpArtSpd < motorTmpReq ? motorTmpReq : motorTmpArtSpd;
				}

				//Bound speed
				motorTmpArtSpd = motorTmpArtSpd > MOTOR_MAX_VALUE ? MOTOR_MAX_VALUE : motorTmpArtSpd;
				motorTmpArtSpd = motorTmpArtSpd < MOTOR_MIN_VALUE ? MOTOR_MIN_VALUE : motorTmpArtSpd;

				//Send updated speed to motor
				motor[motorIndex] = (int)motorTmpArtSpd;

				//Send updated speed back to current motor
				currentMotor->artSpeed = motorTmpArtSpd;
			}
		}
		wait1Msec(MOTOR_TASK_DELAY);
	}
}

#endif //BCI_MOTORCONTROL_C_INCLUDED
