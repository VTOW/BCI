#ifndef BCI_EMAFILTER_H_INCLUDED
#define BCI_EMAFILTER_H_INCLUDED

//Exponential moving average filter
typedef struct EMAFilter_t
{
	float alpha;
	float output;
	float output_old;
} EMAFilter;

/**
 * Initializes an exponential moving average filter
 * @param filter EMA filter to initialize
 * @param alpha  Alpha gain
 */
void filter_Init_EMA(EMAFilter *filter, float alpha = 1.0);

/**
 * Filters an input
 * @param  filter EMA filter to use
 * @param  readIn Input reading
 * @return        Filtered value
 */
float filter_EMA(EMAFilter *filter, const float readIn);

/**
 * Filters an input
 * @param  filter EMA filter to use
 * @param  readIn Input reading
 * @param  alpha  Alpha gain
 * @return        Filtered value
 */
float filter_EMA(EMAFilter *filter, const float readIn, const float alpha);

#endif //BCI_EMAFILTER_H_INCLUDED
