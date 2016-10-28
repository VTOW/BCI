#ifndef BCI_HEAP_H_INCLUDED
#define BCI_HEAP_H_INCLUDED

#ifndef BCI_HEAP_SIZE
#define BCI_HEAP_SIZE 1000
#endif //BCI_HEAP_SIZE

typedef stuct matrix_t
{
  float width;
  float height;
  float *data;
} matrix;

/**
 * Initializes the heap
 */
void heap_init();

/**
 * Allocates memory on the heap
 * @param  size      Number of floats to allocate
 * @param  recursive Internal parameter - Do not use
 * @return           Memory reference
 */
float* heap_malloc(const unsigned int size, bool recursive = false);

/**
 * Allocates a matrix on the heap
 * @param  width  Width of matrix
 * @param  height Height of matrix
 * @return        Matrix reference
 */
matrix* heap_matrix_malloc(const unsigned int width, const unsigned int height);

/**
 * Frees memory
 * @param loc  Location to free from
 * @param size Length to free
 */
void heap_free(const unsigned int loc, const unsigned int size);

/**
 * Frees a matrix
 * @param mat Matrix to free
 */
void heap_free_matrix(matrix *mat);

/**
 * Prints a range of the heap
 * @param loc  Location to print from
 * @param size Length to print
 */
void heap_print(const unsigned int loc, const unsigned int size);

/**
 * Prints diagnostics for a range of the heap
 * @param loc  Location to print from
 * @param size Length to print
 */
void heap_printStats(const unsigned int loc, const unsigned int size);

#endif //BCI_HEAP_H_INCLUDED
