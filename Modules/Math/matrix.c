#ifndef BCI_MATRIX_C_INCLUDED
#define BCI_MATRIX_C_INCLUDED

#include "matrix.h"

bool matrix_Initialize(matrix *mat, const unsigned int columns, const unsigned int rows, float defaultValue)
{
  mat->columns = columns;
  mat->rows = rows;
  #ifdef BCI_MATRIX_DEBUG
    if (!block_Initialize(&(mat->data), columns * rows, defaultValue))
    {
      string s;
      sprintf(s, "Initialize: Cannot initialize matrix with columns: %d and rows: %d", columns, rows);
      util_PrintMatrixError(s);
      return false;
    }
    return true;
  #else
    return block_Initialize(&(mat->data), columns * rows, defaultValue);
  #endif
}

void matrix_Free(matrix *mat)
{
  block_Free(mat->data);
}

void matrix_Set(matrix *mat, const float *data)
{
  for (unsigned int i = 0; i < mat->columns * mat->rows; i++)
  {
    #if defined(BCI_MATRIX_O0)
      block_Set(&(mat->data), i, *(data + i));
    #elif defined(BCI_MATRIX_O1)
      heap_Set(mat->data.loc + i, *(data + i));
    #elif defined(BCI_MATRIX_O2)
      bciHeap[mat->data.loc + i] = *(data + i);
    #endif
  }
}

void matrix_Set(matrix *mat, const unsigned int x, const unsigned int y, const float data)
{
  #if defined(BCI_MATRIX_O0)
    #ifdef BCI_MATRIX_DEBUG
      if (y + (mat->columns * x) >= mat->columns * mat->rows)
      {
        string s;
        sprintf(s, "Set: Invalid location: %d", y + (mat->columns * x));
        util_PrintMatrixError(s);
      }
      else
      {
        block_Set(&(mat->data), y + (mat->columns * x), data);
      }
    #else
      block_Set(&(mat->data), y + (mat->columns * x), data);
    #endif
  #elif defined(BCI_MATRIX_O1)
    heap_Set(mat->data.loc + y + (mat->columns * x), data);
  #elif defined(BCI_MATRIX_O2)
    bciHeap[mat->data.loc + y + (mat->columns * x)] = data;
  #endif
}

//Inline version of matrix_Set
#define matrix_Set_Inline_1(mat, x, y, dataIn) block_Set(&(mat->data), y + (mat->columns * x), dataIn)
#define matrix_Set_Inline_2(mat, x, y, dataIn) block_Set_Inline_NoPtr(mat->data, y + (mat->columns * x), dataIn)
#define matrix_Set_Inline_3(mat, x, y, dataIn) block_Set_Inline_Deep_NoPtr(mat->data, y + (mat->columns * x), dataIn)

float matrix_Get(const matrix *mat, const unsigned int x, const unsigned int y)
{
  #if defined(BCI_MATRIX_O0)
    #ifdef BCI_MATRIX_DEBUG
      if (y + (mat->columns * x) >= mat->columns * mat->rows)
      {
        string s;
        sprintf(s, "Set: Invalid location: %d", y + (mat->columns * x));
        util_PrintMatrixError(s);
      }
      else
      {
        return block_Get(&(mat->data), y + (mat->columns * x));
      }
    #else
      return block_Get(&(mat->data), y + (mat->columns * x));
    #endif
  #elif defined(BCI_MATRIX_O1)
    return heap_Get(mat->data.loc + y + (mat->columns * x));
  #elif defined(BCI_MATRIX_O2)
    return bciHeap[mat->data.loc + y + (mat->columns * x)];
  #endif
}

//Inline version of matrix_Get
#define matrix_Get_Inline_1(mat, x, y) block_Get(&(mat->data), y + (mat->columns * x))
#define matrix_Get_Inline_2(mat, x, y) block_Get_Inline_NoPtr(mat->data, y + (mat->columns * x))
#define matrix_Get_Inline_3(mat, x, y) block_Get_Inline_Deep_NoPtr(mat->data, y + (mat->columns * x))

