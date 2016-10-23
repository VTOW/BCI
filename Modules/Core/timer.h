#ifndef BCI_TIMER_H_INCLUDED
#define BCI_TIMER_H_INCLUDED

//Timer struct
typedef struct timer_t
{
  long firstCalled; //Time the timer was initialzied
  long lastCalled;  //Last time in ms the timer was called
  long mark;		//Current time mark
  long hardMark;	//Current hard time mark
  long repeatMark;  //Hard mark used for repeat function
} timer;

/**
 * Intiializes a timer. Timers are based off of nSysTime.
 * @param timer Timer to initialize
 */
void timer_Initialize(timer *timer);

/**
 * Returns the time passed in ms since previous call of this function
 * @param  timer Timer to use
 * @return       Time since last call (ms)
 */
long timer_GetDT(timer *timer);

/**
 * Returns the time the timer was first initialized
 * @param  timer Timer to use
 * @return       When the timer was initialized
 */
long timer_GetStartingTime(timer *timer);

/**
 * Returns the time since the timer was first initialized
 * @param  timer Timer to use
 * @return       Time since the timer was initialized
 */
long timer_GetDTFromStart(timer *timer);

/**
 * Place a time marker. Placing another marker will overwrite the old one.
 * @param timer Timer to use
 */
void timer_PlaceMarker(timer *timer);

/**
 * Place a hard time marker. Placing another marker will be ignored until
 * calling timer_ClearHardMarker()
 * @param timer Timer to use
 */
void timer_PlaceHardMarker(timer *timer);

/**
 * Clears a hard time marker
 * @param timer Timer to use
 */
void timer_ClearHardMarker(timer *timer);

/**
 * Returns time since last time marker
 * @param  timer Timer to use
 * @return       Time since last time marker
 */
long timer_GetDTFromMarker(timer *timer);

/**
 * Returns time since hard time marker
 * @param  timer Timer to use
 * @return       Time since hard time marker
 */
long timer_GetDTFromHardMarker(timer *timer);

/**
 * Returns true when a time period has passed, then resets
 * @param  timer  Timer to use
 * @param  timeMs Time between when this function returns true
 * @return        True if a time span greater than or equal to timeMs has passed
 */
bool timer_Repeat(timer *timer, long timeMs);

#endif //BCI_TIMER_H_INCLUDED
