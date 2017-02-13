# BCI

This library contains a collection of useful features to help with software development for Vex EDR robots using the RobotC language and development environment.

Code in this library is based on the work of:
 - James Pearman ([Forum Account][jpearmanLink])
 - Justin Marple ([BNSLib Link][BNSLibLink])
 - Griffin Tabor ([Forum Post Link][taborLink])
 - Jordan Kiesel ([Forum Post Link][jordanLink])
 - Unionjackjz1 ([Forum Post Link][spurflysLink])

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
 - PID-based autonomous functions (drive in a straight line, etc.)
 - Common math definitions and macros
 - Redefinitions of all joystick channels and buttons
 - Semaphore wrappers
 - UART wrappers

----------------

For tutorials, see the files in the folder "Modules\Example" or the Wiki. Additionally, all header files are thoroughly and consistantly documented (these are the best sources of up-to-date information).

[jpearmanLink]: <https://www.vexforum.com/index.php/member/3759-jpearman>
[BNSLibLink]: <https://github.com/JMarple/BNSLibrary>
[taborLink]: <https://www.vexforum.com/index.php/19737-wpi-lidar-explanation>
[jordanLink]: <https://www.vexforum.com/index.php/9800-24c-s-motor-control-value-remapping>
[spurflysLink]: <https://www.vexforum.com/index.php/21242-truespeed-for-turbo-motors/0>
