#ifndef BCI_EMAFILTER_H_INCLUDED
#define BCI_EMAFILTER_H_INCLUDED

//Exponential moving average filter
typedef struct EMAFilter_t
{
	float alpha;
	float readIn;
	float output;
	float output_old;
} EMAFilter;

/**
 * Initializes an exponential moving average filter
 * @param filter EMA filter to initialize
 */
void filter_Init_EMA(EMAFilter *filter);

/**
 * Filters an input
 * @param  filter EMA filter to use
 * @param  readIn Input reading
 * @param  alpha  Alpha gain
 * @return        Filtered value
 */
float filter_EMA(EMAFilter *filter, const float readIn, const float alpha);

#endif //BCI_EMAFILTER_H_INCLUDED
