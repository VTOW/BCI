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
      writeDebugStreamLine("BCI HEAP ERROR: matrix_Initialize: Cannot initialize matrix with columns: %d and rows: %d", columns, rows);
      return false;
    }
    return true;
  #else
    return block_Initialize(&(mat->data), columns * rows, defaultValue);
  #endif
}

void matrix_Set(matrix *mat, const float *data)
{
  for (int i = 0; i < mat->columns * mat->rows; i++)
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
        writeDebugStreamLine("BCI HEAP ERROR: matrix_Set: Invalid location: %d", y + (mat->columns * x));
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
        writeDebugStreamLine("BCI HEAP ERROR: matrix_Set: Invalid location: %d", y + (mat->columns * x));
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
  for (int i = 0; i < mat->columns * mat->rows; i++)
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
  for (int i = 0; i < mat->columns * mat->rows; i++)
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
  for (int i = 0; i < mat->columns * mat->rows; i++)
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
        writeDebugStreamLine("BCI HEAP ERROR: matrix_DivideByScalar: Divide by zero error");
      #endif
      return;
    }
  #endif

  for (int i = 0; i < mat->columns * mat->rows; i++)
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
        writeDebugStreamLine("BCI HEAP ERROR: matrix_RaiseToScalar: Negative power error");
      #endif

      return;
    }
  #endif

  for (int i = 0; i < mat->columns * mat->rows; i++)
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
        writeDebugStreamLine("BCI HEAP ERROR: matrix_AddMatrix: Cannot add matrices of sizes [%d,%d] and [%d,%d]", mat1->columns, mat1->rows, mat2->columns, mat2->rows);
      #endif

      return;
    }
  #endif

  for (int i = 0; i < mat1->columns * mat1->rows; i++)
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
        writeDebugStreamLine("BCI HEAP ERROR: matrix_SubtractMatrix: Cannot subtract matrices of sizes [%d,%d] and [%d,%d]", mat1->columns, mat1->rows, mat2->columns, mat2->rows);
      #endif

      return;
    }
  #endif

  for (int i = 0; i < mat1->columns * mat1->rows; i++)
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
        writeDebugStreamLine("BCI HEAP ERROR: matrix_MultiplyByMatrix: Cannot multiply matrices of sizes [%d,%d] and [%d,%d]", mat1->columns, mat1->rows, mat2->columns, mat2->rows);
      #endif

      return;
    }
  #endif

  for (int i = 0; i < mat1->rows; i++)
  {
    for (int j = 0; j < mat2->columns; j++)
    {
      #if defined(BCI_MATRIX_O0)
        block_Set(&(result->data), j + (result->columns * i), 0);
      #elif defined(BCI_MATRIX_O1)
        heap_Set(result->data.loc + j + (result->columns * i), 0);
      #elif defined(BCI_MATRIX_O2)
        bciHeap[result->data.loc + j + (result->columns * i)] = 0;
      #endif

      for (int k = 0; k < mat1->columns; k++)
      {
        #if defined(BCI_MATRIX_O0)
          block_Set(&(result->data),
          j + (result->columns * i),
          block_Get(&(result->data),
             j + (result->columns * i)) +
          block_Get(&(mat1->data),
             k + (mat1->columns * i)) *
          block_Get(&(mat2->data),
             j + (mat2->columns * k)));
        #elif defined(BCI_MATRIX_O1)
          heap_Set(result->data.loc + j + (result->columns * i),
              heap_Get(result->data.loc + j + (result->columns * i)) +
              heap_Get(mat1->data.loc + k + (mat1->columns * i)) *
              heap_Get(mat2->data.loc + j + (mat2->columns * k)));
        #elif defined(BCI_MATRIX_O2)
          bciHeap[result->data.loc + j + (result->columns * i)] =
              bciHeap[result->data.loc + j + (result->columns * i)] +
              bciHeap[mat1->data.loc + k + (mat1->columns * i)] *
              bciHeap[mat2->data.loc + j + (mat2->columns * k)];
        #endif
      }
    }
  }

  // #define TILE 16
  // for (int i = 0; i < mat1->rows; i += TILE)
  // {
  //   for (int j = 0; j < mat2->columns; j += TILE)
  //   {
  //     for (int k = 0; k < mat1->columns; k += TILE)
  //     {
  //       for (int y = i; y < i + TILE; y++)
  //       {
  //         for (int x = j; x < j + TILE; x++)
  //         {
  //           for (int z = k; z < k + TILE; z++)
  //           {
  //             block_Set(&(result->data), x + (result->columns * y), block_Get(&(result->data), x + (result->columns * y)) + block_Get(&(mat1->data), z + (mat1->columns * y)) * block_Get(&(mat2->data), x + (mat2->columns * z)));
  //           }
  //         }
  //       }
  //     }
  //   }
  // }
}

