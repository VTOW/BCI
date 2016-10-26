#ifndef BCI_HEAP_C_INCLUDED
#define BCI_HEAP_C_INCLUDED

#include "heap.h"

static float bciHeap[BCI_HEAP_SIZE];
static string bciHeap_Names[25];

void heap_init()
{
  
}

bool heap_malloc(const string *name, const int type, void *data);

#endif //BCI_HEAP_C_INCLUDED
