#ifndef FILTER_H_INCLUDED
#define FILTER_H_INCLUDED

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

//Exponential moving average filter
void filter_Init_EMA(EMAFilter *filter);
float filter_EMA(EMAFilter *filter, const float readIn, const float alpha);

//Double exponential moving average filter
void filter_Init_DEMA(DEMAFilter *filter);
float filter_DEMA(DEMAFilter *filter, const float readIn, const float alpha, const float beta);

//Five-unit average filter
void filter_Init_FUA(FUAFilter *filter);
float filter_FUA(FUAFilter *filter, const float componentIn);

//Ten-unit average filter
void filter_Init_TUA(TUAFilter *filter);
float filter_TUA(TUAFilter *filter, const float componentIn);

#endif //FILTER_H_INCLUDED
