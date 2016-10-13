#ifndef BCI_LCDCONTROL_H_INCLUDED
#define BCI_LCDCONTROL_H_INCLUDED

//Do nothing with no menus
#ifdef MENU_NUM
#if MENU_NUM > 0

//LCD buttons
#define BUTTON_LEFT   1
#define BUTTON_CENTER 2
#define BUTTON_RIGHT  4

//Default text
#define DEFAULT_LINE       "<<            >>"
#define SUBMENU_SELECT     "<<   SELECT   >>"
#define EXIT_MENU_SELECT   "<<     OK     >>"
#define SUBMENU_BACK       "<<    BACK    >>"
#define SAFETY_TRIG        "   SAFETY_TRIG  "
#define INCORRECT_MENU_NUM "  BAD MENU_NUM  "

//Menu type
typedef struct menu_t
{
	//Pointer to next menu (right button)
	menu_t *next;
	//Pointer to previous menu (left button)
	menu_t *prev;
	//Pointer to higher menu (center button)
	menu_t *up;
	//Pointer to deeper menu (center button)
	menu_t *down;

	//Displayed text
	string *msg;

	//Function value in the "dispatch table"
	int dispatchFuncVal;
} menu;

//Handles function calls from lcdControl
//Note: Must be implemented by the user
void invoke(int func);

//Adds and initializes a menu
menu* newMenu(const string *msg, const int dispatchFuncVal = -1, const menu *next = NULL, const menu *prev = NULL, const menu *up = NULL, const menu *down = NULL);

//Sets a blink rate (in Hz) for the lcd backlight
void setBacklightBlinkRate(const int rate);

//Changes the function a menu has
void changeFunction(menu *m, const int func);

//Changes the message a menu has
void changeMessage(const menu *m, const string *newMsg);

//Returns the current game state safety state
bool getLCDSafetyState();

//Childs 1 menu to a parent
void formLevel(menu *parent, menu *child);

//Childs 2 menus to a parent
void formLevel(menu *parent, menu *child, menu *child2);

//Childs 3 menus to a parent
void formLevel(menu *parent, menu *child, menu *child2, menu *child3);

//Childs 4 menus to a parent
void formLevel(menu *parent, menu *child, menu *child2, menu *child3, menu *child4);

//Childs 5 menus to a parent
void formLevel(menu *parent, menu *child, menu *child2, menu *child3, menu *child4, menu *child5);

//Childs 6 menus to a parent
void formLevel(menu *parent, menu *child, menu *child2, menu *child3, menu *child4, menu *child5, menu *child6);

//Childs n menus to a parent
//Note: This is dependent upon allocation order
//		As a result, this can also be used with an array
void formLevel(menu *parent, menu *startingMenu, const int count = 1);

//Inserts a menu into a row
void putMenuInRow(menu *m, menu *next, menu *prev = NULL);

//Pairs 2 menus
void linkMenus(menu *m1, menu *m2);

//Pairs 3 menus
void linkMenus(menu *m1, menu *m2, menu *m3);

//Pairs 4 menus
void linkMenus(menu *m1, menu *m2, menu *m3, menu *m4);

//Pairs 5 menus
void linkMenus(menu *m1, menu *m2, menu *m3, menu *m4, menu *m5);

//Pairs 6 menus
void linkMenus(menu *m1, menu *m2, menu *m3, menu *m4, menu *m5, menu *m6);

//Pairs 7 menus
void linkMenus(menu *m1, menu *m2, menu *m3, menu *m4, menu *m5, menu *m6, menu *m7);

//Pairs n menus
//Note: This is dependent upon allocation order
//		As a result, this can also be used with an array
void linkMenus(menu *m1, const int count = 1);

//Updates the LCD and responds to button presses
//LCD_NO_SAFETY can be used to disable driver control safety
//LCD_SAFETY_REQ_COMP_SWITCH can be used to limit driver control safety to a competition switch being plugged in
task updateLCDTask();

#endif //MENU_NUM > 0
#endif //MENU_NUM

#endif //BCI_LCDCONTROL_H_INCLUDED
