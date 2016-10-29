#ifndef BCI_HEAP_H_INCLUDED
#define BCI_HEAP_H_INCLUDED

#ifndef BCI_HEAP_SIZE
  #define BCI_HEAP_SIZE 1000
#endif //BCI_HEAP_SIZE

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
float heap_malloc(const unsigned int size);

/**
 * Frees memory
 * @param loc  Location to free from
 * @param size Length to free
 */
void heap_free(const unsigned int loc, const unsigned int size);

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
