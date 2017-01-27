#ifndef BCI_TIMER_C_INCLUDED
#define BCI_TIMER_C_INCLUDED

#include "timer.h"

void timer_Initialize(timer *timer)
{
	timer->firstCalled = nSysTime;
	timer->lastCalled = 0;
	timer->mark = 0;
	timer->hardMark = -1;
	timer->repeatMark = -1;
}

long timer_GetDT(timer *timer)
{
	long dt = nSysTime - timer->lastCalled;
	timer->lastCalled = nSysTime;
	return dt;
}

long timer_GetStartingTime(timer *timer)
{
	return timer->firstCalled;
}

long timer_GetDTFromStart(timer *timer)
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
	return timer->mark == -1 ? 0 : nSysTime - timer->mark;
}

long timer_GetDTFromHardMarker(timer *timer)
{
	return timer->hardMark == -1 ? 0 : nSysTime - timer->hardMark;
}

bool timer_Repeat(timer *timer, long timeMs)
{
	if (timer->repeatMark == -1)
	{
		timer->repeatMark = nSysTime;
	}

	if (nSysTime - timer->repeatMark >= timeMs)
	{
		timer->repeatMark = -1;
		return true;
	}

	return false;
}

#endif //BCI_TIMER_C_INCLUDED
