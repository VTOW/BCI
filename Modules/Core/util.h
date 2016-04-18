#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

//Enum for cortex states
typedef enum
{
	vrNoXmiters =         0,    //No transmitters connected
	vrXmit1 =             0x01, //1 == Transmitter 1 connected
	vrXmit2 =             0x02, //1 == Transmitter 2 connected
	vrBit2 =              0x04, //Unused
	vrCompetitionSwitch = 0x08, //0 == No Comp Switch, 1 == Competition Switch attached
	vrResetSlave =        0x10, //Unused
	vrGameController =    0x20, //0 == Legacy75MHz, 1 == Game Controller
	vrAutonomousMode =    0x40, //0 == Driver Control, 1 == Autonomous Mode
	vrDisabled =          0x80  //0 == Enabled, 1 == Disabled
} TVexRecieverState;

//Enum for LED states
typedef enum
{
	LED_ON = 0,
	LED_OFF = 1
} LEDState;

//Converts an analog in value to millivolts
#define ANALOG_IN_TO_V 286.0

//IME high torque ticks per rev
#define UTIL_IME_HT_TPR 627.2

//IME high speed ticks per rev
#define UTIL_IME_HS_TPR 392.0

//IME turbo gear ticks per rev
#define UTIL_IME_TG_TPR 261.333

//Quad encoder ticks per rev
#define UTIL_QUAD_TPR 360.0

//Wait for a value to become zero
#define waitForZero(val) while(val != 0) { wait1Msec(1); }

//Wait for any LCD button to be pressed
#define waitForLCDPress() while(nLCDButtons == 0) { wait1Msec(1); }

//Wait for all LCD buttons to be released
#define waitForLCDRelease() while(nLCDButtons != 0) { wait1Msec(1); }

//Dumps all current motor and sensor values to the debug stream
void dumpLevels();

//Prints which transmitters are connected, if the competition switch is connected, and which mode the competition is in
void printnVexRCRecieveState();

//Prints the current main battery voltage every 10 seconds
task printBatteryVoltage();

#endif //UTIL_H_INCLUDED
