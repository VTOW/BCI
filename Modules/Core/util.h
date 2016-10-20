#ifndef BCI_UTIL_H_INCLUDED
#define BCI_UTIL_H_INCLUDED

//Enum for cortex states
enum TVexRecieverState
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
};

//Enum for LED states
enum LEDState
{
	LED_ON = 0,
	LED_OFF = 1
};

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

#if defined(BCI_SEM_DEBUG)
#define BCI_lockSem(sem, str) writeDebugStreamLine("BCI_lockSem: %d",str);semaphoreLock(sem);if(bDoesTaskOwnSemaphore(sem))
#define BCI_unlockSem(sem, str) writeDebugStreamLine("BCI_unlockSem: %d",str);if(bDoesTaskOwnSemaphore(sem)){semaphoreUnlock(sem);}
#elif defined(BCI_SEM_DEBUG_FULL)
int bci_sem_debug_full_counter;
#define BCI_lockSem(sem, str) bci_sem_debug_full_counter++;if(bci_sem_debug_full_counter != 1){writeDebugStreamLine("BCI_lockSem: overlock at %d", str);}else{writeDebugStreamLine("BCI_lockSem: %d",str);}semaphoreLock(sem);if(bDoesTaskOwnSemaphore(sem))
#define BCI_unlockSem(sem, str) bci_sem_debug_full_counter--;if(bci_sem_debug_full_counter != 0){writeDebugStreamLine("BCI_unlockSem: underlock at %d", str);}else{writeDebugStreamLine("BCI_unlockSem: %d",str);}if(bDoesTaskOwnSemaphore(sem)){semaphoreUnlock(sem);}
#elif defined(BCI_SEM_DEBUG_FULL_OFF)
#define BCI_lockSem(sem, str) semaphoreLock(sem);if(bDoesTaskOwnSemaphore(sem))
#define BCI_unlockSem(sem, str) if(bDoesTaskOwnSemaphore(sem)){semaphoreUnlock(sem);}
#else
#define BCI_lockSem(sem) semaphoreLock(sem);if(bDoesTaskOwnSemaphore(sem))
#define BCI_unlockSem(sem) if(bDoesTaskOwnSemaphore(sem)){semaphoreUnlock(sem);}
#endif //BCI_SEM_DEBUG

//Dumps all current motor and sensor values to the debug stream
void dumpLevels();

//Prints which transmitters are connected, if the competition switch is connected, and which mode the competition is in
void printnVexRCRecieveState();

//Prints the current main battery voltage every 10 seconds
task printBatteryVoltage();

#endif //BCI_UTIL_H_INCLUDED
