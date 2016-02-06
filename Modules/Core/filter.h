#ifndef FILTER_H_INCLUDED
#define FILTER_H_INCLUDED

//Simple moving average filter
typedef struct SMAFilter
{
	float alpha;
	float readIn;
	float output;
	float output_old;
} SMAFilter;

//Five-unit average filter
typedef struct FUAFilter
{
	float components[5];
	int index;
} FUAFilter;

//Ten-unit average filter
typedef struct TUAFilter
{
	float components[10];
	int index;
} TUAFilter;

//Simple moving average filter
void filter_Init_SMA(SMAFilter *filter);
float filter_SMA(SMAFilter *filter, const float readIn, const float alpha);

//Five-unit average filter
void filter_Init_FUA(FUAFilter *filter);
float filter_FUA(FUAFilter *filter, const float componentIn);

//Ten-unit average filter
void filter_Init_TUA(TUAFilter *filter);
float filter_TUA(TUAFilter *filter, const float componentIn);

#endif //FILTER_H_INCLUDED
