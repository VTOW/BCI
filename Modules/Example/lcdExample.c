/**
 * This is a tutorial for how to use the basic features of lcdControl. For extra
 * reference, see BCI\Modules\Core\lcdControl.h
 */

#define MENU_NUM 3 //Tell BCI we want to have three menus
#include "BCI.h" //Include BCI after we've told it what we want

//Make our three menus, these must be pointers
menu *mainMenu, *callbackMenu, *parentMenu;

task main()
{
  //Make a menu with only a string
  mainMenu = newMenu("Main Menu");

  //Menu a menu with a string and a callback
  callbackMenu = newMenu("Callback", 1);

  //Make a menu with only a string
  parentMenu = newMenu("Parent");

  //Link the two menus together. linkMenus() supports up to seven menus. If you
  //want to link more, give it an array of menus and the length of the array
  linkMenus(mainMenu, callbackMenu);

  //Form a level between parentMenu and mainMenu. If we hit the center button on
  //parentMenu, we will move down to mainMenu. If we hold the center button on
  //mainMenu, we will move up to parentMenu. If we navigate to callbackMenu and
  //try holding up, we won't move up to parentMenu because we havnen't linked it
  //in formLevel()
  formLevel(parentMenu, mainMenu);
}

//We need to implement invoke
void invoke(int func)
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
