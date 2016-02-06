#ifndef LCDCONTROL_C_INCLUDED
#define LCDCONTROL_C_INCLUDED

//Do nothing with no menus
#ifdef MENU_NUM
#if MENU_NUM > 0

#include "lcdControl.h"
#include "util.h"

//LCD system loop wait time in ms
static int lcdSystemLoopWait = 100;

//Menu for current selection
menu *currentMenu = NULL;

//Array for allocation
static menu menus[MENU_NUM];
static int nextMenu = 0;

//Backlight blink rate (in Hz)
static int backlightBlinkRate = 0;

//Whether or not the game state safety fired
bool lcdGameStateSafetyFired = false;

/*
* Adds and initializes a menu pointer, and adds the menu to the main array
*/
menu* newMenu(const string *msg, const int dispatchFuncVal, const menu *next, const menu *prev, const menu *up, const menu *down)
{
	//Bounds check
	if (nextMenu == MENU_NUM)
	{
		//If outside bounds
		//Make it very obvious to the user
		for (int i = 0; i < MENU_NUM; i++)
		{
			changeMessage(&(menus[i]), INCORRECT_MENU_NUM);
		}
		//Return previously allocated menu
		nextMenu--;
		return &(menus[nextMenu++]);
	}

	//Grab the next menu slot
	//Should be a null menu
	menu *m = &(menus[nextMenu]);
	nextMenu++;

	m->next = next;
	m->prev = prev;
	m->up = up;
	m->down = down;
	m->msg = msg;
	m->dispatchFuncVal = dispatchFuncVal;

	return m;
}

/*
* Sets a blink rate (in Hz) for the lcd backlight
*/
void setBacklightBlinkRate(const int rate)
{
	backlightBlinkRate = rate;
}

/*
* Changes the function a menu has
*/
void changeFunction(menu *m, const int func)
{
	m->dispatchFuncVal = func;
}

/*
* Changes the message a menu has
*/
void changeMessage(const menu *m, const string *newMsg)
{
	m->msg = newMsg;
}

/*
* Returns the current game state safety state
*/
bool getLCDSafetyState()
{
	return lcdGameStateSafetyFired;
}

/*
* Childs 1 menu to a parent
*/
void formLevel(menu *parent, menu *child)
{
	child->up = parent;
	parent->down = child;
}

/*
* Childs 2 menus to a parent
*/
void formLevel(menu *parent, menu *child, menu *child2)
{
	child->up = parent;
	child2->up = parent;
	parent->down = child;
}

/*
* Childs 3 menus to a parent
*/
void formLevel(menu *parent, menu *child, menu *child2, menu *child3)
{
	child->up = parent;
	child2->up = parent;
	child3->up = parent;
	parent->down = child;
}

/*
* Childs 4 menus to a parent
*/
void formLevel(menu *parent, menu *child, menu *child2, menu *child3, menu *child4)
{
	child->up = parent;
	child2->up = parent;
	child3->up = parent;
	child4->up = parent;
	parent->down = child;
}

/*
* Childs 5 menus to a parent
*/
void formLevel(menu *parent, menu *child, menu *child2, menu *child3, menu *child4, menu *child5)
{
	child->up = parent;
	child2->up = parent;
	child3->up = parent;
	child4->up = parent;
	child5->up = parent;
	parent->down = child;
}

/*
* Childs 6 menus to a parent
*/
void formLevel(menu *parent, menu *child, menu *child2, menu *child3, menu *child4, menu *child5, menu *child6)
{
	child->up = parent;
	child2->up = parent;
	child3->up = parent;
	child4->up = parent;
	child5->up = parent;
	child6->up = parent;
	parent->down = child;
}

/*
* Childs n menus to a parent
* Note: This is dependent upon allocation order
*/
void formLevel(menu *parent, menu *startingMenu, const int count)
{
	//Step through memory to get child menus
	for (int i = 0; i < count; i++)
	{
		(startingMenu + i)->up = parent;
	}
	parent->down = startingMenu;
}

/*
* Inserts a menu into a row
*/
void putMenuInRow(menu *m, menu *next, menu *prev)
{
	m->next = next;

	if (prev != NULL)
	{
		m->prev = prev;
	}
}

/*
* Pairs 2 menus
*/
void linkMenus(menu *m1, menu *m2)
{
	m1->next = m2;
	m1->prev = m2;
	m2->next = m1;
	m2->prev = m1;
}

/*
* Pairs 3 menus
*/
void linkMenus(menu *m1, menu *m2, menu *m3)
{
	m1->next = m2;
	m1->prev = m3;
	m2->next = m3;
	m2->prev = m1;
	m3->next = m1;
	m3->prev = m2;
}

/*
* Pairs 4 menus
*/
void linkMenus(menu *m1, menu *m2, menu *m3, menu *m4)
{
	m1->next = m2;
	m1->prev = m4;
	m2->next = m3;
	m2->prev = m1;
	m3->next = m4;
	m3->prev = m2;
	m4->next = m1;
	m4->prev = m3;
}

