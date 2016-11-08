#ifndef BCI_MATRIX_H_INCLUDED
#define BCI_MATRIX_H_INCLUDED

typedef struct matrix_t
{
  int width;
  int height;
  block data;
}

 /**
  * Initializes a matrix
  * @param  mat          matrix to initialze
  * @param  width        Width
  * @param  height       Height
  * @param  defaultValue Value to initialze the elements to
  * @return              Whether the matrix was initialized successfully
  */
bool matrix_Initialize(matrix *mat, const unsigned int width, const unsigned int height, float defaultValue = 0);

/**
 * Adds a scalar to every element of this matrix
 * @param mat    matrix to read from
 * @param scalar Scalar
 * @param result matrix to write result to
 */
void matrix_AddScalar(const matrix *mat, const float scalar, matrix *result);

/**
 * Subtracts a scalar to every element of this matrix
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
 * Clears a matrix
 * @param mat      matrix to clear
 * @param clearVal Value to clear the elements to
 */
void matrix_Clear(matrix *mat, float clearVal = 0);

#endif //BCI_MATRIX_H_INCLUDED
