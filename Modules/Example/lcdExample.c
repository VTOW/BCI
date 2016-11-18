/**
 * This is a tutorial for how to use the basic features of lcdControl. For extra
 * reference, see BCI\Modules\Core\lcdControl.h
 */

#define BCI_USE_LCDCONTROL
#define MENU_NUM 3 //Tell BCI we want to have three menus
#define LCD_NO_SAFETY //Our example doesn't use the competition template, so we don't need a safety
#include "..\..\BCI.h" //Include BCI after we've told it what we want

//Make our three menus, these must be pointers
menu *mainMenu, *callbackMenu, *parentMenu;

task main()
{
  //Make a menu with only a string
  mainMenu = lcd_newMenu("Main Menu");

  //Menu a menu with a string and a callback
  callbackMenu = lcd_newMenu("Callback", 1);

  //Make a menu with only a string
  parentMenu = lcd_newMenu("Parent");

  //Link the two menus together. linkMenus() supports up to seven menus. If you
  //want to link more, give it an array of menus and the length of the array
  lcd_linkMenus(mainMenu, callbackMenu);

  //Form a level between parentMenu and mainMenu. If we hit the center button on
  //parentMenu, we will move down to mainMenu. If we hold the center button on
  //mainMenu, we will move up to parentMenu. If we navigate to callbackMenu and
  //try holding up, we won't move up to parentMenu because we havnen't linked it
  //in formLevel()
  lcd_formLevel(parentMenu, mainMenu);

  //Tell BCI to run interactions on the LCD
  startTask(lcdControlTask);
}

//We need to implement invoke
void lcd_invoke(int func)
{
  switch (func)
  {
    //Each case of the switch corresponds to a different callback
    //Case 1 corresponds to the second parameter to newMenu for callbackMenu
    case 1:
      writeDebugStreamLine("Callback run!");
      break;

    default:
      break;
  }
}
