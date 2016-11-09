#define BCI_USE_HEAP
#include "..\..\BCI.h"

task main()
{
	clearDebugStream();

	heap_Init();

  matrix m1, m2, m3;
  matrix_Initialize(&m1, 3, 2);
  matrix_Initialize(&m2, 2, 3);
  matrix_Initialize(&m3, 2, 2);

  float m1Vals[6] = {1,2,3,
  	                 4,5,6};
  matrix_Set(&m1, m1Vals);

  float m2Vals[6] = {7, 8,
  	                 9, 10,
  	                 11,12};
  matrix_Set(&m2, m2Vals);

  long startTime, endTime;
  int i = 0;
  startTime = time1[T1];
  for (; i < 100000; i++)
  {
  	matrix_MultiplyByMatrix(&m1, &m2, &m3);
  }
  endTime = time1[T1];
  writeDebugStreamLine("Time taken: %d", endTime - startTime);
}
