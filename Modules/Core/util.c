#ifndef UTIL_C_INCLUDED
#define UTIL_C_INCLUDED

#include "util.h"

/*
* Dumps all current motor and sensor values to the debug stream
*/
void dumpLevels()
{
	unsigned int i;

	//Print motors
	for (i = 0; i < kNumbOfTotalMotors; i++)
	{
		writeDebugStreamLine("motor port %d: %d", i + 1, motor[i]);
	}

	//Print analog sensors
	for (i = 0; i < kNumbAnalogSensors; i++)
	{
		writeDebugStreamLine("analog port %d: %d", i + 1, SensorValue[i]);
	}

	//Print digital sensors
	for (; i < kNumbDigitalSensors + 7; i++)
	{
		writeDebugStreamLine("digital port %d: %d", i - 7, SensorValue[i]);
	}
}

/*
* Prints which transmitters are connected, if the competition switch is connected, and which mode the competition is in
*/
void printnVexRCRecieveState()
{
	//Print transmitters
	if (nVexRCReceiveState & vrXmit1)
	{
		writeDebugStreamLine("Transmitter 1 is connected");
	}
	else if (nVexRCReceiveState & vrXmit2)
	{
		writeDebugStreamLine("Transmitter 2 is connected");
	}
	else if ((nVexRCReceiveState & (vrXmit1 | vrXmit2)) == (vrXmit1 | vrXmit2))
	{
		writeDebugStreamLine("Transmitter 1 and 2 are connected");
	}

	//Print competition switch
	if (nVexRCReceiveState & vrCompetitionSwitch)
	{
		writeDebugStreamLine("Competition switch is connected");
	}
	else
	{
		writeDebugStreamLine("Competition switch is not connected");
	}

	//Print competition mode
	if (nVexRCReceiveState & vrDisabled)
	{
		writeDebugStreamLine("Robot is disabled");
	}
	else if (nVexRCReceiveState & vrAutonomousMode)
	{
		writeDebugStreamLine("Robot is in autonomous mode");
	}
	else
	{
		writeDebugStreamLine("Robot is in driver control mode");
	}
}

task printBatteryVoltage
{
	while (true)
	{
		writeDebugStream("%1.2f%c", nImmediateBatteryLevel / 1000.0, '\n');
		wait1Msec(10000);
	}
}

#endif //#ifndef UTIL_C_INCLUDED
