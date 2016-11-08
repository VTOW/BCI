#define BCI_USE_HEAP
#define BCI_HEAP_DEBUG
#include "..\..\BCI.h"

task main()
{
	clearDebugStream();
  heap_Init();

  heap_Malloc(3, 1);
  heap_Print(0,11);

  heap_Malloc(2, 2);
  heap_Print(0,11);

  heap_Expand(0,3,1);
  heap_Print(0,11);

  heap_PrintStats(0,11);
}
