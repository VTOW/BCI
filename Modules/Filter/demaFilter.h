#ifndef BCI_DEMAFILTER_H_INCLUDED
#define BCI_DEMAFILTER_H_INCLUDED

//Double exponential moving average filter
typedef struct DEMAFilter_t
{
	float alpha;
	float beta;
	float outputS;
	float outputB;
	float outputS_old;
	float outputB_old;
} DEMAFilter;

/**
 * Initializes a double exponential moving average filter
 * @param filter DEMA filter to initialize
 */
void filter_Init_DEMA(DEMAFilter *filter, float alpha = 1.0, float beta = 1.0);

/**
 * Filters an input
 * @param  filter DEMA filter to use
 * @param  readIn Input reading
 * @return        Filtered value
 */
float filter_DEMA(DEMAFilter *filter, const float readIn);

/**
 * Filters an input
 * @param  filter DEMA filter to use
 * @param  readIn Input reading
 * @param  alpha  Alpha gain
 * @param  beta   Beta gain
 * @return        Filtered value
 */
float filter_DEMA(DEMAFilter *filter, const float readIn, const float alpha, const float beta);

#endif //BCI_DEMAFILTER_H_INCLUDED
