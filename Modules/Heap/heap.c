#ifndef BCI_HEAP_C_INCLUDED
#define BCI_HEAP_C_INCLUDED

#include "heap.h"

//Using BNS Error code here as a flag
//https://github.com/JMarple/BNSLibrary/blob/master/Modules/Core/BNSHeap.h
//0000 1010 1010 0000 0000 0000 0000 0000
#define BCI_FREE_FLAG 178257920

//0101 0101 0000 0000 0000 0000 0000 0000
#define BCI_HEAP_FAIL 1426063360

//0010 1010 1000 0000 0000 0000 0000 0000
#define BCI_HEAP_SUCCESS 713031680

//Headers
bool heap_SetFreeFlags(const unsigned int startLoc, const unsigned int len);

static float bciHeap[BCI_HEAP_SIZE];

void heap_Init()
{
  heap_SetFreeFlags(0, BCI_HEAP_SIZE);
}

//Set free flags for a block
bool heap_SetFreeFlags(const unsigned int startLoc, const unsigned int len)
{
  //Bounds check
  if (startLoc < 0)
  {
    #ifdef BCI_HEAP_DEBUG
      string s;
      sprintf(s, "SetFreeFlags: Invalid location: %d", startLoc);
      util_PrintHeapError(s);
    #endif

    return false;
  }
  else if (startLoc + len > BCI_HEAP_SIZE)
  {
    #ifdef BCI_HEAP_DEBUG
      string s;
      sprintf(s, "SetFreeFlags: Invalid end location: %d", startLoc + len);
      util_PrintHeapError(s);
    #endif

    return false;
  }

  for (unsigned int j = 0; j < len; j++)
  {
    //Set flag
    bciHeap[startLoc + j] = BCI_FREE_FLAG;
  }

  return true;
}

//Clear the free flags for a block
bool heap_ClearFreeFlags(const unsigned int startLoc, const unsigned int len, float initialValue = 0)
{
  //Bounds check
  if (startLoc < 0)
  {
    #ifdef BCI_HEAP_DEBUG
      string s;
      sprintf(s, "ClearFreeFlags: Invalid location: %d", startLoc);
      util_PrintHeapError(s);
    #endif

    return false;
  }
  else if (startLoc + len > BCI_HEAP_SIZE)
  {
    #ifdef BCI_HEAP_DEBUG
      string s;
      sprintf(s, "ClearFreeFlags: Invalid end location: %d", startLoc + len);
      util_PrintHeapError(s);
    #endif

    return false;
  }

  for (unsigned int j = 0; j < len; j++)
  {
    //Clear flag
    bciHeap[startLoc + j] = initialValue;
  }

  return true;
}

//Walk and allocate a block
int heap_Walk(const unsigned int startLoc, const unsigned int len, float initialValue = 0)
{
  unsigned int i = startLoc, runLength = 0;
  while (true)
  {
    //Empty flag
    if (bciHeap[i] == BCI_FREE_FLAG)
    {
      runLength++;
    }
    else
    {
      runLength = 0;
    }

    //If block is long enough, use it
    if (runLength == len)
    {
      //Clear free flags
      heap_ClearFreeFlags(i - runLength + 1, runLength, initialValue);

      //Return index of block
      return i - runLength + 1;
    }

    //If we've gone down the entire heap
    if (i == BCI_HEAP_SIZE - 1)
    {
      #ifdef BCI_HEAP_DEBUG
        string s;
        sprintf(s, "Walk: No space for malloc of length: %d at start index: %d", len, startLoc);
        util_PrintHeapError(s);
      #endif

      return BCI_HEAP_FAIL;
    }

    i++;
  }
}

