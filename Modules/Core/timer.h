#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

//Timer struct
typedef struct timer
{
  long firstCalled; //Time the timer was initialzied
  long lastCalled;  //Last time in ms the timer was called
  long mark;		//Current time mark
} timer;

//Intiialize a timer
void timer_Initialize(timer *timer);

//Get time passed in ms since previous call of this function
long timer_GetDT(timer *timer);

//Get the timer the timer was first initialized
long timer_GetStartingTime(timer *timer);

//Get the time since the timer was first initialized
long timer_GetDTFromStart(timer *timer);

//Place a time marker
void timer_PlaceMarker(timer *timer);

//Get time since last time marker
long timer_GetDTFromMarker(timer *timer);

#endif //TIMER_H_INCLUDED
