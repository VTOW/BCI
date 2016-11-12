#ifndef BCI_DRIVESTRAIGHT_C_INCLUDED
#define BCI_DRIVESTRAIGHT_C_INCLUDED

bool PID_Opt_DriveStraight(const int distance, tMotor *leftMotors, tMotor *rightMotors, const unsigned int numMotors, const tSensors leftSensor, const tSensors rightSensor, pos_PID *distancePID, pos_PID *anglePID)
{
	//Save left and right quad values instead of setting them to zero
	const float encoderLeft = SensorValue[leftSensor], encoderRight = SensorValue[rightSensor];

	//Total distance elapsed since start and total angle change since start
	float distanceElapsed = 0, angleChange = 0;
	pos_PID_ChangeSensor(distancePID, &distanceElapsed);
	pos_PID_ChangeSensor(anglePID, &angleChange);

	//Target distance for the distance PID controller
	//Angle PID controller's target is 0
	const int targetDistance = distance;
	pos_PID_SetTargetPosition(distancePID, targetDistance);
	pos_PID_SetTargetPosition(anglePID, 0);

	//If distance PID controller is at target
	bool atTarget = false;

	//Distance that is "close enough" to target
	const int atTargetDistance = 5;

	//Timer for being at target
	timer atTargetTimer;
	timer_Initialize(&atTargetTimer);

	//Timeout period (ms)
	const int timeoutPeriod = 250;

	//Current left and right quad displacements
	float currentLeft, currentRight;

	//Distance and angle PID output
	int distOutput, angleOutput;

	//Loop index
	unsigned int i = 0;

	while (!atTarget)
	{
		//Calculate distance displacement
		currentLeft = SensorValue[leftSensor] - encoderLeft;
		currentRight = SensorValue[rightSensor] - encoderRight;

		//Overall displacement is the average of left and right displacements
		distanceElapsed = (currentLeft + currentRight) / 2.0;

		//Angle change doesn't need to be a real angle, just the difference in displacements
		angleChange = currentRight - currentLeft;

		//Get output from both PID's
		distOutput = pos_PID_StepController(distancePID);
		angleOutput = pos_PID_StepController(anglePID);

		//Set motors to distance PID output with correction from angle PID
		for (i = 0; i < numMotors; i++)
		{
			motor[*(leftMotors + i)] = distOutput + angleOutput;
			motor[*(rightMotors + i)] = distOutput - angleOutput;
		}

		//Place mark if we're close enough to the target distance
		if (fabs(targetDistance - distanceElapsed) <= atTargetDistance)
		{
			timer_PlaceHardMarker(&atTargetTimer);
		}
		else
		{
			timer_ClearHardMarker(&atTargetTimer);
		}

		//If we've been close enough for long enough, we're there
		if (timer_GetDTFromHardMarker(&atTargetTimer) >= timeoutPeriod)
		{
			atTarget = true;
		}
	}

	for (i = 0; i < numMotors; i++)
		{
			motor[*(leftMotors + i)] = 0;
			motor[*(rightMotors + i)] = 0;
		}

	return true;
}

#endif //BCI_DRIVESTRAIGHT_C_INCLUDED
