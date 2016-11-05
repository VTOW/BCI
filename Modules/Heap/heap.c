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

static float bciHeap[BCI_HEAP_SIZE];

void heap_Init()
{
  for (unsigned int i = 0; i < BCI_HEAP_SIZE; i++)
  {
    bciHeap[i] = BCI_FREE_FLAG;
  }
}

//Clear the free flags for a block
bool heap_ClearFreeFlags(const unsigned int startLoc, const unsigned int len)
{
  for (unsigned int j = 0; j < len; j++)
  {
    //Bounds check
    if (startLoc - j >= BCI_HEAP_SIZE)
    {
      #ifdef BCI_HEAP_DEBUG
        writeDebugStreamLine("BCI HEAP ERROR: heap_ClearFreeFlags: Invalid location: %d", loc);
      #endif

      return false;
    }

    //Clear flag
    bciHeap[startLoc - j] = 0;
  }

  return true;
}

//Walk and allocate a block
int heap_Walk(const unsigned int startLoc, const unsigned int len)
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
      heap_ClearFreeFlags(i, runLength);

      //Return index of block
      return i - runLength;
    }

    //If we've gone down the entire heap
    if (i == BCI_HEAP_SIZE - 1)
    {
      #ifdef BCI_HEAP_DEBUG
        writeDebugStreamLine("BCI HEAP ERROR: heap_Walk: No space for malloc of length: %d at start index: %d", len, startLoc);
      #endif

      return BCI_HEAP_FAIL;
    }

    i++;
  }
}

//Walk heap without allocating
int heap_FindBlock(const unsigned int startLoc, const unsigned int len)
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
      //Return index of block
      return i - runLength;
    }

    //If we've gone down the entire heap
    if (i == BCI_HEAP_SIZE - 1)
    {
      #ifdef BCI_HEAP_DEBUG
        writeDebugStreamLine("BCI HEAP ERROR: heap_FindBlock: No block found of length: %d at start index: %d", len, startLoc);
      #endif

      return BCI_HEAP_FAIL;
    }

    i++;
  }
}

int heap_Malloc(const unsigned int size)
{
  return heap_Walk(0, size);
}

int heap_Realloc(const unsigned int loc, const unsigned int size, const unsigned int expand)
{
  
}

int heap_Expand(const unsigned int loc, const unsigned int size, const unsigned int expand)
{
  //Bounds check
  if (loc >= BCI_HEAP_SIZE)
  {
    #ifdef BCI_HEAP_DEBUG
      writeDebugStreamLine("BCI HEAP ERROR: heap_Expand: Invalid location: %d", loc);
    #endif

    return false;
  }

  //Try to find a block to expand into
  if (heap_FindBlock(loc + size, expand) == loc + size)
  {
    //There is a block to expand into, use it
    heap_ClearFreeFlags(loc + size, expand);
    return true;
  }
  //Else, there isn't a block
  //Reallocate entire block
  else
  {
    return heap_Realloc(loc, size, expand);
  }
}

float heap_Get(const unsigned int loc)
{
  //Bounds check
  if (loc >= BCI_HEAP_SIZE)
  {
    #ifdef BCI_HEAP_DEBUG
      writeDebugStreamLine("BCI HEAP ERROR: heap_Get: Invalid location: %d", loc);
    #endif

    return BCI_HEAP_FAIL;
  }

  return bciHeap[loc];
}

bool heap_Set(const unsigned int loc, const float data)
{
  //Bounds check
  if (loc >= BCI_HEAP_SIZE)
  {
    #ifdef BCI_HEAP_DEBUG
      writeDebugStreamLine("BCI HEAP ERROR: heap_Set: Invalid location: %d", loc);
    #endif

    return false;
  }

  bciHeap[loc] = data;
  return true;
}

bool heap_Free(const unsigned int loc, const unsigned int size)
{
  //Bounds check
  if (loc >= BCI_HEAP_SIZE)
  {
    #ifdef BCI_HEAP_DEBUG
      writeDebugStreamLine("BCI HEAP ERROR: heap_Free: Invalid location: %d", loc);
    #endif

    return false;
  }
  else if (loc + size >= BCI_HEAP_SIZE)
  {
    #ifdef BCI_HEAP_DEBUG
      writeDebugStreamLine("BCI HEAP ERROR: heap_Free: Invalid size: %d", size);
    #endif

    return false;
  }

  for (unsigned int i = loc; i < loc + size; i++)
  {
    bciHeap[i] = BCI_FREE_FLAG;
  }

  return true;
}

void heap_Print(const unsigned int loc, const unsigned int size)
{
  //Bounds check
  if (loc >= BCI_HEAP_SIZE)
  {
    #ifdef BCI_HEAP_DEBUG
      writeDebugStreamLine("BCI HEAP ERROR: heap_Print: Invalid location: %d", loc);
    #endif
  }
  else if (loc + size >= BCI_HEAP_SIZE)
  {
    #ifdef BCI_HEAP_DEBUG
      writeDebugStreamLine("BCI HEAP ERROR: heap_Print: Invalid size: %d", size);
    #endif
  }

  writeDebugStream("BCI HEAP DUMP:\n%d", bciHeap[loc]);

  for (unsigned int i = loc + 1; i < loc + size; i++)
  {
    writeDebugStream(",%d", bciHeap[i]);
  }

  writeDebugStreamLine("");
}

void heap_PrintStats(const unsigned int loc, const unsigned int size)
{
  //Bounds check
  if (loc >= BCI_HEAP_SIZE)
  {
    #ifdef BCI_HEAP_DEBUG
      writeDebugStreamLine("BCI HEAP ERROR: heap_PrintStats: Invalid location: %d", loc);
    #endif
  }
  else if (loc + size >= BCI_HEAP_SIZE)
  {
    #ifdef BCI_HEAP_DEBUG
      writeDebugStreamLine("BCI HEAP ERROR: heap_PrintStats: Invalid size: %d", size);
    #endif
  }

  //Run through the heap and record free space
  int freeSpace = 0;
  for (unsigned int i = 0; i < BCI_HEAP_SIZE; i++)
  {
    if (bciHeap[i] == BCI_FREE_FLAG)
    {
      freeSpace++;
    }
  }

  //Print out percent space used, free space, and used space
  writeDebugStreamLine("BCI HEAP STATS:");
  writeDebugStreamLine("Percent used: %1.2f, Used space: %d, Free space: %d", 100 * ((float)(BCI_HEAP_SIZE - freeSpace) / (float)BCI_HEAP_SIZE), BCI_HEAP_SIZE - freeSpace, freeSpace);
}

#endif //BCI_HEAP_C_INCLUDED
