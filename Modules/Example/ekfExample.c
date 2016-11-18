#define BCI_USE_EKF
#define BCI_MATRIX_DEBUG
#include "..\..\BCI.h"

task main()
{
	clearDebugStream();

	heap_Init();

	matrix data, mean, cov;
	matrix_Initialize(&data, 1, 3);
	matrix_Initialize(&mean, 1, 3);
	matrix_Initialize(&cov, 3, 3);

	writeDebugStreamLine("%1.2f", findMahalanobisDistance(&data, &mean, &cov));
	writeDebugStreamLine("%1.2f", BCI_HEAP_FAIL);
}
