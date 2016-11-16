#ifndef BCI_MATRIX_H_INCLUDED
#define BCI_MATRIX_H_INCLUDED

#if !defined(BCI_MATRIX_O0) && !defined(BCI_MATRIX_O1) && !defined(BCI_MATRIX_O2)
  #define BCI_MATRIX_O0
#endif

typedef struct matrix_t
{
  unsigned int columns;
  unsigned int rows;
  block data;
} matrix;

 /**
  * Initializes a matrix
  * @param  mat          matrix to initialze
  * @param  columns      Columns
  * @param  rows         Rows
  * @param  defaultValue Value to initialze the elements to
  * @return              Whether the matrix was initialized successfully
  */
bool matrix_Initialize(matrix *mat, const unsigned int columns, const unsigned int rows, float defaultValue = 0);

/**
 * Frees a matrix
 * @param mat matrix to free
 */
void matrix_Free(matrix *mat);

/**
 * Sets the elements of a matrix from an arry
 * @param mat  matrix to write to
 * @param data Array of new data
 */
void matrix_Set(matrix *mat, const float *data);

/**
 * Sets an element of a matrix
 * @param mat  matrix to write to
 * @param x    Number of columns in
 * @param y    Number of rows in
 * @param data New data
 */
void matrix_Set(matrix *mat, const unsigned int x, const unsigned int y, const float data);

/**
 * Gets an element of a matrix
 * @param mat  matrix to read from
 * @param x    Number of columns in
 * @param y    Number of rows in
 */
float matrix_Get(const matrix *mat, const unsigned int x, const unsigned int y);

/**
 * Copies one matrix to another
 * @param from matrix to copy from
 * @param to   matrix to copy to
 */
void matrix_Copy(const matrix *from, matrix *to);

/**
 * Adds a scalar to every element of a matrix
 * @param mat    matrix to read from
 * @param scalar Scalar
 * @param result matrix to write result to
 */
void matrix_AddScalar(const matrix *mat, const float scalar, matrix *result);

/**
 * Subtracts a scalar to every element of a matrix
 * @param mat    matrix to read from
 * @param scalar Scalar
 * @param result matrix to write result to
 */
void matrix_SubtractScalar(const matrix *mat, const float scalar, matrix *result);

/**
 * Multiplies a matrix by a scalar
 * @param mat    matrix to read from
 * @param scalar Scalar
 * @param result matrix to write result to
 */
void matrix_MultiplyByScalar(const matrix *mat, const float scalar, matrix *result);

/**
 * Divides a matrix by a scalar
 * @param mat    matrix to read from
 * @param scalar Scalar
 * @param result matrix to write result to
 */
void matrix_DivideByScalar(const matrix *mat, const float scalar, matrix *result);

/**
 * Raises a matrix to a power
 * @param mat    matrix to read from
 * @param scalar Scalar
 * @param result matrix to write result to
 */
void matrix_RaiseToScalar(const matrix *mat, const float scalar, matrix *result);

/**
 * Adds two matricies together
 * @param mat1   First matrix
 * @param mat2   Second matrix
 * @param result matrix to write result to
 */
void matrix_AddMatrix(const matrix *mat1, const matrix *mat2, matrix *result);

/**
 * Subtracts two matricies from each other
 * @param mat1   First matrix
 * @param mat2   Second matrix
 * @param result matrix to write result to
 */
void matrix_SubtractMatrix(const matrix *mat1, const matrix *mat2, matrix *result);

/**
 * Multiplies two matricies together
 * @param mat1   First matrix
 * @param mat2   Second matrix
 * @param result matrix to write result to
 */
void matrix_MultiplyByMatrix(const matrix *mat1, const matrix *mat2, matrix *result);

/**
 * Transposes a matrix
 * @param mat    matrix to read from
 * @param result matrix to write to
 */
void matrix_Transpose(const matrix *mat, matrix *result);

/**
 * Calculates the matrix of minors
 * @param  mat    matrix to read from
 * @param  result matrix to write to
 * @return        Whether the operation was successful
 */
bool matrix_Minors(const matrix *mat, matrix *result);

/**
 * Calculates the cofactor matrix
 * @param  mat    matrix to read from
 * @param  result matrix to write to
 * @return        Whether the operation was successful
 */
bool matrix_Cofactor(const matrix *mat, matrix *result);

/**
 * Returns the trace of a square matrix
 * @param  mat Square matrix to read from
 * @return     The trace of the matrix
 */
float matrix_Trace(const matrix *mat);

/**
 * Returns the determinant of a square matrix
 * @param  mat Square matrix to read from
 * @return     The determinant of that matrix
 */
float matrix_Determinant(const matrix *mat);

/**
 * Inverts a matrix
 * @param mat    matrix to read from
 * @param result matrix to write to
 * @return       Whether the matrix is invertible
 */
bool matrix_Invert(const matrix *mat, matrix *result);

/**
 * Clears a matrix
 * @param mat      matrix to clear
 * @param clearVal Value to clear the elements to
 */
void matrix_Clear(matrix *mat, float clearVal = 0);

#endif //BCI_MATRIX_H_INCLUDED
