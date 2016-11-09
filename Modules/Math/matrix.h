#ifndef BCI_MATRIX_H_INCLUDED
#define BCI_MATRIX_H_INCLUDED

typedef struct matrix_t
{
  int columns;
  int rows;
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

//--------------------------------------------------------------
//These functions save the result to a separate matrix passed in
//Consequently, they use space O(1)
//--------------------------------------------------------------

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
 * Inverts a matrix
 * @param mat    matrix to read from
 * @param result matrix to write to
 */
void matrix_Invert(const matrix *mat, matrix *result);

/**
 * Transposes a matrix
 * @param mat    matrix to read from
 * @param result matrix to write to
 */
void matrix_Transpose(const matrix *mat, matrix *result);

//------------------------------------------------------------
//These functions save the result to the same matrix passed in
//Consequently, they use space O(n)
//------------------------------------------------------------

/**
 * Adds a scalar to every element of a matrix
 * @param mat    matrix for read/write
 * @param scalar Scalar
 */
void matrix_AddScalar(matrix *mat, const float scalar);

/**
 * Subtracts a scalar to every element of a matrix
 * @param mat    matrix for read/write
 * @param scalar Scalar
 */
void matrix_SubtractScalar(matrix *mat, const float scalar);

/**
 * Multiplies a matrix by a scalar
 * @param mat    matrix for read/write
 * @param scalar Scalar
 */
void matrix_MultiplyByScalar(matrix *mat, const float scalar);

/**
 * Divides a matrix by a scalar
 * @param mat    matrix for read/write
 * @param scalar Scalar
 */
void matrix_DivideByScalar(matrix *mat, const float scalar);

/**
 * Raises a matrix to a power
 * @param mat    matrix for read/write
 * @param scalar Scalar
 */
void matrix_RaiseToScalar(matrix *mat, const float scalar);

/**
 * Adds two matricies together
 * @param mat1   First matrix
 * @param mat2   Second matrix
 */
void matrix_AddMatrix(matrix *mat1, const matrix *mat2);

/**
 * Subtracts two matricies from each other
 * @param mat1   First matrix
 * @param mat2   Second matrix
 */
void matrix_SubtractMatrix(matrix *mat1, const matrix *mat2);

/**
 * Multiplies two matricies together
 * @param mat1   First matrix
 * @param mat2   Second matrix
 */
void matrix_MultiplyByMatrix(matrix *mat1, const matrix *mat2);

/**
 * Inverts a matrix
 * @param mat    matrix for read/write
 */
void matrix_Invert(matrix *mat);

/**
 * Transposes a matrix
 * @param mat    matrix for read/write
 */
void matrix_Transpose(matrix *mat);

//-----------------------------------------------------------

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
 * Clears a matrix
 * @param mat      matrix to clear
 * @param clearVal Value to clear the elements to
 */
void matrix_Clear(matrix *mat, float clearVal = 0);

#endif //BCI_MATRIX_H_INCLUDED
