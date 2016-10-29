#define BCI_USE_HEAP
#define BCI_HEAP_DEBUG
#include "..\..\BCI.h"

task main()
{
	clearDebugStream();
  heap_init();

  heap_malloc(3);
  heap_print(0,10);

  heap_malloc(2);
  heap_print(0,10);

  heap_free(1,2);
  heap_print(0,10);

  heap_malloc(3);
  heap_print(0,10);

  heap_printStats(0,10);
}
