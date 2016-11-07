#ifndef BCI_ARRAYLIST_H_INCLUDED
#define BCI_ARRAYLIST_H_INCLUDED

typedef struct arrayList_t
{
  block b;
  unsigned int usedSpace;
} arrayList;

/**
 * Initializes an arrayList
 * @param list arrayList to initialze
 * @param size Starting size
 * @return     Whether the arrayList was initialized successfully
 */
bool arrayList_Initialize(arrayList *list, const unsigned int size = 10);

/**
 * Trims the capacity of this arrayList down to the number of elements used
 * @param  list arrayList to trim
 * @return      Whether the trim was successful
 */
bool arrayList_TrimToSize(arrayList *list);

/**
 * Increases the capacity of this arrayList, if necessary, to ensure that it can
 * hold at least the number of elements specified
 * @param  list        arrayList to modify
 * @param  minCapacity Minimum capacity
 * @return             Whether the operation was successful
 */
bool arrayList_EnsureCapacity(arrayList *list, const unsigned int minCapacity);

/**
 * Returns the size of this arrayList
 * @param  list arrayList to read from
 * @return      The size of the arrayList
 */
unsigned int arrayList_Size(arrayList *list);

/**
 * Returns the data at an index in this arrayList
 * @param  list  arrayList to read from
 * @param  index Index of data
 * @return       Data at index
 */
float arrayList_Get(const arrayList *list, const unsigned int index);

/**
 * Sets the data at an index in this arrayList
 * @param  list  arrayList to write to
 * @param  index Index of data
 * @param  data  Data to write
 * @return       Whether the write was successful
 */
bool arrayList_Set(arrayList *list, const unsigned int index, const float data);

/**
 * Adds data to this arrayList
 * @param  list arrayList to add to
 * @param  data Data to add
 * @return      Whether the add was successful
 */
bool arrayList_Add(arrayList *list, const float data);

/**
 * Removed an element from this arrayList
 * @param  list  arrayList to remove from
 * @param  index Index of data
 * @return       Data removed
 */
float arrayList_Remove(arrayList *list, const unsigned int index);

/**
 * Clears this arrayList
 * @param  list     arrayList to clear
 * @param  clearVal Value to clear elements to
 * @return          Whether the clear was successful
 */
bool arrayList_Clear(arrayList *list, float clearVal = 0);

/**
 * Frees this arrayList
 * @param  list arrayList to free
 * @return      Whether the free was successful
 */
bool arrayList_Free(arrayList *list);

#endif //BCI_ARRAYLIST_H_INCLUDED