void matrix_Copy(const matrix *from, matrix *to)
{
  #ifdef BCI_MATRIX_O0
    if (to->rows != from->rows || to->columns != from->columns)
    {
      #ifdef BCI_MATRIX_DEBUG
        string s;
        sprintf(s, "Copy: Cannot copy matrix of size [%d,%d] into result matrix of size [%d,%d]", from->columns, from->rows, to->columns, to->rows);
        util_PrintMatrixError(s);
      #endif

      return;
    }
  #endif

  for (unsigned int i = 0; i < to->rows; i++)
  {
    for (unsigned int j = 0; j < to->columns; j++)
    {
      #if defined(BCI_MATRIX_O0)
        matrix_Set(to, i, j, matrix_Get(from, i, j));
      #elif defined(BCI_MATRIX_O1)
        matrix_Set_Inline_2(to, i, j, matrix_Get_Inline_2(from, i, j));
      #elif defined(BCI_MATRIX_O2)
        matrix_Set_Inline_3(to, i, j, matrix_Get_Inline_3(from, i, j));
      #endif
    }
  }
}

void matrix_AddScalar(const matrix *mat, const float scalar, matrix *result)
{
  for (unsigned int i = 0; i < mat->columns * mat->rows; i++)
  {
    #if defined(BCI_MATRIX_O0)
      block_Set(&(result->data), i, block_Get(&(mat->data), i) + scalar);
    #elif defined(BCI_MATRIX_O1)
      heap_Set(result->data.loc + i, heap_Get(mat->data.loc + i) + scalar);
    #elif defined(BCI_MATRIX_O2)
      bciHeap[result->data.loc + i] = bciHeap[mat->data.loc + i] + scalar;
    #endif
  }
}

void matrix_SubtractScalar(const matrix *mat, const float scalar, matrix *result)
{
  for (unsigned int i = 0; i < mat->columns * mat->rows; i++)
  {
    #if defined(BCI_MATRIX_O0)
      block_Set(&(result->data), i, block_Get(&(mat->data), i) - scalar);
    #elif defined(BCI_MATRIX_O1)
      heap_Set(result->data.loc + i, heap_Get(mat->data.loc + i) - scalar);
    #elif defined(BCI_MATRIX_O2)
      bciHeap[result->data.loc + i] = bciHeap[mat->data.loc + i] - scalar;
    #endif
  }
}

void matrix_MultiplyByScalar(const matrix *mat, const float scalar, matrix *result)
{
  for (unsigned int i = 0; i < mat->columns * mat->rows; i++)
  {
    #if defined(BCI_MATRIX_O0)
      block_Set(&(result->data), i, block_Get(&(mat->data), i) * scalar);
    #elif defined(BCI_MATRIX_O1)
      heap_Set(result->data.loc + i, heap_Get(mat->data.loc + i) * scalar);
    #elif defined(BCI_MATRIX_O2)
      bciHeap[result->data.loc + i] = bciHeap[mat->data.loc + i] * scalar;
    #endif
  }
}

void matrix_DivideByScalar(const matrix *mat, const float scalar, matrix *result)
{
  #if defined(BCI_MATRIX_O0)
    if (scalar == 0)
    {
      #ifdef BCI_MATRIX_DEBUG
        string s;
        sprintf(s, "DivideByScalar: Cannot divide matrix by zero");
        util_PrintMatrixError(s);
      #endif
      return;
    }
  #endif

  for (unsigned int i = 0; i < mat->columns * mat->rows; i++)
  {
    #if defined(BCI_MATRIX_O0)
      block_Set(&(result->data), i, block_Get(&(mat->data), i) / scalar);
    #elif defined(BCI_MATRIX_O1)
      heap_Set(result->data.loc + i, heap_Get(mat->data.loc + i) / scalar);
    #elif defined(BCI_MATRIX_O2)
      bciHeap[result->data.loc + i] = bciHeap[mat->data.loc + i] / scalar;
    #endif
  }
}

void matrix_RaiseToScalar(const matrix *mat, const float scalar, matrix *result)
{
  #if defined(BCI_MATRIX_O0)
    if (scalar < 0)
    {
      #ifdef BCI_MATRIX_DEBUG
        string s;
        sprintf(s, "RaiseToScalar: Cannot raise matrix to a negative scalar");
        util_PrintMatrixError(s);
      #endif

      return;
    }
  #endif

  for (unsigned int i = 0; i < mat->columns * mat->rows; i++)
  {
    #if defined(BCI_MATRIX_O0)
      block_Set(&(result->data), i, pow(block_Get(&(mat->data), i), scalar));
    #elif defined(BCI_MATRIX_O1)
      heap_Set(result->data.loc + i, pow(heap_Get(mat->data.loc + i), scalar));
    #elif defined(BCI_MATRIX_O2)
      bciHeap[result->data.loc + i] = pow(bciHeap[mat->data.loc + i], scalar);
    #endif
  }
}

