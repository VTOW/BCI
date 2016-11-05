#define BCI_USE_HEAP
#define BCI_HEAP_DEBUG
#include "..\..\BCI.h"

task main()
{
	clearDebugStream();
  heap_Init();

  heap_Malloc(3);
  heap_Print(0,10);

  heap_Malloc(2);
  heap_Print(0,10);

  heap_Free(1,2);
  heap_Print(0,10);

  heap_Malloc(3);
  heap_Print(0,10);

  heap_PrintStats(0,10);
}
