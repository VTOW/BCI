# BCI

This library contains a collection of useful features to help with software development for Vex EDR robots using the RobotC language and development environment.

Code in this library is based on the work of:
 - James Pearman
 - Justin Marple (https://github.com/JMarple/BNSLibrary)
 - Griffin Tabor

----------------

Currently, BCI features these tools:
 - Dynamic memory (heap based)
 - Position tracking (odometry)
 - ArrayList data structure
 - Matrix math
 - Filters (IIR, etc.)
 - PID control (position and velocity domain)
 - TBH control
 - Bang-bang control
 - Motor slew rate controller
 - LCD menu system
 - Common math definitions and macros
 - Redefinitions of all joystick channels and buttons
 - Semaphore wrappers
 - UART wrappers

----------------

For tutorials, see the files in the folder "Modules\Example" or the Wiki. Additionally, all header files are thoroughly and consistantly documented (these are the best sources of up-to-date information).
