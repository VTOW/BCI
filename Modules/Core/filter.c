#ifndef FILTER_C_INCLUDED
#define FILTER_C_INCLUDED

#include "filter.h"

void filter_Init_SMA(SMAFilter *filter)
{
	filter->alpha = 1.0;
	filter->readIn = 0.0;
	filter->output = 0.0;
	filter->output_old = 0.0;
}

float filter_SMA(SMAFilter *filter, const float readIn, const float alpha)
{
	filter->alpha = alpha;
	filter->readIn = readIn;
	filter->output = (1.0 - alpha) * filter->output_old + alpha * readIn;
	filter->output_old = filter->output;
	return filter->output;
}

void filter_Init_FUA(FUAFilter *filter)
{
	filter->index = 0;

	for (int i = 0; i < 10; i++)
	{
		filter->components[i] = 0;
	}
}

float filter_FUA(FUAFilter *filter, const float componentIn)
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

#endif //FILTER_C_INCLUDED