//Walk heap without allocating
unsigned int heap_FindBlock(const unsigned int startLoc, const unsigned int len, unsigned int max = BCI_HEAP_SIZE)
{
  //Bounds check
  if (startLoc < 0 || startLoc >= BCI_HEAP_SIZE)
  {
    #ifdef BCI_HEAP_DEBUG
      string s;
      sprintf(s, "FindBlock: Invalid location: %d", startLoc);
      util_PrintHeapError(s);
    #endif

    return BCI_HEAP_FAIL;
  }
  else if (startLoc + len > BCI_HEAP_SIZE)
  {
    #ifdef BCI_HEAP_DEBUG
      string s;
      sprintf(s, "FindBlock: Impossible to find block of length: %d for start location: %d", len, startLoc);
      util_PrintHeapError(s);
    #endif

    return BCI_HEAP_FAIL;
  }

  unsigned int i = startLoc, runLength = 0;
  while (true)
  {
    //Empty flag
    if (bciHeap[i] == BCI_FREE_FLAG)
    {
      runLength++;
    }
    else
    {
      runLength = 0;
    }

    //If block is long enough, use it
    if (runLength == len)
    {
      //Return index of block
      return i - runLength + 1;
    }

    //If we've gone down the entire heap
    if (i == BCI_HEAP_SIZE - 1)
    {
      #ifdef BCI_HEAP_DEBUG
        string s;
        sprintf(s, "FindBlock: No block found of length: %d at start index: %d", len, startLoc);
        util_PrintHeapError(s);
      #endif

      return BCI_HEAP_FAIL;
    }
    //If we've gone too far
    else if (i - startLoc == max)
    {
      #ifdef BCI_HEAP_DEBUG
        string s;
        sprintf(s, "FindBlock: No block found of length: %d at start index: %d for max: %d", len, startLoc, max);
        util_PrintHeapError(s);
      #endif

      return BCI_HEAP_FAIL;
    }

    i++;
  }
}

int heap_Malloc(const unsigned int size, float initialValue)
{
  #ifdef BCI_HEAP_DEBUG
    int out = heap_Walk(0, size, initialValue);
    if (out == BCI_HEAP_FAIL)
    {
      string s;
      sprintf(s, "Malloc: No space for malloc of length: %d", size);
      util_PrintHeapError(s);
    }
    return out;
  #else
    return heap_Walk(0, size, initialValue);
  #endif
}

int heap_Realloc(const unsigned int loc, const unsigned int size, const unsigned int expand)
{
  //Find a new block to allocate into
  int newBlock;
  if ((newBlock = heap_Malloc(size + expand)) != BCI_HEAP_FAIL)
  {
    //Move data into new block
    for (unsigned int i = loc; i < loc + size; i++)
    {
      bciHeap[newBlock + i - loc] = bciHeap[i];
    }

    //Clear old block
    heap_SetFreeFlags(loc, size);

    return newBlock;
  }

  return BCI_HEAP_FAIL;
}

int heap_Expand(const unsigned int loc, const unsigned int size, const unsigned int expand)
{
  //Bounds check
  if (loc < 0 || loc >= BCI_HEAP_SIZE)
  {
    #ifdef BCI_HEAP_DEBUG
      string s;
      sprintf(s, "Expand: Invalid location: %d", loc);
      util_PrintHeapError(s);
    #endif

    return BCI_HEAP_FAIL;
  }

  if  (size == 0)
  {
    return heap_Malloc(1);
  }
  //Try to find a block below to expand into
  else if (heap_FindBlock(loc + size - 1, expand) == loc + size)
  {
    //There is a block to expand into, use it
    heap_ClearFreeFlags(loc + size, expand);
    return BCI_HEAP_SUCCESS;
  }
  //Try to find a block above to shift into
  else if (loc - expand >= 0 && heap_FindBlock(loc - expand, expand) == loc - expand)
  {
    //There is a block to expand into, use it
    heap_ClearFreeFlags(loc - expand, expand);

    //Shift data upwards
    for (unsigned int i = loc; i < loc + size; i++)
    {
      bciHeap[i - expand] = bciHeap[i];
    }

    //Return new index
    return loc - expand;
  }
  //Else, there isn't a block
  //Reallocate entire block
  else
  {
    writeDebugStreamLine("realloc");
    return heap_Realloc(loc, size, expand);
  }
}

float heap_Get(const unsigned int loc)
{
  //Bounds check
  if (loc < 0 || loc >= BCI_HEAP_SIZE)
  {
    #ifdef BCI_HEAP_DEBUG
      string s;
      sprintf(s, "Get: Invalid location: %d", loc);
      util_PrintHeapError(s);
    #endif

    return BCI_HEAP_FAIL;
  }

  return bciHeap[loc];
}

//Inline version of heap_Get
#define heap_Get_Inline(loc) bciHeap[loc]
#define heap_Get_Inline_Deep(loc) bciHeap[loc]

