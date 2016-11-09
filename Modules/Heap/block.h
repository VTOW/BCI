#ifndef BCI_BLOCK_H_INCLUDED
#define BCI_BLOCK_H_INCLUDED

typedef struct block_t
{
  unsigned int loc;
  unsigned int size;
} block;

/**
 * Initializes a block
 * @param  b    Block to initialize
 * @param  size Size of block
 * @return      Whether the block was initialized successfully
 */
bool block_Initialize(block *b, const unsigned int size, float defaultValue = 0);

/**
 * Expands the size of a block
 * @param  b     Block to expand
 * @param expand Size to increase block by
 * @return       Whether the block was expanded successfully
 */
bool block_Expand(block *b, const unsigned int expand);

/**
 * Returns the data at a location in the block
 * @param  b   Block to read from
 * @param  loc Location in the block
 * @return     Data at the location
 */
float block_Get(const block *b, const unsigned int loc);

/**
 * Sets an element of a block
 * @param  b    Block to write to
 * @param  loc  Location in the heap
 * @param  data Element to set to
 * @return      Whether the element was set successfully
 */
bool block_Set(block *b, const unsigned int loc, const float data);

/**
 * Frees a block
 * @param  b   Block to free
 * @return     Whether the free was successful
 */
bool block_Free(block *b);

/**
 * Shrinks a block
 * @param  b             Block to free
 * @param  shrink        Length to shrink block by
 * @param  shrinkFromEnd Whether to shrink from the end of the block (if true,
 *                       shrink from end; if false, shrink from front)
 * @return               Whether the shrink was successful
 */
bool block_Shrink(block *b, const unsigned int shrink, bool shrinkFromEnd = true);

#endif //BCI_BLOCK_H_INCLUDED
