#ifndef BCI_ARRAYLIST_H_INCLUDED
#define BCI_ARRAYLIST_H_INCLUDED

typedef struct arrayList_t
{
  int size;     // Current size
  int capacity; // Maximum capacity until another malloc
  int startIndex;
} arrayList;

/**
 * Initializes an ArrayList
 * @param list ArrayList to initialze
 * @param size Starting size
 * @return     Whether the ArrayList was initialized successfully
 */
bool arrayList_Initialize(arrayList *list, const int size);

/**
 * Initializes an ArrayList
 * @param list ArrayList to initialze
 */
void arrayList_Initialize(arrayList *list);

/**
 * Adds an element to an ArrayList
 * @param list ArrayList to use
 * @param data Elements to add
 */
void arrayList_Add(arrayList *list, const float data);

#endif //BCI_ARRAYLIST_H_INCLUDED
