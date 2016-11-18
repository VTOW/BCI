#define BCI_USE_ARRAYLIST
//#define BCI_HEAP_DEBUG
#include "..\..\BCI.h"

task main()
{
	clearDebugStream();
  heap_Init();

	arrayList list;
	arrayList_Initialize(&list);
	heap_Print(0,20);

	arrayList_Add(&list, 1);
	heap_Print(0,20);

	arrayList_Add(&list, 2);
	heap_Print(0,20);

	arrayList_Set(&list, 0, 2);
	heap_Print(0,20);

	writeDebugStreamLine("%d",arrayList_Get(&list, 0));
	writeDebugStreamLine("%d",arrayList_Get(&list, 1));
	writeDebugStreamLine("%d",arrayList_Size(&list));

	arrayList_Remove(&list, 1);
	arrayList_Remove(&list, 0);
	heap_Print(0,20);
	writeDebugStreamLine("%d",arrayList_Size(&list));

	arrayList_Clear(&list);
	heap_Print(0,20);

	arrayList_Clear(&list, 3);
	heap_Print(0,20);

	arrayList_Add(&list, 1);
	heap_Print(0,20);
	writeDebugStreamLine("%d,%d",list.b.loc,arrayList_Size(&list));

	arrayList list2;
	arrayList_Initialize(&list2);
	heap_Print(0,20);

	arrayList_Free(&list);
	heap_Print(0,20);
}
