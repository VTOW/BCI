#ifndef BCI_H_INCLUDED
#define BCI_H_INCLUDED

#if defined(BCI_USE_EKF)
  #define BCI_USE_MATRIX;
#endif

#if defined(BCI_USE_BLOCK) || defined(BCI_USE_MATRIX) || defined(BCI_USE_ARRAYLIST)
  #define BCI_USE_HEAP
#endif

#if defined(BCI_USE_MATRIX) || defined(BCI_USE_ARRAYLIST)
  #define BCI_USE_BLOCK
#endif

#if defined(BCI_USE_BANGBANG) || defined(BCI_USE_VEL_PID) || defined(BCI_USE_VEL_TBH)
  #define BCI_USE_DEMA_FILTER
#endif

#if defined(BCI_USE_PID_OPT)
  #define BCI_USE_POS_PID
#endif

#if defined(BCI_USE_PID_OPT) || defined(BCI_USE_LCDCONTROL)
  #define BCI_USE_TIMER
#endif

#include "Modules\Math\math.h"

#include "Modules\Util\joystickDefinitions.h"
#include "Modules\Util\semaphore.h"
#include "Modules\Util\util.h"

#ifdef BCI_USE_UART
  #include "Modules\Util\uart.c"
#endif

#ifdef BCI_USE_TIMER
  #include "Modules\Util\timer.c"
#endif

#ifdef BCI_USE_HEAP
  #include "Modules\Util\error.c"
#endif

#ifdef BCI_USE_EMA_FILTER
  #include "Modules\Filter\emaFilter.c"
#endif

#ifdef BCI_USE_DEMA_FILTER
  #include "Modules\Filter\demaFilter.c"
#endif

#ifdef BCI_USE_FUA_FILTER
  #include "Modules\Filter\fuaFilter.c"
#endif

#ifdef BCI_USE_TUA_FILTER
  #include "Modules\Filter\tuaFilter.c"
#endif

#ifdef BCI_USE_BIQUAD_FILTER
  #include "Modules\Filter\biquadFilter.c"
#endif

#ifdef BCI_USE_POS_PID
  #include "Modules\Control\positionPID.c"
#endif

#ifdef BCI_USE_VEL_PID
  #include "Modules\Control\velocityPID.c"
#endif

#ifdef BCI_USE_VEL_TBH
  #include "Modules\Control\velocityTBH.c"
#endif

#ifdef BCI_USE_BANGBANG
  #include "Modules\Control\bangBang.c"
#endif

#ifdef BCI_USE_MOTORCONTROL
  #include "Modules\Control\motorControl.c"
#endif

#ifdef BCI_USE_LCDCONTROL
  #include "Modules\LCD\lcdControl.c"
#endif

#ifdef BCI_USE_PID_OPT
 #include "Modules\PID_Optional\driveStraight.c"
#endif

#ifdef BCI_USE_HEAP
  #include "Modules\Heap\heap.c"
#endif

#ifdef BCI_USE_BLOCK
  #include "Modules\Heap\block.c"
#endif

#ifdef BCI_USE_ARRAYLIST
  #include "Modules\Heap\arrayList.c"
#endif

#ifdef BCI_USE_MATRIX
  #include "Modules\Math\matrix.c"
#endif

#ifdef BCI_USE_EKF
  #include "Modules\Math\ekf.c"
#endif

#include "Modules\Etc\suppressWarning.c"

#endif //BCI_H_INCLUDED
