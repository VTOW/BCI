#ifndef ARRAYLIST_C_INCLUDED
#define ARRAYLIST_C_INCLUDED

bool arrayList_Initialize(arrayList *list, const int size)
{
  list->size = size;
  list->capacity = size;

  if ((list->startIndex = heap_Malloc(size)) == BCI_HEAP_FAIL)
  {
    return false;
  }

  return true;
}

void arrayList_Initialize(arrayList *list)
{
  arrayList_Initialize(list, 1);
}

void arrayList_Add(arrayList *list, const float data)
{
  //If we can just add the element
  if (list->size + 1 <= list->capacity)
  {
    heap_Set(list->size++, data);
  }
  //Else, we have to realloc
  else
  {
    heap_Expand(list->startIndex, 1);
    //TODO: if expand fails, we need to defragment the heap
  }
}

#endif //ARRAYLIST_C_INCLUDED
