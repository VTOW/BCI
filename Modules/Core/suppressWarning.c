#ifndef BCI_SUPPRESSWARNING_C_INCLUDED
#define BCI_SUPPRESSWARNING_C_INCLUDED

//This function references every function and task in BCI to get rid of warnings
//It also references itself
void ZQ_KILL_WARNING(void *trash)
{
	bangBang_InitController((bangBang*)0,(tSensors)0,0,0);
	bangBang_InitController((bangBang*)0,(tMotor)0,0,0);
	bangBang_InitController((bangBang*)0,(float*)0,0,0);
	bangBang_SetFilterConstants((bangBang*)0,0,0);
	bangBang_SetTargetVelocity((bangBang*)0,0);
	bangBang_GetError((bangBang*)0);
	bangBang_GetVelocity((bangBang*)0);
	bangBang_GetTargetVelocity((bangBang*)0);
	bangBang_GetOutput((bangBang*)0);
	bangBang_StepVelocity((bangBang*)0);
	bangBang_StepController((bangBang*)0);

	filter_Init_EMA((EMAFilter*)0);
	filter_EMA((EMAFilter*)0,0,0);
	filter_Init_DEMA((DEMAFilter*)0);
	filter_DEMA((DEMAFilter*)0,0,0,0);
	filter_Init_FUA((FUAFilter*)0);
	filter_FUA((FUAFilter*)0,0);
	filter_Init_TUA((TUAFilter*)0);
	filter_TUA((TUAFilter*)0,0);

	addMotor((tMotor)0);
	startTask(motorSlewRateTask);

	pos_PID_InitController((pos_PID*)0,(tSensors)0,0,0,0);
	pos_PID_InitController((pos_PID*)0,(tMotor)0,0,0,0);
	pos_PID_InitController((pos_PID*)0,(float*)0,0,0,0);
	pos_PID_SetTargetPosition((pos_PID*)0,0);
	pos_PID_GetError((pos_PID*)0);
	pos_PID_GetOutput((pos_PID*)0);
	pos_PID_StepController((pos_PID*)0);
	pos_PID_StepController((pos_PID*)0,0);
	pos_PID_GetPosition((pos_PID*)0);

	timer_Initialize((timer*)0);
	timer_GetDT((timer*)0);
	timer_GetStartingTime((timer*)0);
	timer_GetDTFromStart((timer*)0);
	timer_PlaceMarker((timer*)0);
	timer_PlaceHardMarker((timer*)0);
	timer_ClearHardMarker((timer*)0);
	timer_GetDTFromMarker((timer*)0);
	timer_GetDTFromHardMarker((timer*)0);
	timer_Repeat((timer*)0,0);

	dumpLevels();
	printnVexRCRecieveState();
	startTask(printBatteryVoltage);

	vel_PID_InitController((vel_PID*)0,(tSensors)0,0,0);
	vel_PID_InitController((vel_PID*)0,(tMotor)0,0,0);
	vel_PID_InitController((vel_PID*)0,(float*)0,0,0);
	vel_PID_SetFilterConstants((vel_PID*)0,0,0);
	vel_PID_SetTargetVelocity((vel_PID*)0,0);
	vel_PID_GetError((vel_PID*)0);
	vel_PID_GetOutput((vel_PID*)0);
	vel_PID_StepVelocity((vel_PID*)0);
	vel_PID_StepController((vel_PID*)0);
	vel_PID_StepController((vel_PID*)0,0);
	vel_PID_GetVelocity((vel_PID*)0);

	vel_TBH_InitController((vel_TBH*)0,(tSensors)0,0,0);
	vel_TBH_InitController((vel_TBH*)0,(tMotor)0,0,0);
	vel_TBH_InitController((vel_TBH*)0,(float*)0,0,0);
	vel_TBH_ReInitController((vel_TBH*)0);
	vel_TBH_SetFilterConstants((vel_TBH*)0,0,0);
	vel_TBH_SetTargetVelocity((vel_TBH*)0,0);
	vel_TBH_GetError((vel_TBH*)0);
	vel_TBH_GetVelocity((vel_TBH*)0);
	vel_TBH_GetTargetVelocity((vel_TBH*)0);
	vel_TBH_GetOutput((vel_TBH*)0);
	vel_TBH_SetOpenLoopApprox((vel_TBH*)0,0);
	vel_TBH_GetOpenLoopApprox((vel_TBH*)0);
	vel_TBH_StepVelocity((vel_TBH*)0);
	vel_TBH_StepController((vel_TBH*)0);

	ZQ_KILL_WARNING((void*)LED_ON);
	ZQ_KILL_WARNING((void*)vrNoXmiters);

	#ifdef BCI_USE_PID_OPT
	 PID_Opt_DriveStraight((tMotor*)0,(tMotor*)0,0,(long*)0,(long*)0,0);
	#endif

	#ifdef BCI_USE_HEAP
		heap_init();
		heap_malloc(0);
		heap_free(0,0);
		heap_print(0,0);
		heap_printStats(0,0);
	#endif
}

#endif //BCI_SUPPRESSWARNING_C_INCLUDED
