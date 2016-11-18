#define BCI_USE_BLOCK
#define BCI_BLOCK_DEBUG
#include "..\..\BCI.h"

task main()
{
	clearDebugStream();
  heap_Init();

  block b;
  block_Initialize(&b, 2);
  writeDebugStreamLine("%d,%d",b.loc,b.size);
  heap_Print(0,11);
  writeDebugStreamLine("%d",block_Shrink(&b,1));
  heap_Print(0,11);
  writeDebugStreamLine("%d,%d",b.loc,b.size);
}