void matrix_AddMatrix(const matrix *mat1, const matrix *mat2, matrix *result)
{
  #if defined(BCI_MATRIX_O0)
    if (mat1->columns != mat2->columns || mat1->rows != mat2->rows)
    {
      #ifdef BCI_MATRIX_DEBUG
        string s;
        sprintf(s, "AddMatrix: Cannot add matrices of sizes [%d,%d] and [%d,%d]", mat1->columns, mat1->rows, mat2->columns, mat2->rows);
        util_PrintMatrixError(s);
      #endif

      return;
    }
  #endif

  for (unsigned int i = 0; i < mat1->columns * mat1->rows; i++)
  {
    #if defined(BCI_MATRIX_O0)
      block_Set(&(result->data), i, block_Get(&(mat1->data), i) + block_Get(&(mat2->data), i));
    #elif defined(BCI_MATRIX_O1)
      heap_Set(result->data.loc + i, heap_Get(mat1->data.loc + i) + heap_Get(mat2->data.loc + i));
    #elif defined(BCI_MATRIX_O2)
      bciHeap[result->data.loc + i] = bciHeap[mat1->data.loc + i] + bciHeap[mat2->data.loc + i];
    #endif
  }
}

void matrix_SubtractMatrix(const matrix *mat1, const matrix *mat2, matrix *result)
{
  #if defined(BCI_MATRIX_O0)
    if (mat1->columns != mat2->columns || mat1->rows != mat2->rows)
    {
      #ifdef BCI_MATRIX_DEBUG
        string s;
        sprintf(s, "SubtractMatrix: Cannot subtract matrices of sizes [%d,%d] and [%d,%d]", mat1->columns, mat1->rows, mat2->columns, mat2->rows);
        util_PrintMatrixError(s);
      #endif

      return;
    }
  #endif

  for (unsigned int i = 0; i < mat1->columns * mat1->rows; i++)
  {
    #if defined(BCI_MATRIX_O0)
      block_Set(&(result->data), i, block_Get(&(mat1->data), i) - block_Get(&(mat2->data), i));
    #elif defined(BCI_MATRIX_O1)
      heap_Set(result->data.loc + i, heap_Get(mat1->data.loc + i) - heap_Get(mat2->data.loc + i));
    #elif defined(BCI_MATRIX_O2)
      bciHeap[result->data.loc + i] = bciHeap[mat1->data.loc + i] - bciHeap[mat2->data.loc + i];
    #endif
  }
}

void matrix_MultiplyByMatrix(const matrix *mat1, const matrix *mat2, matrix *result)
{
  #if defined(BCI_MATRIX_O0)
    if (mat1->columns != mat2->rows || mat1->rows != mat2->columns)
    {
      #ifdef BCI_MATRIX_DEBUG
        string s;
        sprintf(s, "MultiplyByMatrix: Cannot multiply matrices of sizes [%d,%d] and [%d,%d]", mat1->columns, mat1->rows, mat2->columns, mat2->rows);
        util_PrintMatrixError(s);
      #endif

      return;
    }
  #endif

  for (unsigned int i = 0; i < mat1->rows; i++)
  {
    for (unsigned int j = 0; j < mat2->columns; j++)
    {
      #if defined(BCI_MATRIX_O0)
        matrix_Set(result, i, j, 0);
      #elif defined(BCI_MATRIX_O1)
        matrix_Set_Inline_2(result, i, j, 0);
      #elif defined(BCI_MATRIX_O2)
        matrix_Set_Inline_3(result, i, j, 0);
      #endif

      for (unsigned int k = 0; k < mat1->columns; k++)
      {
        #if defined(BCI_MATRIX_O0)
          matrix_Set(result, i, j, matrix_Get(result, i, j) + matrix_Get(mat1, i, k) * matrix_Get(mat2, k, j));
        #elif defined(BCI_MATRIX_O1)
          matrix_Set_Inline_2(result, i, j, matrix_Get_Inline_2(result, i, j) + matrix_Get_Inline_2(mat1, i, k) * matrix_Get_Inline_2(mat2, k, j));
        #elif defined(BCI_MATRIX_O2)
          matrix_Set_Inline_3(result, i, j, matrix_Get_Inline_3(result, i, j) + matrix_Get_Inline_3(mat1, i, k) * matrix_Get_Inline_3(mat2, k, j));
        #endif
      }
    }
  }
}

