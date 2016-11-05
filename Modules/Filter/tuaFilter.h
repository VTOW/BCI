#ifndef BCI_TUAFILTER_H_INCLUDED
#define BCI_TUAFILTER_H_INCLUDED

//Ten-unit average filter
typedef struct TUAFilter_t
{
	float components[10];
	int index;
} TUAFilter;

/**
 * Initializes a ten-unit average filter
 * @param filter TUA filter to initialize
 */
void filter_Init_TUA(TUAFilter *filter);

/**
 * Filters an input
 * @param  filter      TUA filter to use
 * @param  componentIn Input reading
 * @return             Filtered value
 */
float filter_TUA(TUAFilter *filter, const float componentIn);

#endif //BCI_TUAFILTER_H_INCLUDED
