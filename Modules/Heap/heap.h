#ifndef BCI_HEAP_H_INCLUDED
#define BCI_HEAP_H_INCLUDED

#ifndef BCI_HEAP_SIZE
#define BCI_HEAP_SIZE 1000
#endif //BCI_HEAP_SIZE

/**
 * Initializes the heap
 */
void heap_init();

/**
 * Allocates memory for a type of object
 * @param  name Name of object
 * @param  type Type of object
 * @param  data Data in object
 * @return      Whether the operation was successful
 */
bool heap_malloc(const string *name, const int type, void *data);

#endif //BCI_HEAP_H_INCLUDED
