#ifndef BCI_HEAP_C_INCLUDED
#define BCI_HEAP_C_INCLUDED

#include "heap.h"

//Using BNS Error code here as a flag
//https://github.com/JMarple/BNSLibrary/blob/master/Modules/Core/BNSHeap.h
#define BCI_FREE_FLAG 2852126720

static float bciHeap[BCI_HEAP_SIZE];

//Float to reference for a malloc fail
float BCI_MALLOC_FAIL = 0;

void heap_init()
{
  for (int i = 0; i < BCI_HEAP_SIZE; i++)
  {
    bciHeap[i] = BCI_DATA_FLAG;
  }
}

float* heap_malloc(const unsigned int size, bool recursive)
{
  //Get next free spot in heap
  unsigned int i = 0, runLength = 0;
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
    if (runLength == size)
    {
      //Clear free flags
      for (int j = runLength; j > 0; j--)
      {
        bciHeap[i - j] = 0;
      }

      return &(bciHeap[i]);
    }

    //If we've gone down the entire heap
    if (i == BCI_HEAP_SIZE - 1)
    {
      //If we've already tried to defrag
      if (recursive)
      {
        return &BCI_MALLOC_FAIL;
      }
      else
      {
        //Defragment the heap

        //Try again
        return heap_malloc(size, true);
      }
    }

    i++;
  }
}

matrix* heap_matrix_malloc(const unsigned int width, const unsigned int height)
{

}

void heap_free(const unsigned int loc, const unsigned int size)
{

}

void heap_free_matrix(matrix *mat)
{

}

void heap_print(const unsigned int loc, const unsigned int size)
{

}

void heap_printStats(const unsigned int loc, const unsigned int size)
{

}

#endif //BCI_HEAP_C_INCLUDED
