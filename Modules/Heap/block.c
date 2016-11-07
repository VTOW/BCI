#ifndef BCI_BLOCK_C_INCLUDED
#define BCI_BLOCK_C_INCLUDED

#include "block.h"

bool block_Initialize(block *b, const unsigned int size)
{
  b->loc = heap_Malloc(size);

  #ifdef BCI_HEAP_DEBUG
    if (b->loc == BCI_HEAP_FAIL)
    {
      writeDebugStreamLine("BCI HEAP ERROR: block_Initialize: No space for new block of size: %d", size);
      return false;
    }
  #endif

  b->size = size;
  return true;
}

bool block_Expand(block *b, const unsigned int expand)
{
  int result = heap_Expand(b->loc, b->size, expand);

  //Expand went fine
  if (result == BCI_HEAP_SUCCESS)
  {
    b->size += expand;
    return true;
  }
  //Expand failed
  else if (result == BCI_HEAP_FAIL)
  {
    #ifdef BCI_HEAP_DEBUG
      writeDebugStreamLine("BCI HEAP ERROR: block_Expand: No space for to expand block of size: %d by: %d", b->size, expand);
    #endif

    return false;
  }
  //Expand had to reallocate the block
  else
  {
    b->loc = result;
    b->size += expand;
    return true;
  }
}

#endif //BCI_BLOCK_C_INCLUDED
