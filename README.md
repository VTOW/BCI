# BCI
-----
Team 2442A's Core Library
------------------------

This library contains a collection of useful features to help with software development for Vex EDR robots using the RobotC language and development environment.

Filter
------
The filter module contains a collection of filtering operations and datatypes. Currently supported filtering operations:
- Simple Moving Average
- Five-Unit Average
- Ten-Unit Average

LCD Control
-----------
The LCD Control module provides a powerful and reflective LCD programming system targeted at efficient, fast development of complex menu systems. At the top level, this module provides an easy to use framework for making and using menus. A menu is an informational, navigational, and functional tool displayed on an LCD for human-robot interaction. Each menu has four connecting menus, a displayed message, and a callback function. This module also has support for flashing the LCD's backlight and contains an included, customizable match safety feature that prevents being dead on field due to operator or programmer error.

Motor Control
-------------
The motor control module provides slew rate support down to the decimal resolution. This is configurable for all motors, with support for individual motor slew rate control.

PID
---
There are two PID-based position and velocity control modules included, both with support for quadrature encoders and IME's.

TBH
---
There is one TBH-based velocity control module included, with support for quadrature encoders and IME's.

Timer
----
This module contains a timer system for frequently used timing operations, and can be used to build non-blocking button debouncing and waits.

Util
----
This module contains useful utility functions and definitions used for low level programming and general debugging.

Joystick Definitions
--------------------
This module contains relative position-based redefinitions of all joystick and partner joystick buttons.

# In-Depth Documentation
-----------------------
Filter
-----
There are three types of filters, `EMAFilter`, an exponential moving average; `FUAFilter`, a five-unit moving average; and `TUAFitler`, a ten-unit moving average. Each filter must be initialized with its respective initialization function before it can be used. Initialization functions take the form `void filter_Init_<FILTER_PREFIX>(<FILTER_TYPE> *filter)`, where `<FILTER_PREFIX>` is the prefix of a filter type which denotes its type (i.e., `EMA`, `FUA`, or `TUA`) and`<FILTER TYPE>` is type of filter.

Once initialized, filters can be used in stepped increments. To use a filter, call its respective stepping function, which takes the form `float filter_<FILTER_PREFIX>(<FILTER_TYPE> *filter, ...)`. This stepping function always returns the newly filtered value. The ellipsis, `...`, denotes varying parameters for different filters. For an `EMAFilter`, this is `float readIn, float alpha`, where `readIn` is a new data point and `alpha` is a blending percentage in the range [0, 1]. For an `FUAFilter` and a `TUAFilter`, this is `float componentIn`, where `componentIn` is a new data point.

LCD Control
----------
This module uses a centralized main task to perform menu management and callback handling. Before any menus can be created, a number of menus must be defined above the library include line in the form `#define MENU_NUM n`, where `n` denotes the number of menus being used. If `MENU_NUM` is less than the total number of calls to `initMenu`, the string "BAD MENU_NUM" will be displayed to the user on the LCD screen. At this point, a choice about included safety features must be made via definition (i.e., `#define`). These choices are: `LCD_NO_SAFETY`, which removes all safety features; `LCD_SAFETY_REQ_COMP_SWITCH`, which disables all safety features unless a competition switch is plugged in to the primary joystick. The state of the LCD safety can be checked at any time using `bool getLCDSafetyState()`, which returns true when the safety has fired. In addition, below the library include line, the function `void invoke(int func)` must be implemented by the user, where `func` is a dispatch table function value. The recommended implementation of this function is a switch statement, switching over `func`, with a case statement for every implemented value of `func`. Finally, the function `void setBacklightBlinkRate(int rate)`, can be used to specify an LCD backlight blink rate, where `rate` is the blink rate in hertz. By default, a blink rate of zero is defined to not blink.

