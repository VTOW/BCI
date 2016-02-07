BCI
===
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
