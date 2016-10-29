#ifndef BCI_FILTER_H_INCLUDED
#define BCI_FILTER_H_INCLUDED

//Exponential moving average filter
typedef struct EMAFilter_t
{
	float alpha;
	float readIn;
	float output;
	float output_old;
} EMAFilter;

//Double exponential moving average filter
typedef struct DEMAFilter_t
{
	float alpha;
	float beta;
	float readIn;
	float outputS;
	float outputB;
	float outputS_old;
	float outputB_old;
} DEMAFilter;

//Five-unit average filter
typedef struct FUAFilter_t
{
	float components[5];
	int index;
} FUAFilter;

//Ten-unit average filter
typedef struct TUAFilter_t
{
	float components[10];
	int index;
} TUAFilter;

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

/**
 * Initializes a double exponential moving average filter
 * @param filter DEMA filter to initialize
 */
void filter_Init_DEMA(DEMAFilter *filter);

/**
 * Filters an input
 * @param  filter DEMA filter to use
 * @param  readIn Input reading
 * @param  alpha  Alpha gain
 * @param  beta   Beta gain
 * @return        Filtered value
 */
float filter_DEMA(DEMAFilter *filter, const float readIn, const float alpha, const float beta);

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

#endif //BCI_FILTER_H_INCLUDED