Now, menus can be created and initialized. Before a menu can be used, it must be initialized. The menu initialization function takes the form `menu* newMenu(string *msg, int dispatchFuncVal = -1, menu *next = NULL, menu *prev = NULL, menu *up = NULL, menu *down = NULL)`. The string `msg` is any valid string to be display when the menu is selected, and is the only required parameter for this function. The other, optional, parameters are `dispatchFuncVal`, an integer value passed to the user-created dispatch table during a function callback event; `next`, a right-linked menu; `prev`, a left-linked menu; `up`, an up-linked menu; and `down`, a down-linked menu. Menu messages can be changed with the function `void changeMessage(menu *menu, string *newMsg)`, where `menu` is the menu containing the message to be changed, and `newMsg` is any valid string destined to be the new message of `menu`. In addition, menu dispatch table function value can also be changed with the function `void changeFunction(menu *menu, int func)`, where `menu` is the menu containing the dispatch table function value to be changed, and `func` is any integer value destined to be the new dispatch table function value of `menu`.

Once menus are initialized, they can be linked together into rows and levels. Menus can be formed into rows using the  function `void linkMenus(menu *m1, menu *m2)`, where `m1` will be a link to `m2`, and `m2` will be a link to `m1`. This function can accept between two and six menus. Menus can be group together into levels using the function `void formLevel(menu *parent, menu *child)`, where `parent` is the parent menu for the group, and `child` is any number of menus, up to five, who will be children of `parent`. The first menu in the list of children will be used when navigating downward from parent, and any child of parent will direct to parent when navigating upward from that child.

Once menus are linked together, they can be used by the core management task to facilitate user interaction. This task, `task updateLCDTask()`, handles all menu-, safety-, and backlight-related tasks. The recommended use of this task is to start it in `pre_auton` and wait until a confirmation signal is sent to `invoke`, using a function integrated into a menu via the dispatch table system, upon which the task is ended.

Motor Control
-------------
This module, like the LCD Control module, uses a centralized main task to perform core functions. In this case, those functions are: motor slewing. Physical motors (or more accurately, motor ports), and represented in software using a data type called `driveMotor`. Each `driveMotor` has a requested speed, an artificial speed, a slew rate, and an active flag. The requested speed is set by the programmer using the macro `setMotorSpeed(motor, power)`, where `motor` is a motor as declared in RobotC's pragma statements and `power` is an integer motor power. The slew rate is also set by the programmer, using the macro `setMotorSlew(motor, rate)`, where `motor` is a motor as declared in RobotC's pragma statements, and `rate` is a positive slew rate (this number can be floating point). Finally, the active flag is also set by the programming, using the macro `setMotorActive(motor)` or `setMotorInactive(motor)`, where `motor` is a motor as declared in RobotC's pragma statements. Active motors are updated by the module's main task, `task motorSlewRateTask()`, and inactive motor are not updated and have their update cycles skipped. Motors can be retrieved from the module using the macro `getMotor(motor)`, where `motor` is a motor as declared in RobotC's pragma statements. In addition, a motor's requested speed can be retrieved from the module using the macro `getMotorSpeed(motor)`, where `motor` is a motor as declared in RobotC's pragma statements. This module also provides redefinitions of primitive RobotC motor control statements for raw motor control, namely, `setMotorSpeedRaw(motor, power)` and `getMotorSpeedRaw(motor)`, where `motor` is a motor as declared in RobotC's pragma statements and `power` is an integer motor power.

Before a `driveMotor` can be used by the module, it must be initialized using the function `driveMotor* addMotor(tMotor motor, float slewRate = MOTOR_DEFAULT_SLEW_RATE)`, where `motor` is a motor as declared in RobotC's pragma statements and `slewRate` is any positive slew rate (this number can be floating point). By default, `slewRate` is the default motor slew rate, 10. Once This function returns a `driveMotor` reference of the initialized `driveMotor`.

Once a `driveMotor` is initialized, no further actions need to be taken for motor setup except starting the module's main task, `task motorSlewRateTask()`.
