#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

//Timer struct
typedef struct timer
{
  long firstCalled; //Time the timer was initialzied
  long lastCalled;  //Last time in ms the timer was called
  long mark;		//Current time mark
  long hardMark;	//Current hard time mark
  long repeatMark;  //Hard mark used for repeat function
} timer;

//Intiialize a timer
void timer_Initialize(timer *timer);

//Get time passed in ms since previous call of this function
long timer_GetDT(timer *timer);

//Get the time the timer was first initialized
long timer_GetStartingTime(timer *timer);

//Get the time since the timer was first initialized
long timer_GetDTFromStart(timer *timer);

//Place a time marker
void timer_PlaceMarker(timer *timer);

//Place a hard time marker
void timer_PlaceHardMarker(timer *timer);

//Clear a hard time marker
void timer_ClearHardMarker(timer *timer);

//Get time since last time marker
long timer_GetDTFromMarker(timer *timer);

//Get time since hard time marker
long timer_GetDTFromHardMarker(timer *timer);

//Returns true when a time period has passed, then resets
bool timer_Repeat(timer *timer, long timeMs);

#endif //TIMER_H_INCLUDED