bool matrix_Minors(const matrix *mat, matrix *result)
{
  #if defined(BCI_MATRIX_O0)
    if (mat->columns != mat->rows)
    {
      #ifdef BCI_MATRIX_DEBUG
        string s;
        sprintf(s, "Minors: Cannot calculate matrix of minors for non-square matrix of size [%d,%d]", mat->columns, mat->rows);
        util_PrintMatrixError(s);
      #endif

      return false;
    }
  #endif

  matrix tmp;
  matrix_Initialize(&tmp, mat->rows - 1, mat->rows - 1);

  for(unsigned int i = 0; i < mat->rows; i++)
  {
    for(unsigned int j = 0; j < mat->columns; j++)
    {
      int x = 0;

      for(unsigned int m = 0; m < mat->rows - 1; m++)
      {
        int y = 0;
        for(unsigned int n = 0; n < mat->columns - 1; n++)
        {
          #if defined(BCI_MATRIX_O0)
            matrix_Set(&tmp, x, y, matrix_Get(mat, m + (m >= i), n + (n >= j)));
          #elif defined(BCI_MATRIX_O1)
            matrix_Set_Inline_2((&tmp), x, y, matrix_Get_Inline_2(mat, m + (m >= i), n + (n >= j)));
          #elif defined(BCI_MATRIX_O2)
            matrix_Set_Inline_3((&tmp), x, y, matrix_Get_Inline_3(mat, m + (m >= i), n + (n >= j)));
          #endif
          y++;
        }
        x++;
      }

      #if defined(BCI_MATRIX_O0)
        matrix_Set(result, i, j, matrix_Determinant(&tmp));
      #elif defined(BCI_MATRIX_O1)
        matrix_Set_Inline_2(result, i, j, matrix_Determinant(&tmp));
      #elif defined(BCI_MATRIX_O2)
        matrix_Set_Inline_3(result, i, j, matrix_Determinant(&tmp));
      #endif
    }
  }

  matrix_Free(&tmp);

  return true;
}

bool matrix_Cofactor(const matrix *mat, matrix *result)
{
  #if defined(BCI_MATRIX_O0)
    if (mat->columns != mat->rows)
    {
      #ifdef BCI_MATRIX_DEBUG
        string s;
        sprintf(s, "Cofactor: Cannot calculate cofactor matrix for non-square matrix of size [%d,%d]", mat->columns, mat->rows);
        util_PrintMatrixError(s);
      #endif

      return false;
    }
  #endif

  matrix_Minors(result, mat);

  for(unsigned int i = 0; i < result->rows; i++)
  {
    for(unsigned int j = 0; j < result->rows; j++)
    {
      if((i + j) % 2 == 1)
      {
        #if defined(BCI_MATRIX_O0)
          matrix_Set(result, j, i, matrix_Get(result, j, i) * -1);
        #elif defined(BCI_MATRIX_O1)
          matrix_Set_Inline_2(result, j, i, matrix_Get_Inline_2(result, j, i) * -1);
        #elif defined(BCI_MATRIX_O2)
          matrix_Set_Inline_3(result, j, i, matrix_Get_Inline_3(result, j, i) * -1);
        #endif
      }
    }
  }

  return true;
}

void matrix_Transpose(const matrix *mat, matrix *result)
{
  for (unsigned int i = 0; i < mat->rows; i++)
  {
    for (unsigned int j = 0; j < mat->columns; j++)
    {
      #if defined(BCI_MATRIX_O0)
        matrix_Set(result, j, i, matrix_Get(mat, i, j));
      #elif defined(BCI_MATRIX_O1)
        matrix_Set_Inline_2(result, j, i, matrix_Get_Inline_2(mat, i, j));
      #elif defined(BCI_MATRIX_O2)
        matrix_Set_Inline_3(result, j, i, matrix_Get_Inline_3(mat, i, j));
      #endif
    }
  }
}

float matrix_Trace(const matrix *mat)
{
  #if defined(BCI_MATRIX_O0)
    if (mat->columns != mat->rows)
    {
      #ifdef BCI_MATRIX_DEBUG
        string s;
        sprintf(s, "Trace: Cannot calculate trace for non-square matrix of size [%d,%d]", mat->columns, mat->rows);
        util_PrintMatrixError(s);
      #endif

      return 0;
    }
  #endif

  float trace = 0;

  for (unsigned int i = 0; i < mat->rows; i++)
  {
    #if defined(BCI_MATRIX_O0)
      trace += matrix_Get(mat, i, i);
    #elif defined(BCI_MATRIX_O1)
      trace += matrix_Get_Inline_2(mat, i, i);
    #elif defined(BCI_MATRIX_O2)
      trace += matrix_Get_Inline_3(mat, i, i);
    #endif
  }

  return trace;
}

