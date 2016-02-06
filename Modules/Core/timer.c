#ifndef TIMER_C_INCLUDED
#define TIMER_C_INCLUDED

#include "timer.h"

void timer_Initialize(timer* timer)
{
	timer->firstCalled = nSysTime;
	timer->lastCalled = 0;
}

long timer_GetDT(timer* timer)
{
	long dt = nSysTime - timer->lastCalled;
	timer->lastCalled = nSysTime;
	return dt;
}

long timer_GetStartingTime(timer* timer)
{
	return timer->firstCalled;
}

long timer_GetDTFromStart(timer* timer)
{
	return nSysTime - timer->firstCalled;
}

void timer_PlaceMarker(timer *timer)
{
	timer->mark = nSysTime;
}

long timer_GetDTFromMarker(timer *timer)
{
	return nSysTime - timer->mark;
}

#endif //TIMER_C_INCLUDED