/**
* Inverts a matrix
* @param mat    matrix to read from
* @param result matrix to write to
*/
void matrix_Invert(const matrix *mat, matrix *result)
{
}

/**
* Transposes a matrix
* @param mat    matrix to read from
* @param result matrix to write to
*/
void matrix_Transpose(const matrix *mat, matrix *result)
{
}

//------------------------------------------------------------
//These functions save the result to the same matrix passed in
//Consequently, they use space O(n)
//------------------------------------------------------------

/**
* Adds a scalar to every element of this matrix
* @param mat    matrix for read/write
* @param scalar Scalar
*/
void matrix_AddScalar(matrix *mat, const float scalar)
{
}

/**
* Subtracts a scalar to every element of this matrix
* @param mat    matrix for read/write
* @param scalar Scalar
*/
void matrix_SubtractScalar(matrix *mat, const float scalar)
{
}

/**
* Multiplies a matrix by a scalar
* @param mat    matrix for read/write
* @param scalar Scalar
*/
void matrix_MultiplyByScalar(matrix *mat, const float scalar)
{
}

/**
* Divides a matrix by a scalar
* @param mat    matrix for read/write
* @param scalar Scalar
*/
void matrix_DivideByScalar(matrix *mat, const float scalar)
{
}

/**
* Raises a matrix to a power
* @param mat    matrix for read/write
* @param scalar Scalar
*/
void matrix_RaiseToScalar(matrix *mat, const float scalar)
{
}

/**
* Adds two matricies together
* @param mat1   First matrix
* @param mat2   Second matrix
*/
void matrix_AddMatrix(matrix *mat1, const matrix *mat2)
{
}

/**
* Subtracts two matricies from each other
* @param mat1   First matrix
* @param mat2   Second matrix
*/
void matrix_SubtractMatrix(matrix *mat1, const matrix *mat2)
{
}

/**
* Multiplies two matricies together
* @param mat1   First matrix
* @param mat2   Second matrix
*/
void matrix_MultiplyByMatrix(matrix *mat1, const matrix *mat2)
{
}

/**
* Inverts a matrix
* @param mat    matrix for read/write
*/
void matrix_Invert(matrix *mat)
{
}

/**
* Transposes a matrix
* @param mat    matrix for read/write
*/
void matrix_Transpose(matrix *mat)
{
}

//-----------------------------------------------------------

/**
* Returns the trace of a square matrix
* @param  mat Square matrix to read from
* @return     The trace of the matrix
*/
float matrix_Trace(const matrix *mat)
{
}

/**
* Returns the determinant of a square matrix
* @param  mat Square matrix to read from
* @return     The determinant of that matrix
*/
float matrix_Determinant(const matrix *mat)
{
}

/**
* Clears a matrix
* @param mat      matrix to clear
* @param clearVal Value to clear the elements to
*/
void matrix_Clear(matrix *mat, float clearVal)
{
}

#endif //BCI_MATRIX_C_INCLUDED
