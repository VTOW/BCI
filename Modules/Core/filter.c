#ifndef FILTER_C_INCLUDED
#define FILTER_C_INCLUDED

#include "filter.h"

void filter_Init_EMA(EMAFilter *filter)
{
	filter->alpha = 1.0;
	filter->readIn = 0.0;
	filter->output = 0.0;
	filter->output_old = 0.0;
}

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

void filter_Init_FUA(FUAFilter *filter)
{
	filter->index = 0;

	for (int i = 0; i < 5; i++)
	{
		filter->components[i] = 0;
	}
}

void filter_Init_TUA(TUAFilter *filter)
{
	filter->index = 0;

	for (int i = 0; i < 10; i++)
	{
		filter->components[i] = 0;
	}
}

float filter_EMA(EMAFilter *filter, const float readIn, const float alpha)
{
	filter->alpha = alpha;
	filter->readIn = readIn;
	filter->output = alpha * readIn + (1.0 - alpha) * filter->output_old;
	filter->output_old = filter->output;
	return filter->output;
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

#endif //FILTER_C_INCLUDED
