#ifndef BCI_MATRIX_C_INCLUDED
#define BCI_MATRIX_C_INCLUDED

#include "matrix.h"

/**
 * Initializes a matrix
 * @param  mat          matrix to initialze
 * @param  columns      Columns
 * @param  rows         Rows
 * @param  defaultValue Value to initialze the elements to
 * @return              Whether the matrix was initialized successfully
 */
bool matrix_Initialize(matrix *mat, const unsigned int columns, const unsigned int rows, float defaultValue)
{
  mat->columns = columns;
  mat->rows = rows;
  #ifdef BCI_HEAP_DEBUG
    if (!block_Initialize(&(mat->data), columns * rows, defaultValue))
    {
      writeDebugStreamLine("BCI MATRIX ERROR: matrix_Initialize: Cannot initialize matrix with columns: %d and rows: %d", columns, rows);
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
    #ifdef BCI_HEAP_DEBUG
      if (y + (mat->columns * x) >= mat->columns * mat->rows)
      {
        writeDebugStreamLine("BCI MATRIX ERROR: matrix_Set: Invalid location: %d", y + (mat->columns * x));
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

/**
 * Gets an element of a matrix
 * @param mat  matrix to read from
 * @param x    Number of columns in
 * @param y    Number of rows in
 */
float matrix_Get(const matrix *mat, const unsigned int x, const unsigned int y)
{
  #if defined(BCI_MATRIX_O0)
    #ifdef BCI_HEAP_DEBUG
      if (y + (mat->columns * x) >= mat->columns * mat->rows)
      {
        writeDebugStreamLine("BCI MATRIX ERROR: matrix_Set: Invalid location: %d", y + (mat->columns * x));
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

//--------------------------------------------------------------
//These functions save the result to a separate matrix passed in
//Consequently, they use space O(1)
//--------------------------------------------------------------

/**
* Adds a scalar to every element of this matrix
* @param mat    matrix to read from
* @param scalar Scalar
* @param result matrix to write result to
*/
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

/**
* Subtracts a scalar to every element of this matrix
* @param mat    matrix to read from
* @param scalar Scalar
* @param result matrix to write result to
*/
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

/**
* Multiplies a matrix by a scalar
* @param mat    matrix to read from
* @param scalar Scalar
* @param result matrix to write result to
*/
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

/**
* Divides a matrix by a scalar
* @param mat    matrix to read from
* @param scalar Scalar
* @param result matrix to write result to
*/
void matrix_DivideByScalar(const matrix *mat, const float scalar, matrix *result)
{
  #if defined(BCI_MATRIX_O0)
    if (scalar == 0)
    {
      #ifdef BCI_HEAP_DEBUG
        writeDebugStreamLine("BCI MATRIX ERROR: matrix_DivideByScalar: Cannot divide matrix by zero");
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

/**
* Raises a matrix to a power
* @param mat    matrix to read from
* @param scalar Scalar
* @param result matrix to write result to
*/
void matrix_RaiseToScalar(const matrix *mat, const float scalar, matrix *result)
{
  #if defined(BCI_MATRIX_O0)
    if (scalar < 0)
    {
      #ifdef BCI_HEAP_DEBUG
        writeDebugStreamLine("BCI MATRIX ERROR: matrix_RaiseToScalar: Cannot raise matrix to a negative scalar");
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

/**
* Adds two matricies together
* @param mat1   First matrix
* @param mat2   Second matrix
* @param result matrix to write result to
*/
void matrix_AddMatrix(const matrix *mat1, const matrix *mat2, matrix *result)
{
  #if defined(BCI_MATRIX_O0)
    if (mat1->columns != mat2->columns || mat1->rows != mat2->rows)
    {
      #ifdef BCI_HEAP_DEBUG
        writeDebugStreamLine("BCI MATRIX ERROR: matrix_AddMatrix: Cannot add matrices of sizes [%d,%d] and [%d,%d]", mat1->columns, mat1->rows, mat2->columns, mat2->rows);
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

/**
* Subtracts two matricies from each other
* @param mat1   First matrix
* @param mat2   Second matrix
* @param result matrix to write result to
*/
void matrix_SubtractMatrix(const matrix *mat1, const matrix *mat2, matrix *result)
{
  #if defined(BCI_MATRIX_O0)
    if (mat1->columns != mat2->columns || mat1->rows != mat2->rows)
    {
      #ifdef BCI_HEAP_DEBUG
        writeDebugStreamLine("BCI MATRIX ERROR: matrix_SubtractMatrix: Cannot subtract matrices of sizes [%d,%d] and [%d,%d]", mat1->columns, mat1->rows, mat2->columns, mat2->rows);
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

/**
* Multiplies two matricies together. Because this is a very expensive operation,
* multiple optimization options are provided. Only use these option if you are
* sure your matricies can be multiplied together. If an error occurs, it will be
* ignored and the operation will continue incorrectly, corrupting heap memory.
*  - Option BCI_MATRIX_O0 is the default option and does not optimize.
*  - Option BCI_MATRIX_O1 optimizes block access and skips block bounds checks.
*  - Option BCI_MATRIX_O2 contains the previous optimizations, and adds heap
*    access optimizations and skips heap bounds checks.
* @param mat1   First matrix
* @param mat2   Second matrix
* @param result matrix to write result to
*/
void matrix_MultiplyByMatrix(const matrix *mat1, const matrix *mat2, matrix *result)
{
  #if defined(BCI_MATRIX_O0)
    if (mat1->columns != mat2->rows || mat1->rows != mat2->columns)
    {
      #ifdef BCI_HEAP_DEBUG
        writeDebugStreamLine("BCI MATRIX ERROR: matrix_MultiplyByMatrix: Cannot multiply matrices of sizes [%d,%d] and [%d,%d]", mat1->columns, mat1->rows, mat2->columns, mat2->rows);
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

/**
* Inverts a matrix
* @param mat    matrix to read from
* @param result matrix to write to
*/
void matrix_Invert(const matrix *mat, matrix *result)
{
  #if defined(BCI_MATRIX_O0)
    if (mat->columns != mat->rows)
    {
      #ifdef BCI_HEAP_DEBUG
        writeDebugStreamLine("BCI MATRIX ERROR: matrix_Invert: Cannot invert matrix of size [%d,%d]", mat->columns, mat->rows);
      #endif

      return;
    }
    else if (result->rows != mat->rows || result->columns != mat->columns)
    {
      #ifdef BCI_HEAP_DEBUG
        writeDebugStreamLine("BCI MATRIX ERROR: matrix_Invert: Cannot invert matrix of size [%d,%d] into result matrix of size [%d,%d]", mat->columns, mat->rows, result->columns, result->rows);
      #endif

      return;
    }
  #endif
}

/**
* Transposes a matrix
* @param mat    matrix to read from
* @param result matrix to write to
*/
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

/**
* Returns the trace of a square matrix
* @param  mat Square matrix to read from
* @return     The trace of the matrix
*/
float matrix_Trace(const matrix *mat)
{
  #if defined(BCI_MATRIX_O0)
    if (mat->columns != mat->rows)
    {
      #ifdef BCI_HEAP_DEBUG
        writeDebugStreamLine("BCI MATRIX ERROR: matrix_Trace: Cannot calculate trace for non-square matrix of size [%d,%d]", mat->columns, mat->rows);
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

/**
* Returns the determinant of a square matrix
* @param  mat Square matrix to read from
* @return     The determinant of that matrix
*/
float matrix_Determinant(const matrix *mat)
{
  #if defined(BCI_MATRIX_O0)
    if (mat->columns != mat->rows)
    {
      #ifdef BCI_HEAP_DEBUG
        writeDebugStreamLine("BCI MATRIX ERROR: matrix_Determinant: Cannot calculate determinant for non-square matrix of size [%d,%d]", mat->columns, mat->rows);
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

/**
* Clears a matrix
* @param mat      matrix to clear
* @param clearVal Value to clear the elements to
*/
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
