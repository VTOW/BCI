#ifndef FILTER_H_INCLUDED
#define FILTER_H_INCLUDED

//Exponential moving average filter
typedef struct EMAFilter
{
	float alpha;
	float readIn;
	float output;
	float output_old;
} EMAFilter;

//Double exponential moving average filter
typedef struct DEMAFilter
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

/*
//Kalman filter
typedef struct KalmanFilter
{
	//State vector estimate
	float x_vel;
	float x_accel;

	//Previous state vector estimate
	float x_vel_prev;
	float x_accel_prev;

	//Process noise covariance
	float Q_cov_vel;
	float Q_cov_accel;

	//Measurement noise covariance
	float R_cov;

	//Covariance matrix
	float P_cov_vel;
	float P_cov_accel;
	float P_cov_vel_prev;
	float P_cov_accel_prev;

	//Delta time
	float dt;
	float lastTime;
} KalmanFilter;*/

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
/*
//Kalman filter
void filter_Init_Kalman(KalmanFilter *filter);
float filter_Kalman(KalmanFilter *filter, const float velocityIn);
*/
#endif //FILTER_H_INCLUDED
