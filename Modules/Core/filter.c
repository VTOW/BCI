#ifndef FILTER_C_INCLUDED
#define FILTER_C_INCLUDED

#include "filter.h"

void filter_Init_EMA(EMAFilter *filter)
{
	filter->alpha = 1.0;
	filter->readIn = 0.0;
	filter->output = 0.0;
	filter->output_old = 0.0;
}

float filter_EMA(EMAFilter *filter, const float readIn, const float alpha)
{
	filter->alpha = alpha;
	filter->readIn = readIn;
	filter->output = alpha * readIn + (1.0 - alpha) * filter->output_old;
	filter->output_old = filter->output;
	return filter->output;
}

void filter_Init_DEMA(DEMAFilter *filter)
{
	filter->alpha = 1.0;
	filter->beta = 1.0;
	filter->readIn = 0.0;
	filter->outputS = 0.0;
	filter->outputB = 0.0;
	filter->outputS_old = 0.0;
	filter->outputB_old = 0.0;
}

float filter_DEMA(DEMAFilter *filter, const float readIn, const float alpha, const float beta)
{
	filter->alpha = alpha;
	filter->beta = beta;
	filter->readIn = readIn;
	filter->outputS = (alpha * readIn) + ((1.0 - alpha) * (filter->outputS_old + filter->outputB_old));
	filter->outputB = (beta * (filter->outputS - filter->outputS_old)) + ((1.0 - beta) * filter->outputB_old);
	filter->outputS_old = filter->outputS;
	filter->outputB_old = filter->outputB;

	return filter->outputS + filter->outputB;
}

void filter_Init_FUA(FUAFilter *filter)
{
	filter->index = 0;

	for (int i = 0; i < 5; i++)
	{
		filter->components[i] = 0;
	}
}

float filter_FUA(FUAFilter *filter, const float componentIn)
{
	filter->components[filter->index] = componentIn;
	filter->index = filter->index + 1 > 4 ? 0 : filter->index + 1;

	float avg = 0.0;

	for (int i = 0; i < 5; i++)
	{
		avg += filter->components[i];
	}

	return avg / 5.0;
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
/*
void filter_Init_Kalman(KalmanFilter *filter)
{
	filter->x_vel = 0;
	filter->x_accel = 0;

	filter->x_vel_prev = 0;
	filter->x_accel_prev = 0;

	filter->Q_cov_vel = 0;
	filter->Q_cov_accel = 0;

	filter->R_cov = 0;

	filter->P_cov_vel = 0;
	filter->P_cov_accel = 0;
	filter->P_cov_vel_prev = 0;
	filter->P_cov_accel_prev = 0;

	filter->dt = 0;
	filter->lastTime = 0;
}

float filter_Kalman(KalmanFilter *filter, const float velocityIn, const float accelerationIn)
{
	//Predict step
	filter->dt = nSystime - lastTime;
	filter->lastTime = nSystime;

	if (filter->dt == 0)
	{
		return 0;
	}

	filter->x_vel = x_vel_prev + filter->dt * filter->x_accel_prev
								+ filter->dt * accelerationIn;

	filter->x_accel = filter->x_accel_prev + accelerationIn;

	filter->P_cov_vel = P_cov_vel_prev + Q_cov_vel;
	filter->P_cov_accel = P_cov_

	//Update step

}*/

#endif //FILTER_C_INCLUDED