bool heap_Set(const unsigned int loc, const float data)
{
  //Bounds check
  if (loc < 0 || loc >= BCI_HEAP_SIZE)
  {
    #ifdef BCI_HEAP_DEBUG
      string s;
      sprintf(s, "Set: Invalid location: %d", loc);
      util_PrintHeapError(s);
    #endif

    return false;
  }

  bciHeap[loc] = data;
  return true;
}

//Inline version of heap_Set
#define heap_Set_Inline(loc, data) bciHeap[loc] = data
#define heap_Set_Inline_Deep(loc, data) bciHeap[loc] = data

bool heap_Free(const unsigned int loc, const unsigned int size)
{
  //Bounds check
  if (loc < 0 || loc >= BCI_HEAP_SIZE)
  {
    #ifdef BCI_HEAP_DEBUG
      string s;
      sprintf(s, "Free: Invalid location: %d", loc);
      util_PrintHeapError(s);
    #endif

    return false;
  }
  else if (loc + size >= BCI_HEAP_SIZE)
  {
    #ifdef BCI_HEAP_DEBUG
      string s;
      sprintf(s, "Free: Invalid end location: %d", size);
      util_PrintHeapError(s);
    #endif

    return false;
  }

  for (unsigned int i = loc; i < loc + size; i++)
  {
    bciHeap[i] = BCI_FREE_FLAG;
  }

  return true;
}

bool heap_Shrink(const unsigned int loc, const unsigned int size, const unsigned int shrink, bool shrinkFromEnd)
{
  //Bounds check
  if (loc < 0 || loc >= BCI_HEAP_SIZE)
  {
    #ifdef BCI_HEAP_DEBUG
      string s;
      sprintf(s, "Shrink: Invalid location: %d", loc);
      util_PrintHeapError(s);
    #endif

    return false;
  }

  if (shrinkFromEnd)
  {
    heap_SetFreeFlags(loc + size - shrink, shrink);
  }
  else
  {
    heap_SetFreeFlags(loc, shrink);
  }

  return true;
}

void heap_Print(const unsigned int loc, const unsigned int size)
{
  //Bounds check
  if (loc < 0 || loc >= BCI_HEAP_SIZE)
  {
    #ifdef BCI_HEAP_DEBUG
      string s;
      sprintf(s, "Print: Invalid location: %d", loc);
      util_PrintHeapError(s);
    #endif
  }
  else if (loc + size > BCI_HEAP_SIZE)
  {
    #ifdef BCI_HEAP_DEBUG
      string s;
      sprintf(s, "Print: Invalid size: %d", size);
      util_PrintHeapError(s);
    #endif
  }

  writeDebugStream("BCI HEAP DUMP:\n");

  for (unsigned int i = loc; i < loc + size; i++)
  {
    if (i == loc)
    {
      if (bciHeap[i] == BCI_FREE_FLAG)
      {
        writeDebugStream("#");
      }
      else
      {
        writeDebugStream("%d", bciHeap[i]);
      }
    }
    else
    {
      if (bciHeap[i] == BCI_FREE_FLAG)
      {
        writeDebugStream(",#");
      }
      else
      {
        writeDebugStream(",%d", bciHeap[i]);
      }
    }
  }

  writeDebugStreamLine("");
}

void heap_PrintStats(const unsigned int loc, const unsigned int size)
{
  //Bounds check
  if (loc < 0 || loc >= BCI_HEAP_SIZE)
  {
    #ifdef BCI_HEAP_DEBUG
      string s;
      sprintf(s, "PrintStats: Invalid location: %d", loc);
      util_PrintHeapError(s);
    #endif
  }
  else if (loc + size > BCI_HEAP_SIZE)
  {
    #ifdef BCI_HEAP_DEBUG
      string s;
      sprintf(s, "PrintStats: Invalid size: %d", size);
      util_PrintHeapError(s);
    #endif
  }

  //Run through the block and record free space
  int freeSpace = 0;
  for (unsigned int i = 0; i < size; i++)
  {
    if (bciHeap[i] == BCI_FREE_FLAG)
    {
      freeSpace++;
    }
  }

  //Print out percent space used, free space, and used space
  writeDebugStreamLine("BCI HEAP STATS:");
  writeDebugStreamLine("Percent used: %1.2f, Used space: %d, Free space: %d", 100 * ((float)(size - freeSpace) / (float)size), size - freeSpace, freeSpace);
}

#endif //BCI_HEAP_C_INCLUDED
