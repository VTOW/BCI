#ifndef BCI_LCDCONTROL_C_INCLUDED
#define BCI_LCDCONTROL_C_INCLUDED

//Do nothing with no menus
#ifdef MENU_NUM
#if MENU_NUM > 0

#include "lcdControl.h"

//LCD system loop wait time in ms
static int lcdSystemLoopWait = 100;

//Menu for current selection
menu *currentMenu = NULL;

//Array for menu allocation
static menu menus[MENU_NUM];

//Index of next menu allocation slot
static int nextMenu = 0;

//Backlight blink rate (in Hz)
static int backlightBlinkRate = 0;

//Whether or not the game state safety fired
bool lcdGameStateSafetyFired = false;

/*
* Adds and initializes a menu pointer, and adds the menu to the main array
*/
menu* lcd_newMenu(const string *msg, const int dispatchFuncVal, const string *msg2, const menu *next, const menu *prev, const menu *up, const menu *down)
{
	//Bounds check
	if (nextMenu == MENU_NUM)
	{
		//If outside bounds
		//Make it very obvious to the user
		for (int i = 0; i < MENU_NUM; i++)
		{
			lcd_changeMessage(&(menus[i]), LCD_INCORRECT_MENU_NUM);
		}

		//Return previously allocated menu
		nextMenu--;
		return &(menus[nextMenu++]);
	}

	//Grab the next menu slot
	//Should be a null menu
	menu *m = &(menus[nextMenu]);
	nextMenu++;

	//Initialize menu
	m->next = next;
	m->prev = prev;
	m->up = up;
	m->down = down;
	m->msg = msg;
	m->msg2 = msg2;
	m->dispatchFuncVal = dispatchFuncVal;

	return m;
}

menu* lcd_newMenu(const string *msg, const string *msg2, const int dispatchFuncVal, const menu *next, const menu *prev, const menu *up, const menu *down)
{
	return lcd_newMenu(msg, dispatchFuncVal, msg2, next, prev, up, down);
}

/*
* Sets a blink rate (in Hz) for the lcd backlight
*/
void lcd_setBacklightBlinkRate(const int rate)
{
	backlightBlinkRate = rate;
}

/*
* Changes the function a menu has
*/
void lcd_changeFunction(menu *m, const int func)
{
	m->dispatchFuncVal = func;
}

/*
* Changes the message a menu has
*/
void lcd_changeMessage(const menu *m, const string *newMsg)
{
	m->msg = newMsg;
}

/*
* Returns the current game state safety state
*/
bool lcd_getLCDSafetyState()
{
	return lcdGameStateSafetyFired;
}

/*
* Childs 1 menu to a parent
*/
void lcd_formLevel(menu *parent, menu *child)
{
	child->up = parent;
	parent->down = child;
}

/*
* Childs 2 menus to a parent
*/
void lcd_formLevel(menu *parent, menu *child, menu *child2)
{
	child->up = parent;
	child2->up = parent;
	parent->down = child;
}

/*
* Childs 3 menus to a parent
*/
void lcd_formLevel(menu *parent, menu *child, menu *child2, menu *child3)
{
	child->up = parent;
	child2->up = parent;
	child3->up = parent;
	parent->down = child;
}

/*
* Childs 4 menus to a parent
*/
void lcd_formLevel(menu *parent, menu *child, menu *child2, menu *child3, menu *child4)
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
void lcd_formLevel(menu *parent, menu *child, menu *child2, menu *child3, menu *child4, menu *child5)
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
void lcd_formLevel(menu *parent, menu *child, menu *child2, menu *child3, menu *child4, menu *child5, menu *child6)
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
*		As a result, this can also be used with an array
*/
void lcd_formLevel(menu *parent, menu *startingMenu, const int count)
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
void lcd_putMenuInRow(menu *m, menu *next, menu *prev)
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
void lcd_linkMenus(menu *m1, menu *m2)
{
	m1->next = m2;
	m1->prev = m2;
	m2->next = m1;
	m2->prev = m1;
}

