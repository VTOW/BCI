#ifndef BCI_EMAFILTER_C_INCLUDED
#define BCI_EMAFILTER_C_INCLUDED

#include "emaFilter.h"

void filter_Init_EMA(EMAFilter *filter, float alpha)
{
	filter->alpha = alpha;
	filter->output = 0.0;
	filter->output_old = 0.0;
}

float filter_EMA(EMAFilter *filter, const float readIn)
{
	filter->output = filter->alpha * readIn + (1.0 - filter->alpha) * filter->output_old;
	filter->output_old = filter->output;
	return filter->output;
}

float filter_EMA(EMAFilter *filter, const float readIn, const float alpha)
{
	filter->alpha = alpha;
	return filter_EMA(filter, readIn);
}

#endif //BCI_EMAFILTER_C_INCLUDED
