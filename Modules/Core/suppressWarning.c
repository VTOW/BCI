#ifndef SUPPRESSWARNING_C_INCLUDED
#define SUPPRESSWARNING_C_INCLUDED

void ZQ_KILL_WARNING()
{
	bangBang_InitController();
	bangBang_SetFilterConstants();
	bangBang_SetTargetVelocity();
	bangBang_GetError(null);
	bangBang_GetVelocity();
	bangBang_GetTargetVelocity();
	bangBang_GetOutput();
	bangBang_StepVelocity();

	ZQ_KILL_WARNING();
}

#endif //SUPPRESSWARNING_C_INCLUDED
