#define BCI_USE_MATRIX
#define BCI_MATRIX_O2
//#define BCI_HEAP_DEBUG
//#define BCI_BLOCK_DEBUG
//#define BCI_MATRIX_DEBUG
#include "..\..\BCI.h"

task main()
{
	clearDebugStream();

	heap_Init();

  matrix m1, m2, m3;
  matrix_Initialize(&m1, 5, 5);
  matrix_Initialize(&m2, 5, 5);
  matrix_Initialize(&m3, 5, 5);

  float m1Vals[25] = {5,2,3,3,5, 5,3,3,3,5, 3,3,7,3,7, 3,3,3,3,7, 5,5,7,7,6};
  matrix_Set(&m1, m1Vals);

  float m2Vals[25] = {1,2,3,4,5, 1,2,3,4,5, 1,2,3,4,5, 1,2,3,4,5, 1,2,3,4,5};
  matrix_Set(&m2, m2Vals);

  //heap_PrintStats(0,1000);
  //writeDebugStreamLine("%d",matrix_Determinant(&m1));
  //matrix_Transpose(&m1, &m3);
  //heap_PrintStats(0,1000);
  //for (int i = 0; i < 5; i++)
  //{
  //	for (int j = 0; j < 5; j++)
  //	{
  //		writeDebugStreamLine("%d", matrix_Get(&m3, i, j));
  //	}
  //	writeDebugStreamLine(",");
  //}

  //Naive implementation takes 2889.6 milliseconds on average
  //Optimized naive implemenetation takes 872 milliseconds on average
  for (int j = 0; j < 5; j++)
  {
	  long startTime, endTime;
	  int i = 0;
	  startTime = time1[T1];
	  for (; i < 1; i++)
	  {
	  	matrix_MultiplyByMatrix(&m1, &m2, &m3);
	  	matrix_Transpose(&m1, &m3);
	  	matrix_Determinant(&m1);
	  	matrix_Invert(&m1, &m3);
	  }
	  endTime = time1[T1];
	  writeDebugStreamLine("Time taken: %d", endTime - startTime);
	}
}
