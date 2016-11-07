#ifndef BCI_FUAFILTER_C_INCLUDED
#define BCI_FUAFILTER_C_INCLUDED

#include "fuaFilter.h"

void filter_Init_FUA(FUAFilter *filter)
{
	filter->index = 0;

	for (int i = 0; i < 5; i++)
	{
		filter->components[i] = 0;
	}
}

float filter_FUA(FUAFilter *filter, const float componentIn)
{
	filter->components[filter->index] = componentIn;
	filter->index = filter->index + 1 > 4 ? 0 : filter->index + 1;

	float avg = 0.0;

	for (int i = 0; i < 5; i++)
	{
		avg += filter->components[i];
	}

	return avg / 5.0;
}

#endif //BCI_FUAFILTER_C_INCLUDED
