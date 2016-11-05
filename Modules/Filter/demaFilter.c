#ifndef BCI_DEMAFILTER_C_INCLUDED
#define BCI_DEMAFILTER_C_INCLUDED

#include "demaFilter.h"

void filter_Init_DEMA(DEMAFilter *filter)
{
	filter->alpha = 1.0;
	filter->beta = 1.0;
	filter->readIn = 0.0;
	filter->outputS = 0.0;
	filter->outputB = 0.0;
	filter->outputS_old = 0.0;
	filter->outputB_old = 0.0;
}

float filter_DEMA(DEMAFilter *filter, const float readIn, const float alpha, const float beta)
{
	filter->alpha = alpha;
	filter->beta = beta;
	filter->readIn = readIn;
	filter->outputS = (alpha * readIn) + ((1.0 - alpha) * (filter->outputS_old + filter->outputB_old));
	filter->outputB = (beta * (filter->outputS - filter->outputS_old)) + ((1.0 - beta) * filter->outputB_old);
	filter->outputS_old = filter->outputS;
	filter->outputB_old = filter->outputB;

	return filter->outputS + filter->outputB;
}

#endif //BCI_DEMAFILTER_C_INCLUDED
