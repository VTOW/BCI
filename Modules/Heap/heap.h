#ifndef BCI_HEAP_H_INCLUDED
#define BCI_HEAP_H_INCLUDED

#ifndef BCI_HEAP_SIZE
  #define BCI_HEAP_SIZE 1000
#endif

/**
 * Initializes the heap
 */
void heap_Init();

/**
 * Allocates memory on the heap
 * @param  size      Size of block
 * @return           Index of the start of the block
 */
int heap_Malloc(const unsigned int size);

/**
 * Expands the size of a block on the heap
 * @param  loc   Location in the heap
 * @param  size  Size of block
 * @param expand Size to increase block by
 * @return       Whether the block was expanded successfully
 */
bool heap_Expand(const unsigned int loc, const unsigned int size, const unsigned int expand);

/**
 * Returns the data at a location in the heap
 * @param  loc Location in the heap
 * @return     Data at the location
 */
float heap_Get(const unsigned int loc);

/**
 * Sets an element of the heap
 * @param  loc  Location in the heap
 * @param  data Element to set to
 * @return      Whether the element was set successfully
 */
bool heap_Set(const unsigned int loc, const float data);

/**
 * Frees memory
 * @param loc  Location to free from
 * @param size Length to free
 * @return     Whether the free was successful
 */
bool heap_Free(const unsigned int loc, const unsigned int size);

/**
 * Prints a range of the heap
 * @param loc  Location to print from
 * @param size Length to print
 */
void heap_Print(const unsigned int loc, const unsigned int size);

/**
 * Prints diagnostics for a range of the heap
 * @param loc  Location to print from
 * @param size Length to print
 */
void heap_PrintStats(const unsigned int loc, const unsigned int size);

#endif //BCI_HEAP_H_INCLUDED