float matrix_Determinant(const matrix *mat)
{
  #if defined(BCI_MATRIX_O0)
    if (mat->columns != mat->rows)
    {
      #ifdef BCI_MATRIX_DEBUG
        string s;
        sprintf(s, "Determinant: Cannot calculate determinant for non-square matrix of size [%d,%d]", mat->columns, mat->rows);
        util_PrintMatrixError(s);
      #endif

      return 0;
    }
  #endif

  float sumOfDet;
  matrix detMat;
  int multiplier, col, row, index, i;

  switch (mat->rows)
  {
    case 1:
    {
      #if defined(BCI_MATRIX_O0)
        return matrix_Get(mat, 0, 0);
      #elif defined(BCI_MATRIX_O1)
        return matrix_Get_Inline_2(mat, 0, 0);
      #elif defined(BCI_MATRIX_O2)
        return matrix_Get_Inline_3(mat, 0, 0);
      #endif
    }

    case 2:
    {
      #if defined(BCI_MATRIX_O0)
        return matrix_Get(mat, 0, 0) * matrix_Get(mat, 1, 1) - matrix_Get(mat, 1, 0) * matrix_Get(mat, 0, 1);
      #elif defined(BCI_MATRIX_O1)
        return matrix_Get_Inline_2(mat, 0, 0) * matrix_Get_Inline_2(mat, 1, 1) - matrix_Get_Inline_2(mat, 1, 0) * matrix_Get_Inline_2(mat, 0, 1);
      #elif defined(BCI_MATRIX_O2)
        return matrix_Get_Inline_3(mat, 0, 0) * matrix_Get_Inline_3(mat, 1, 1) - matrix_Get_Inline_3(mat, 1, 0) * matrix_Get_Inline_3(mat, 0, 1);
      #endif
    }

    case 3:
    {
      #if defined(BCI_MATRIX_O0)
        return matrix_Get(mat, 0, 0) * (matrix_Get(mat, 1, 1) * matrix_Get(mat, 2, 2) - matrix_Get(mat, 1, 2) * matrix_Get(mat, 2, 1)) -
               matrix_Get(mat, 0, 1) * (matrix_Get(mat, 1, 0) * matrix_Get(mat, 2, 2) - matrix_Get(mat, 1, 2) * matrix_Get(mat, 2, 0)) +
               matrix_Get(mat, 0, 2) * (matrix_Get(mat, 1, 0) * matrix_Get(mat, 2, 1) - matrix_Get(mat, 1, 1) * matrix_Get(mat, 2, 1));
      #elif defined(BCI_MATRIX_O1)
        return matrix_Get_Inline_2(mat, 0, 0) * (matrix_Get_Inline_2(mat, 1, 1) * matrix_Get_Inline_2(mat, 2, 2) - matrix_Get_Inline_2(mat, 1, 2) * matrix_Get_Inline_2(mat, 2, 1)) -
               matrix_Get_Inline_2(mat, 0, 1) * (matrix_Get_Inline_2(mat, 1, 0) * matrix_Get_Inline_2(mat, 2, 2) - matrix_Get_Inline_2(mat, 1, 2) * matrix_Get_Inline_2(mat, 2, 0)) +
               matrix_Get_Inline_2(mat, 0, 2) * (matrix_Get_Inline_2(mat, 1, 0) * matrix_Get_Inline_2(mat, 2, 1) - matrix_Get_Inline_2(mat, 1, 1) * matrix_Get_Inline_2(mat, 2, 1));
      #elif defined(BCI_MATRIX_O2)
        return matrix_Get_Inline_3(mat, 0, 0) * (matrix_Get_Inline_3(mat, 1, 1) * matrix_Get_Inline_3(mat, 2, 2) - matrix_Get_Inline_3(mat, 1, 2) * matrix_Get_Inline_3(mat, 2, 1)) -
               matrix_Get_Inline_3(mat, 0, 1) * (matrix_Get_Inline_3(mat, 1, 0) * matrix_Get_Inline_3(mat, 2, 2) - matrix_Get_Inline_3(mat, 1, 2) * matrix_Get_Inline_3(mat, 2, 0)) +
               matrix_Get_Inline_3(mat, 0, 2) * (matrix_Get_Inline_3(mat, 1, 0) * matrix_Get_Inline_3(mat, 2, 1) - matrix_Get_Inline_3(mat, 1, 1) * matrix_Get_Inline_3(mat, 2, 1));
      #endif
    }

    default:
    {
      sumOfDet = 0;
      matrix_Initialize(&detMat, mat->rows-1, mat->columns-1);

      multiplier = 1;
      for(col = 0; col < mat->columns; col++)
      {
        index = 0;
        for(i = 0; i < mat->columns; i++)
        {
          if(col != i)
          {
            for(row = 1; row < mat->rows; row++)
            {
              #if defined(BCI_MATRIX_O0)
                matrix_Set(&detMat, index, row-1, matrix_Get(mat, i, row));
              #elif defined(BCI_MATRIX_O1)
                matrix_Set_Inline_2((&detMat), index, row-1, matrix_Get_Inline_2(mat, i, row));
              #elif defined(BCI_MATRIX_O2)
                matrix_Set_Inline_2((&detMat), index, row-1, matrix_Get_Inline_3(mat, i, row));
              #endif
            }
            index++;
          }
        }

        #if defined(BCI_MATRIX_O0)
          sumOfDet += multiplier * matrix_Get(mat, col, 0) * matrix_Determinant(&detMat);
        #elif defined(BCI_MATRIX_O1)
          sumOfDet += multiplier * matrix_Get_Inline_2(mat, col, 0) * matrix_Determinant(&detMat);
        #elif defined(BCI_MATRIX_O2)
          sumOfDet += multiplier * matrix_Get_Inline_2(mat, col, 0) * matrix_Determinant(&detMat);
        #endif

        multiplier *= -1;
      }

      matrix_Free(&detMat);

      return sumOfDet;
    }
  }
}

