#ifndef BCI_BLOCK_C_INCLUDED
#define BCI_BLOCK_C_INCLUDED

#include "block.h"

bool block_Initialize(block *b, const unsigned int size, float defaultValue)
{
  b->loc = heap_Malloc(size, defaultValue);

  if (b->loc == BCI_HEAP_FAIL)
  {
    #ifdef BCI_BLOCK_DEBUG
      string s;
      sprintf(s, "Initialize: No space for new block of size: %d", size);
      util_PrintBlockError(s);
    #endif

    return false;
  }

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
    #ifdef BCI_BLOCK_DEBUG
      string s;
      sprintf(s, "Expand: No space for to expand block of size: %d by: %d", b->size, expand);
      util_PrintBlockError(s);
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

float block_Get(const block *b, const unsigned int loc)
{
  //Bounds check
  if (loc < 0 || loc >= b->size)
  {
    #ifdef BCI_BLOCK_DEBUG
      string s;
      sprintf(s, "Get: Invalid location: %d", loc);
      util_PrintBlockError(s);
    #endif

    return BCI_HEAP_FAIL;
  }

  return heap_Get(b->loc + loc);
}

//Inline version of block_Get
#define block_Get_Inline(b, offset) heap_Get(b->loc + offset)
#define block_Get_Inline_NoPtr(b, offset) heap_Get(b.loc + offset)
#define block_Get_Inline_Deep(b, offset) heap_Get_Inline_Deep(b->loc + offset)
#define block_Get_Inline_Deep_NoPtr(b, offset) heap_Get_Inline_Deep(b.loc + offset)

bool block_Set(block *b, const unsigned int loc, const float data)
{
  //Bounds check
  if (loc < 0 || loc >= b->size)
  {
    #ifdef BCI_BLOCK_DEBUG
      string s;
      sprintf(s, "Set: Invalid location: %d", loc);
      util_PrintBlockError(s);
    #endif

    return false;
  }

  return heap_Set(b->loc + loc, data);
}

//Inline version of block_Set
#define block_Set_Inline(b, offset, data) heap_Set(b->loc + offset, data)
#define block_Set_Inline_NoPtr(b, offset, data) heap_Set(b.loc + offset, data)
#define block_Set_Inline_Deep(b, offset, data) heap_Set_Inline_Deep(b->loc + offset, data)
#define block_Set_Inline_Deep_NoPtr(b, offset, data) heap_Set_Inline_Deep(b.loc + offset, data)

bool block_Free(block *b)
{
  return heap_Free(b->loc, b->size);
}

bool block_Shrink(block *b, const unsigned int shrink, bool shrinkFromEnd)
{
  if (heap_Shrink(b->loc, b->size, shrink, shrinkFromEnd))
  {
    //We need to adjust start index if we shrunk from the front
    if (!shrinkFromEnd)
    {
      b->loc += shrink;
    }

    b->size -= shrink;
    return true;
  }

  return false;
}

#endif //BCI_BLOCK_C_INCLUDED
