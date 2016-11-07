#ifndef BCI_FUAFILTER_H_INCLUDED
#define BCI_FUAFILTER_H_INCLUDED

//Five-unit average filter
typedef struct FUAFilter_t
{
	float components[5];
	int index;
} FUAFilter;

/**
 * Initializes a five-unit average filter
 * @param filter FUA filter to initialize
 */
void filter_Init_FUA(FUAFilter *filter);

/**
 * Filters an input
 * @param  filter      FUA filter to use
 * @param  componentIn Input reading
 * @return             Filtered value
 */
float filter_FUA(FUAFilter *filter, const float componentIn);

#endif //BCI_FUAFILTER_H_INCLUDED
