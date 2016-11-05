#ifndef BCI_EMAFILTER_C_INCLUDED
#define BCI_EMAFILTER_C_INCLUDED

#include "emaFilter.h"

void filter_Init_EMA(EMAFilter *filter)
{
	filter->alpha = 1.0;
	filter->readIn = 0.0;
	filter->output = 0.0;
	filter->output_old = 0.0;
}

float filter_EMA(EMAFilter *filter, const float readIn, const float alpha)
{
	filter->alpha = alpha;
	filter->readIn = readIn;
	filter->output = alpha * readIn + (1.0 - alpha) * filter->output_old;
	filter->output_old = filter->output;
	return filter->output;
}

#endif //BCI_EMAFILTER_C_INCLUDED
