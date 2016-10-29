#ifndef BCI_H_INCLUDED
#define BCI_H_INCLUDED

#include "Modules\Core\math.h"
#include "Modules\Core\joystickDefinitions.h"
#include "Modules\Core\util.c"
#include "Modules\Core\timer.c"
#include "Modules\Core\filter.c"

#include "Modules\Core\positionPID.c"
#include "Modules\Core\velocityPID.c"
#include "Modules\Core\velocityTBH.c"
#include "Modules\Core\bangBang.c"
#include "Modules\Core\motorControl.c"
#include "Modules\Core\lcdControl.c"

#ifdef BCI_USE_PID_OPT
 #include "Modules\PID_Optional\driveStraight.c"
#endif

#ifdef BCI_USE_HEAP
  #include "Modules\Heap\heap.c"
#endif

#include "Modules\Core\suppressWarning.c"

#endif //BCI_H_INCLUDED
