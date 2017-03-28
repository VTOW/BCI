#ifndef BCI_SUPPRESSWARNING_C_INCLUDED
#define BCI_SUPPRESSWARNING_C_INCLUDED

//This function references every function and task in BCI to get rid of warnings
//It also references itself
void ZQ_KILL_WARNING(void *trash)
{
	#ifdef BCI_USE_BANGBANG
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
	#endif

	#ifdef BCI_USE_EMA_FILTER
		filter_Init_EMA((EMAFilter*)0);
		filter_EMA((EMAFilter*)0,0,0);
	#endif

	#ifdef BCI_USE_DEMA_FILTER
		filter_Init_DEMA((DEMAFilter*)0);
		filter_DEMA((DEMAFilter*)0,0,0,0);
	#endif

	#ifdef BCI_USE_FUA_FILTER
		filter_Init_FUA((FUAFilter*)0);
		filter_FUA((FUAFilter*)0,0);
	#endif

	#ifdef BCI_USE_TUA_FILTER
		filter_Init_TUA((TUAFilter*)0);
		filter_TUA((TUAFilter*)0,0);
	#endif

	#ifdef BCI_USE_BIQUAD_FILTER
		biquadFilter_Initialize((biquadFilter*)0,0,0,0,0);
		biquadFilter_Sample((biquadFilter*)0,0);
	#endif

	#ifdef BCI_USE_MOTORCONTROL
		addMotor((tMotor)0);
		startTask(motorSlewRateTask);
	#endif

	#ifdef BCI_USE_POS_PID
		pos_PID_InitController((pos_PID*)0,(tSensors)0,0,0,0);
		pos_PID_InitController((pos_PID*)0,(tMotor)0,0,0,0);
		pos_PID_InitController((pos_PID*)0,(float*)0,0,0,0);
		pos_PID_SetTargetPosition((pos_PID*)0,0);
		pos_PID_GetError((pos_PID*)0);
		pos_PID_GetOutput((pos_PID*)0);
		pos_PID_StepController((pos_PID*)0);
		pos_PID_StepController((pos_PID*)0,0);
		pos_PID_GetPosition((pos_PID*)0);
		pos_PID_ChangeBias((pos_PID*)0, 0);
		pos_PID_ChangeSensor((pos_PID*)0, (tSensors)0);
		pos_PID_ChangeSensor((pos_PID*)0, (tMotor)0);
		pos_PID_ChangeSensor((pos_PID*)0, (float*)0);
	  pos_PID_ChangeBounds((pos_PID*)0,0,0);
	#endif

	#ifdef BCI_USE_TIMER
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
	#endif

	#ifdef BCI_USE_VEL_PID
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
	#endif

	#ifdef BCI_USE_VEL_TBH
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
	#endif

	ZQ_KILL_WARNING((void*)LED_ON);
	ZQ_KILL_WARNING((void*)vrNoXmiters);

	#ifdef BCI_USE_HEAP
		heap_Init();
		heap_Malloc(0);
		heap_Realloc(0,0,0);
		heap_Expand(0,0,0);
		heap_Get(0);
		heap_Set(0,0);
		heap_Free(0,0);
		heap_Print(0,0);
		heap_PrintStats(0,0);
		heap_ClearFreeFlags(0,0);
		heap_Walk(0,0);
		heap_FindBlock(0,0);
		heap_Shrink(0,0,0);
	#endif

	#ifdef BCI_USE_BLOCK
		block_Initialize((block*)0, 0);
		block_Expand((block*)0, 0);
		block_Get((block*)0, 0);
		block_Set((block*)0, 0,0);
		block_Free((block*)0);
		block_Shrink((block*)0, 0);
	#endif

	#ifdef BCI_USE_ARRAYLIST
		arrayList_Initialize((arrayList*)0);
		arrayList_EnsureCapacity((arrayList*)0, 0);
		arrayList_Size((arrayList*)0);
		arrayList_Get((arrayList*)0, 0);
		arrayList_Set((arrayList*)0, 0, 0);
		arrayList_Add((arrayList*)0, 0);
		arrayList_Remove((arrayList*)0, 0);
	#endif

	#ifdef BCI_USE_MATRIX
		matrix_Initialize((matrix*)0,0,0);
		matrix_Free((matrix*)0);
		matrix_Set((matrix*)0, (float*)0);
		matrix_Set((matrix*)0, 0,0,0);
		matrix_Get( (matrix*)0, 0,0);
		matrix_Copy((matrix*)0,(matrix*)0);
		matrix_AddScalar( (matrix*)0, 0, (matrix*)0);
		matrix_SubtractScalar( (matrix*)0, 0, (matrix*)0);
		matrix_MultiplyByScalar( (matrix*)0, 0, (matrix*)0);
		matrix_DivideByScalar( (matrix*)0, 0, (matrix*)0);
		matrix_RaiseToScalar( (matrix*)0, 0, (matrix*)0);
		matrix_AddMatrix( (matrix*)0, (matrix*)0, (matrix*)0);
		matrix_SubtractMatrix( (matrix*)0, (matrix*)0, (matrix*)0);
		matrix_MultiplyByMatrix( (matrix*)0, (matrix*)0, (matrix*)0);
		matrix_Transpose( (matrix*)0, (matrix*)0);
		matrix_Minors( (matrix*)0, (matrix*)0);
		matrix_Cofactor( (matrix*)0, (matrix*)0);
		matrix_Trace( (matrix*)0);
		matrix_Determinant( (matrix*)0);
		matrix_Invert( (matrix*)0, (matrix*)0);
		matrix_Clear((matrix*)0);
	#endif

	#ifdef BCI_USE_UART
		BCI_UART_ClearDataInBuffer(UART1);
	#endif

	#if defined(BCI_USE_HEAP) || defined(BCI_USE_BLOCK) || defined(BCI_USE_ARRAYLIST) || defined(BCI_USE_MATRIX)
		util_PrintHeapError("");
		util_PrintBlockError("");
		util_PrintArrayListError("");
		util_PrintMatrixError("");
	#endif

	#ifdef BCI_USE_LCDCONTROL
		lcd_newMenu("");
		lcd_newMenu("");
		lcd_setBacklightBlinkRate(0);
		lcd_changeFunction((menu*)0,0);
		lcd_changeMessage((menu*)0, "");
		lcd_getLCDSafetyState();
		lcd_formLevel((menu*)0, (menu*)0);
		lcd_formLevel((menu*)0, (menu*)0, (menu*)02);
		lcd_formLevel((menu*)0, (menu*)0, (menu*)02, (menu*)03);
		lcd_formLevel((menu*)0, (menu*)0, (menu*)02, (menu*)03, (menu*)04);
		lcd_formLevel((menu*)0, (menu*)0, (menu*)02, (menu*)03, (menu*)04, (menu*)05);
		lcd_formLevel((menu*)0, (menu*)0, (menu*)02, (menu*)03, (menu*)04, (menu*)05, (menu*)06);
		lcd_formLevel((menu*)0, (menu*)0);
		lcd_putMenuInRow((menu*)0, (menu*)0);
		lcd_linkMenus((menu*)0, (menu*)0);
		lcd_linkMenus((menu*)0, (menu*)0, (menu*)0);
		lcd_linkMenus((menu*)0, (menu*)0, (menu*)0, (menu*)0);
		lcd_linkMenus((menu*)0, (menu*)0, (menu*)0, (menu*)0, (menu*)0);
		lcd_linkMenus((menu*)0, (menu*)0, (menu*)0, (menu*)0, (menu*)0, (menu*)0);
		lcd_linkMenus((menu*)0, (menu*)0, (menu*)0, (menu*)0, (menu*)0, (menu*)0, (menu*)0);
		lcd_linkMenus((menu*)0);
		startTask(lcdControlTask);
	#endif

	sp_Translate((statePack*)0, 0, 0);
	sp_Rotate((statePack*)0, 0);
	sp_Rotate_Point((statePack*)0, 0, 0, 0);
}

#endif //BCI_SUPPRESSWARNING_C_INCLUDED