bool matrix_Invert(const matrix *mat, matrix *result)
{
  #if defined(BCI_MATRIX_O0)
    if (mat->columns != mat->rows)
    {
      #ifdef BCI_MATRIX_DEBUG
        string s;
        sprintf(s, "Invert: Cannot invert matrix of size [%d,%d]", mat->columns, mat->rows);
        util_PrintMatrixError(s);
      #endif

      return false;
    }
    else if (result->rows != mat->rows || result->columns != mat->columns)
    {
      #ifdef BCI_MATRIX_DEBUG
        string s;
        sprintf(s, "Invert: Cannot invert matrix of size [%d,%d] into result matrix of size [%d,%d]", mat->columns, mat->rows, result->columns, result->rows);
        util_PrintMatrixError(s);
      #endif

      return false;
    }
  #endif

  matrix tmp, tmp2;
  float det;

  if (mat->rows == 1)
  {
    #if defined(BCI_MATRIX_O0)
      matrix_Set(result, 0, 0, 1.0 / matrix_Get(mat, 0, 0));
    #elif defined(BCI_MATRIX_O1)
      matrix_Set_Inline_2(result, 0, 0, 1.0 / matrix_Get_Inline_2(mat, 0, 0));
    #elif defined(BCI_MATRIX_O2)
      matrix_Set_Inline_3(result, 0, 0, 1.0 / matrix_Get_Inline_3(mat, 0, 0));
    #endif
    return true;
  }

  matrix_Initialize(&tmp, mat->columns, mat->rows);
  matrix_Initialize(&tmp2, mat->columns, mat->rows);

  matrix_Cofactor(mat, tmp);
  matrix_Transpose(tmp, tmp2);
  det = matrix_Determinant(mat);

  if (det == 0)
  {
    matrix_Free(&tmp);
    matrix_Free(&tmp2);
    return false;
  }

  matrix_DivideByScalar(&tmp2, det, &tmp);
  matrix_Copy(&tmp, result);

  matrix_Free(&tmp);
  matrix_Free(&tmp2);
  return true;
}

void matrix_Clear(matrix *mat, float clearVal)
{
  for (unsigned int i = 0; i < mat->rows; i++)
  {
    for (unsigned int j = 0; j < mat->columns; j++)
    {
      #if defined(BCI_MATRIX_O0)
        matrix_Set(mat, i, j, clearVal);
      #elif defined(BCI_MATRIX_O1)
        matrix_Set_Inline_2(mat, i, j, clearVal);
      #elif defined(BCI_MATRIX_O2)
        matrix_Set_Inline_3(mat, i, j, clearVal);
      #endif
    }
  }
}

#endif //BCI_MATRIX_C_INCLUDED
