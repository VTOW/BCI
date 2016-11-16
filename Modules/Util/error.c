#ifndef BCI_ERROR_C_INCLUDED
#define BCI_ERROR_C_INCLUDED

#include "error.h"

void util_PrintHeapError(const string *msg)
{
  writeDebugStreamLine("BCI HEAP ERROR: heap_%s", msg);
}

void util_PrintBlockError(const string *msg)
{
  writeDebugStreamLine("BCI BLOCK ERROR: block_%s", msg);
}

void util_PrintArrayListError(const string *msg)
{
  writeDebugStreamLine("BCI ARRAYLIST ERROR: arrayList_%s", msg);
}

void util_PrintMatrixError(const string *msg)
{
  writeDebugStreamLine("BCI MATRIX ERROR: matrix_%s", msg);
}

#endif //BCI_ERROR_C_INCLUDED
