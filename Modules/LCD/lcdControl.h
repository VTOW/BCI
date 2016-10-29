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
string DEFAULT_LINE       = "<<            >>";
string SUBMENU_SELECT     =  "<<   SELECT   >>";
string EXIT_MENU_SELECT   =  "<<     OK     >>";
string SUBMENU_BACK       =  "<<    BACK    >>";
string SAFETY_TRIG        =  "   SAFETY_TRIG  ";
string INCORRECT_MENU_NUM = "  BAD MENU_NUM  ";

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
	string *msg2;

	//Function value in the "dispatch table"
	int dispatchFuncVal;
} menu;

/**
 * Runs a callback function. This must be implemented by the user
 * Define flag LCD_NO_CALLBACKS if you don't want to use any callbacks
 * @param func ID of callback
 */
#ifndef LCD_NO_CALLBACKS
	void invoke(int func);
#endif //LCD_NO_CALLBACKS

/**
 * Initializes a menu
 * @param  msg             Menu message displayed on LCD
 * @param  dispatchFuncVal Callback ID
 * @param  msg2            String on LCD line 2
 * @param  next            Right-linked menu
 * @param  prev            Left-linked menu
 * @param  up              Up-linked menu
 * @param  down            Down-linked menu
 * @return                 Initialized menu
 */
menu* newMenu(const string *msg, const int dispatchFuncVal = -1, const string *msg2 = &SUBMENU_SELECT, const menu *next = NULL, const menu *prev = NULL, const menu *up = NULL, const menu *down = NULL);

/**
 * Sets a blink rate (in Hz) for the lcd backlight
 * @param rate Backlight blink rate (Hz)
 */
void setBacklightBlinkRate(const int rate);

/**
 * Changes the function a menu has
 * @param m    Menu to change
 * @param func New callback ID
 */
void changeFunction(menu *m, const int func);

/**
 * Changes the message a menu has
 * @param m      Menu to change
 * @param newMsg New message
 */
void changeMessage(const menu *m, const string *newMsg);

/**
 * Returns the current game state safety state
 * @return current game state safety state
 */
bool getLCDSafetyState();

/**
 * Forms a level between a parent and children menus
 * @param parent Parent menu
 * @param child  Child menu
 */
void formLevel(menu *parent, menu *child);
void formLevel(menu *parent, menu *child, menu *child2);
void formLevel(menu *parent, menu *child, menu *child2, menu *child3);
void formLevel(menu *parent, menu *child, menu *child2, menu *child3, menu *child4);
void formLevel(menu *parent, menu *child, menu *child2, menu *child3, menu *child4, menu *child5);
void formLevel(menu *parent, menu *child, menu *child2, menu *child3, menu *child4, menu *child5, menu *child6);
void formLevel(menu *parent, menu *startingMenu, const int count = 1);

/**
 * Inserts a menu into a row
 * @param m    Menu to insert
 * @param next Right-linked menu
 * @param prev Left-linked menu
 */
void putMenuInRow(menu *m, menu *next, menu *prev = NULL);

/**
 * Links menus together into a row
 * @param m1 One menu to link
 * @param m2 Another menu to link
 */
void linkMenus(menu *m1, menu *m2);
void linkMenus(menu *m1, menu *m2, menu *m3);
void linkMenus(menu *m1, menu *m2, menu *m3, menu *m4);
void linkMenus(menu *m1, menu *m2, menu *m3, menu *m4, menu *m5);
void linkMenus(menu *m1, menu *m2, menu *m3, menu *m4, menu *m5, menu *m6);
void linkMenus(menu *m1, menu *m2, menu *m3, menu *m4, menu *m5, menu *m6, menu *m7);
void linkMenus(menu *m1, const int count = 1);

/**
 * Displays menus on LCD and handles user interaction.
 * Define flag LCD_NO_SAFETY to disable driver control safety
 * Define flag LCD_SAFETY_REQ_COMP_SWITCH to limit driver control safety to fire
 * 	only when a competition switch is plugged in
 */
task updateLCDTask();

#endif //MENU_NUM > 0
#endif //MENU_NUM

#endif //BCI_LCDCONTROL_H_INCLUDED
