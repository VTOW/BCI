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
 * Allocates memory on the heap. Allocating a block of size <= 0 will return
 * BCI_HEAP_FAIL. ALlocating a block of size >= BCI_HEAP_SIZE will return
 * BCI_HEAP_FAIL
 * @param  size         Length of block
 * @param  initialValue Value to initialize block elements to
 * @return              Index of the start of the block
 */
int heap_Malloc(const unsigned int size, float initialValue = 0);

/**
 * Reallocates a block. Do not try to reallocate from the middle of a block,
 * this is undefined behaviour
 * @param  loc   Start of block
 * @param  size  Length of block
 * @param expand Size to increase block by
 * @return       New index of the block
 */
int heap_Realloc(const unsigned int loc, const unsigned int size, const unsigned int expand);

/**
 * Expands the size of a block on the heap. This function may call heap_Realloc
 * if it can't find enough contiguous free elements to expand into. Do not try
 * to expand from the middle of a block, this is undefined behaviour
 * @param  loc   Start of block
 * @param  size  Length of block
 * @param expand Size to increase block by
 * @return       Whether the block was expanded successfully, or the index of
 *               the reallocated block
 */
int heap_Expand(const unsigned int loc, const unsigned int size, const unsigned int expand);

/**
 * Returns the data at a location in the heap
 * @param  loc Location in the heap
 * @return     Data at the location
 */
float heap_Get(const unsigned int loc);

/**
 * Sets an element of a block
 * @param  loc  Location in the heap
 * @param  data Element to set to
 * @return      Whether the element was set successfully
 */
bool heap_Set(const unsigned int loc, const float data);

/**
 * Frees a block
 * @param loc  Start of block
 * @param size Length of block
 * @return     Whether the free was successful
 */
bool heap_Free(const unsigned int loc, const unsigned int size);

/**
 * Shrinks a block
 * @param  loc           Start of block
 * @param  size          Length of block
 * @param  shrink        Length to shrink block by
 * @param  shrinkFromEnd Whether to shrink from the end of the block (if true,
 *                       shrink from end; if false, shrink from front)
 * @return               Whether the shrink was successful
 */
bool heap_Shrink(const unsigned int loc, const unsigned int size, const unsigned int shrink, bool shrinkFromEnd = true);

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