/*
* Pairs 3 menus
*/
void lcd_linkMenus(menu *m1, menu *m2, menu *m3)
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
void lcd_linkMenus(menu *m1, menu *m2, menu *m3, menu *m4)
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
void lcd_linkMenus(menu *m1, menu *m2, menu *m3, menu *m4, menu *m5)
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
void lcd_linkMenus(menu *m1, menu *m2, menu *m3, menu *m4, menu *m5, menu *m6)
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
* Pairs 7 menus
*/
void lcd_linkMenus(menu *m1, menu *m2, menu *m3, menu *m4, menu *m5, menu *m6, menu *m7)
{
	m1->next = m2;
	m1->prev = m7;
	m2->next = m3;
	m2->prev = m1;
	m3->next = m4;
	m3->prev = m2;
	m4->next = m5;
	m4->prev = m3;
	m5->next = m6;
	m5->prev = m4;
	m6->next = m7;
	m6->prev = m5;
	m7->next = m1;
	m7->prev = m6;
}

/*
* Pairs n menus
* Note: This is dependent upon allocation order
*		As a result, this can also be used with an array
*/
void lcd_linkMenus(menu *m1, const int count)
{
	//Pointer to current menu
	//Start at input menu
	menu *currentMenu = m1;

	//Step through memory and link menus
	for (int i = 0; i < count; i++)
	{
		//First menu is special
		if (i == 0)
		{
			currentMenu->next = currentMenu + 1;
			currentMenu->prev = currentMenu + count - 1;
		}
		//Last menu is special
		else if (i == count - 1)
		{
			currentMenu->next = currentMenu - count + 1;
			currentMenu->prev = currentMenu - 1;
		}
		else
		{
			currentMenu->next = currentMenu + 1;
			currentMenu->prev = currentMenu - 1;
		}

		//Grab next menu in memory
		currentMenu = currentMenu + 1;
	}
}

/*
* Updates the LCD and responds to button presses
*/
task lcdControlTask()
{
	//Timer for backlight blink
	timer backlightTimer;
	timer_Initialize(&backlightTimer);

	clearLCDLine(0);
	clearLCDLine(1);
	currentMenu = &(menus[0]);                //Start control with first menu
	displayLCDString(0, 0, *menus[0].msg);    //Display first menu
	displayLCDString(1, 0, LCD_SUBMENU_SELECT);   //Display default nav ui

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
					displayLCDString(0, 0, LCD_SAFETY_TRIG);
					displayLCDString(1, 0, LCD_SAFETY_TRIG);
					break;
				}
			}

			#else //LCD_SAFETY_REQ_COMP_SWITCH

			if (!(nVexRCReceiveState & vrDisabled) && !(nVexRCReceiveState & vrAutonomousMode))
			{
				startTask(usercontrol);
				displayLCDString(0, 0, LCD_SAFETY_TRIG);
				displayLCDString(1, 0, LCD_SAFETY_TRIG);
				break;
			}

			#endif //LCD_SAFETY_REQ_COMP_SWITCH

		#endif //LCD_NO_SAFETY

		//Blink LCD backlight at set rate (in Hz)
		if (backlightBlinkRate == 0)
		{
			bLCDBacklight = true;
		}
		else if (timer_Repeat(&backlightTimer, 1000.0 / backlightBlinkRate))
		{
			bLCDBacklight = !bLCDBacklight;
		}

		//Only one menu has been added
		//Only check for a function
		if (nextMenu == 1)
		{
			if (nLCDButtons & kButtonCenter)
			{
				#ifndef LCD_NO_INVOKE
					if (currentMenu->dispatchFuncVal != -1)
					{
						//A function exists, execute it
						lcd_invoke(currentMenu->dispatchFuncVal);
					}
				#endif //LCD_NO_INVOKE
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

						clearLCDLine(0);
						clearLCDLine(1);
						displayLCDString(0, 0, *currentMenu->msg);
						displayLCDString(1, 0, LCD_SUBMENU_SELECT);

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
					#ifndef LCD_NO_CALLBACKS
						//No lower menu exists, check if there is a function
						else if (currentMenu->dispatchFuncVal != -1)
						{
							//A function exists, execute it
							lcd_invoke(currentMenu->dispatchFuncVal);

							waitForLCDRelease();
						}
					#endif //LCD_NO_CALLBACKS
				}
			}
		}

		clearLCDLine(0);
		clearLCDLine(1);
		displayLCDString(0, 0, *currentMenu->msg);
		displayLCDString(1, 0, *currentMenu->msg2);

		//Slow loop time to minimize impact on other threads
		//Lower loop time for more responsive controls
		wait1Msec(lcdSystemLoopWait);
	}

	//Clear menu once the user is done
	clearLCDLine(0);
	clearLCDLine(1);
}

#endif //MENU_NUM > 0
#endif //MENU_NUM

#endif //BCI_LCDCONTROL_C_INCLUDED
