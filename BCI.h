#ifndef BCI_H_INCLUDED
#define BCI_H_INCLUDED

#include "Modules\Math\math.h"

#include "Modules\Util\joystickDefinitions.h"
#include "Modules\Util\semaphore.h"
#include "Modules\Util\uart.c"
#include "Modules\Util\util.h"
#include "Modules\Util\timer.c"
#include "Modules\Util\error.c"

#include "Modules\Filter\emaFilter.c"
#include "Modules\Filter\demaFilter.c"
#include "Modules\Filter\fuaFilter.c"
#include "Modules\Filter\tuaFilter.c"
#include "Modules\Filter\biquadFilter.c"

#include "Modules\Control\positionPID.c"
#include "Modules\Control\velocityPID.c"
#include "Modules\Control\velocityTBH.c"
#include "Modules\Control\bangBang.c"
#include "Modules\Control\motorControl.c"

#include "Modules\LCD\lcdControl.c"

#ifdef BCI_USE_PID_OPT
 #include "Modules\PID_Optional\driveStraight.c"
#endif

#ifdef BCI_USE_HEAP
  #include "Modules\Heap\heap.c"
  #include "Modules\Heap\block.c"
  #include "Modules\Heap\arrayList.c"
  #include "Modules\Math\matrix.c"
#endif

#include "Modules\Etc\suppressWarning.c"

#endif //BCI_H_INCLUDED
