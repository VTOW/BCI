#ifndef TIMER_C_INCLUDED
#define TIMER_C_INCLUDED

#include "timer.h"

void timer_Initialize(timer* timer)
{
	timer->firstCalled = nSysTime;
	timer->lastCalled = 0;
	timer->mark = 0;
	timer->hardMark = -1;
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

void timer_PlaceHardMarker(timer *timer)
{
	if (timer->hardMark == -1)
	{
		timer->hardMark = nSysTime;
	}
}

void timer_ClearHardMarker(timer *timer)
{
	timer->hardMark = -1;
}

long timer_GetDTFromMarker(timer *timer)
{
	return nSysTime - timer->mark;
}

long timer_GetDTFromHardMarker(timer *timer)
{
	return nSysTime - timer->hardMark;
}

#endif //TIMER_C_INCLUDED
