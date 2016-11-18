#ifndef BCI_EKF_C_INCLUDED
#define BCI_EKF_C_INCLUDED

#include "ekf.h"

float findMahalanobisDistance(matrix *data, matrix *mean, matrix *cov)
{
  matrix sub1, sub2, sub1_2, inverse, result;
  matrix_Initialize(sub1, 1, data->rows);
  matrix_Initialize(sub2, data->rows, 1);
  matrix_Initialize(sub1_2, data->rows, 1);
  matrix_Initialize(inverse, cov->columns, cov->rows);
  matrix_Initialize(result, 1, 1);

  matrix_SubtractMatrix(data, mean, &sub1);
  matrix_Transpose(&sub1, &sub1_2);

  if (matrix_Invert(cov, &inverse))
  {
    return 0;
  }

  matrix_MultiplyByMatrix(&sub1_2, &inverse, &sub2);
  matrix_Transpose(&sub1_2, &sub1);
  matrix_MultiplyByMatrix(&sub2, &sub1, result);

  const float finalResult = matrix_Get(&result, 0, 0);

  matrix_Free(&sub1);
  matrix_Free(&sub2);
  matrix_Free(&sub1_2);
  matrix_Free(&inverse);
  matrix_Free(&result);

  return finalResult;
}

#endif //BCI_EKF_C_INCLUDED
