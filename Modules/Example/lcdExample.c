/**
 * This is a tutorial for how to use the basic features of lcdControl. For extra
 * reference, see BCI\Modules\Core\lcdControl.h
 */

#define MENU_NUM 3 //Tell BCI we want to have three menus
#include "BCI.h" //Include BCI after we've told it what we want

menu *mainMenu, *callbackMenu, *parentMenu; //Make our three menus, these must be pointers

task main()
{
  mainMenu = newMenu("Main Menu"); //Make a menu with only a string
  callbackMenu = newMenu("Callback", 1); //Menu a menu with a string and a callback
  parentMenu = newMenu("Parent"); //Make a menu with only a string

  linkMenus(mainMenu, callbackMenu); //Link the two menus together
                                     //linkMenus() supports up to seven menus
                                     //If you want to link more, give it an array
                                     //and the length of the array

  formLevel(parentMenu, mainMenu); //Form a level between parentMenu and mainMenu
                                   //If we hit the center button on parentMenu,
                                   //we will move down to mainMenu. If we hold
                                   //the center button on mainMenu, we will move
                                   //up to parentMenu. If we navigate to callbackMenu
                                   //and try holding up, we won't move up to parentMenu
                                   //because we havnen't linked it in formLevel()
}

//We need to implement invoke
void invoke(int func)
{
  switch (func)
  {
    //Each case of the switch corresponds to a different callback
    case 1: //Case 1 corresponds to the second parameter to newMenu for callbackMenu
      writeDebugStreamLine("Callback run!");
      break;

    default:
      break;
  }
}
