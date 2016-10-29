#ifndef BCI_HEAP_C_INCLUDED
#define BCI_HEAP_C_INCLUDED

#include "heap.h"

//Using BNS Error code here as a flag
//https://github.com/JMarple/BNSLibrary/blob/master/Modules/Core/BNSHeap.h
//0000 1010 1010 0000 0000 0000 0000 0000
#define BCI_FREE_FLAG 178257920

//0101 0101 0000 0000 0000 0000 0000 0000
#define BCI_MALLOC_FAIL 1426063360

static float bciHeap[BCI_HEAP_SIZE];

void heap_init()
{
  for (unsigned int i = 0; i < BCI_HEAP_SIZE; i++)
  {
    bciHeap[i] = BCI_FREE_FLAG;
  }
}

float heap_malloc(const unsigned int size)
{
  //Get next free spot in heap
  unsigned int i = 0, runLength = 0;
  while (true)
  {
    //Empty flag
    if (bciHeap[i] == BCI_FREE_FLAG)
    {
      writeDebugStreamLine("%d",i);
      runLength++;
    }
    else
    {
      runLength = 0;
    }

    //If block is long enough, use it
    if (runLength == size)
    {
      //Clear free flags
      for (unsigned int j = 0; j < runLength; j++)
      {
        bciHeap[i - j] = 0;
      }

      //Return index of block
      return i;
    }

    //If we've gone down the entire heap
    if (i == BCI_HEAP_SIZE - 1)
    {
      #ifdef BCI_HEAP_DEBUG
        writeDebugStreamLine("BCI HEAP ERROR: No space for malloc of size %d", size);
      #endif //BCI_HEAP_DEBUG

      return BCI_MALLOC_FAIL;
    }

    i++;
  }
}

void heap_free(const unsigned int loc, const unsigned int size)
{
  for (unsigned int i = loc; i < loc + size; i++)
  {
    bciHeap[i] = BCI_FREE_FLAG;
  }
}

void heap_print(const unsigned int loc, const unsigned int size)
{
  writeDebugStream("BCI HEAP DUMP:\n%d", bciHeap[loc]);

  for (unsigned int i = loc + 1; i < loc + size; i++)
  {
    writeDebugStream(",%d", bciHeap[i]);
  }

  writeDebugStreamLine("");
}

void heap_printStats(const unsigned int loc, const unsigned int size)
{
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
