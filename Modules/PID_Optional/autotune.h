#ifndef AUTOTUNE_H_INCLUDED
#define AUTOTUNE_H_INCLUDED

//Function header for the user-implemented version which runs the plant
void runPlant();

//An autotuned PID controller
typedef struct autotune_pos_PID_t
{
	pos_PID pid;
	tSensors sensor;

	bool didOvershootLastCorrection;
	float adjustmentAmount;
	int decimalPlaces;
	
	float pAdjustment;
	float pAdjustment_prev;
	
	float iAdjustment;
	
	float dAdjustment;

	int iterationCount;
} autotune_pos_PID;

//Initializes the autotuner
void autotune_Init(autotune_pos_PID *apid, const tSensors sensor, const float kP_Initial = 1.0, const float kI_Initial = 0.0, const float kD_Initial = 0.0);

//Runs the autotuner
void autotune_Run(autotune_pos_PID *apid);

#endif //AUTOTUNE_H_INCLUDED