/*
* Pairs 5 menus
*/
void linkMenus(menu *m1, menu *m2, menu *m3, menu *m4, menu *m5)
{
	m1->next = m2;
	m1->prev = m5;
	m2->next = m3;
	m2->prev = m1;
	m3->next = m4;
	m3->prev = m2;
	m4->next = m5;
	m4->prev = m3;
	m5->next = m1;
	m5->prev = m4;
}

/*
* Pairs 6 menus
*/
void linkMenus(menu *m1, menu *m2, menu *m3, menu *m4, menu *m5, menu *m6)
{
	m1->next = m2;
	m1->prev = m6;
	m2->next = m3;
	m2->prev = m1;
	m3->next = m4;
	m3->prev = m2;
	m4->next = m5;
	m4->prev = m3;
	m5->next = m6;
	m5->prev = m4;
	m6->next = m1;
	m6->prev = m5;
}

/*
* Updates the LCD and responds to button presses
*/
task updateLCDTask()
{
	int oldTime = time1[T4];

	clearLCDLine(0);
	clearLCDLine(1);
	currentMenu = &(menus[0]);                //Start control with first menu
	displayLCDString(0, 0, *menus[0].msg);    //Display first menu
	displayLCDString(1, 0, SUBMENU_SELECT);   //Display default nav ui

	while (true)
	{
		//Safety feature - Stop LCD control because the game has entered driver control mode
		#ifndef LCD_NO_SAFETY //Do not use the safety

			#ifdef LCD_SAFETY_REQ_COMP_SWITCH //Require the competition switch to be plugged in for the safety to work

			if (nVexRCReceiveState & vrCompetitionSwitch)
			{
				if (!(nVexRCReceiveState & vrDisabled) && !(nVexRCReceiveState & vrAutonomousMode))
				{
					startTask(usercontrol);
					displayLCDString(0, 0, SAFETY_TRIG);
					displayLCDString(1, 0, SAFETY_TRIG);
					break;
				}
			}

			#else //LCD_SAFETY_REQ_COMP_SWITCH

			if (!(nVexRCReceiveState & vrDisabled) && !(nVexRCReceiveState & vrAutonomousMode))
			{
				startTask(usercontrol);
				displayLCDString(0, 0, SAFETY_TRIG);
				displayLCDString(1, 0, SAFETY_TRIG);
				break;
			}

			#endif //LCD_SAFETY_REQ_COMP_SWITCH

		#endif //LCD_NO_SAFETY

		//Blink LCD backlight at set rate (in Hz)
		if (backlightBlinkRate == 0)
		{
			bLCDBacklight = true;
		}
		else if (time1[T4] - oldTime > 1000 / backlightBlinkRate) //deltaTime > period
		{
			bLCDBacklight = !bLCDBacklight;
			oldTime = time1[T4];
		}

		//Only one menu has been added
		//Only check for a function
		if (nextMenu == 1)
		{
			if (nLCDButtons & kButtonCenter)
			{
				if (currentMenu->dispatchFuncVal != -1)
				{
					//A function exists, execute it
					invoke(currentMenu->dispatchFuncVal);
				}
			}
		}
		else
		{
			//Left button
			if (nLCDButtons & kButtonLeft)
			{
				if (currentMenu->prev != NULL)
				{
					currentMenu = currentMenu->prev;
					waitForLCDRelease();
				}
			}
			//Right button
			else if (nLCDButtons & kButtonRight)
			{
				if (currentMenu->next != NULL)
				{
					currentMenu = currentMenu->next;
					waitForLCDRelease();
				}
			}
			//Center button
			else if (nLCDButtons & kButtonCenter)
			{
				//Let the user hold the center button
				wait1Msec(250);

				//Center held
				if (nLCDButtons & kButtonCenter)
				{
					//If a higher menu exists
					if (currentMenu->up != NULL)
					{
						currentMenu = currentMenu->up;
						waitForLCDRelease();
					}
				}
				//Center not held
				else
				{
					//If a lower menu exists
					if (currentMenu->down != NULL)
					{
						currentMenu = currentMenu->down;
						waitForLCDRelease();
					}
					//No lower menu exists, check if there is a function
					else if (currentMenu->dispatchFuncVal != -1)
					{
						//A function exists, execute it
						invoke(currentMenu->dispatchFuncVal);
					}
				}
			}
		}

		clearLCDLine(0);
		clearLCDLine(1);
		displayLCDString(0, 0, *currentMenu->msg);
		displayLCDString(1, 0, SUBMENU_SELECT);

		//Slow loop time to minimize impact on other threads
		//Lower loop time for more responsive controls
		wait1Msec(lcdSystemLoopWait);
	}

	//Clear menu once the user is done
	clearLCDLine(0);
	clearLCDLine(1);
}

#endif //#if MENU_NUM > 0
#endif //#ifdef MENU_NUM

#endif //#ifndef LCDCONTROL_C_INCLUDED
