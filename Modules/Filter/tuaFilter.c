#ifndef BCI_TUAFILTER_C_INCLUDED
#define BCI_TUAFILTER_C_INCLUDED

#include "tuaFilter.h"

void filter_Init_TUA(TUAFilter *filter)
{
	filter->index = 0;

	for (int i = 0; i < 10; i++)
	{
		filter->components[i] = 0;
	}
}

float filter_TUA(TUAFilter *filter, const float componentIn)
{
	filter->components[filter->index] = componentIn;
	filter->index = filter->index + 1 > 9 ? 0 : filter->index + 1;

	float avg = 0.0;

	for (int i = 0; i < 10; i++)
	{
		avg += filter->components[i];
	}

	return avg / 10.0;
}

#endif //BCI_TUAFILTER_C_INCLUDED
