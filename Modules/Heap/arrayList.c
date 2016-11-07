#ifndef BCI_ARRAYLIST_C_INCLUDED
#define BCI_ARRAYLIST_C_INCLUDED

#include "arrayList.h"

bool arrayList_Initialize(arrayList *list, const unsigned int size)
{
  list->usedSpace = 0;
  return block_Initialize(&(list->b), size);
}

bool arrayList_TrimToSize(arrayList *list)
{
  return block_Shrink(&(list->b), list->b.size - list->usedSpace);
}

bool arrayList_EnsureCapacity(arrayList *list, const unsigned int minCapacity)
{
  if (minCapacity > list->b.size)
  {
    return block_Expand(&(list->b), minCapacity);
  }

  return true;
}

unsigned int arrayList_Size(arrayList *list)
{
  return list->b.size;
}

float arrayList_Get(const arrayList *list, const unsigned int index)
{
  //Bounds check
  if (index < 0 || index > list->b.size)
  {
    #ifdef BCI_HEAP_DEBUG
      writeDebugStreamLine("BCI HEAP ERROR: arrayList_Get: Invalid location: %d", index);
    #endif

    return BCI_HEAP_FAIL;
  }

  return block_Get(&(list->b), index);
}

bool arrayList_Set(arrayList *list, const unsigned int index, const float data)
{
  //Bounds check
  if (index < 0 || index > list->b.size)
  {
    #ifdef BCI_HEAP_DEBUG
      writeDebugStreamLine("BCI HEAP ERROR: arrayList_Set: Invalid location: %d", index);
    #endif

    return BCI_HEAP_FAIL;
  }

  return block_Set(&(list->b), index, data);
}

bool arrayList_Add(arrayList *list, const float data)
{
  arrayList_EnsureCapacity(list, list->b.size + 1);
  block_Set(&(list->b), list->usedSpace++, data);
}

float arrayList_Remove(arrayList *list, const unsigned int index)
{
  //Bounds check
  if (index < 0 || index > list->b.size)
  {
    #ifdef BCI_HEAP_DEBUG
      writeDebugStreamLine("BCI HEAP ERROR: arrayList_Set: Invalid location: %d", index);
    #endif

    return BCI_HEAP_FAIL;
  }

  float out = arrayList_Get(list, index);

  //If index isn't the last element, we have to shift bottom elements up
  if (index != list->b.size)
  {
    for (unsigned int i = index; i < list->b.size - 1; i++)
    {
      block_Set(&(list->b), index, block_Get(&(list->b), index + 1));
    }
  }

  return out;
}

bool arrayList_Clear(arrayList *list, float clearVal)
{
  for (unsigned int i = 0; i < list->b.size; i++)
  {
    block_Set(&(list->b), i, clearVal);
  }

  return true;
}

bool arrayList_Free(arrayList *list)
{
  return block_Free(&(list->b));
}

#endif //BCI_ARRAYLIST_C_INCLUDED
