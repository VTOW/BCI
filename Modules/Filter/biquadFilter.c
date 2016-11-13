#ifndef BCI_BIQUADFILTER_C_INCLUDED
#define BCI_BIQUADFILTER_C_INCLUDED

#include "biquadFilter.h"

bool biquadFilter_Initialize(
    biquadFilter *filter,
    const enum BiquadFilterType type,
    const float sampleFreq,
    const float cutoffFreq,
    const float defaultValue)
{
  if (filter == 0) return false;

  float w0 = 2 * PI * cutoffFreq / sampleFreq;
  float cosw0 = cos(w0);
  float sinw0 = sin(w0);

  float Q = 0.707;
  float alpha = sinw0 / (2 * Q);
  float b0, b1, b2, a0, a1, a2;

  writeDebugStreamLine("%f %f %f %f", cosw0, sinw0, alpha, Q);

  // Calculates the coefficients for the transfer function.
  switch (type)
  {
    case LOWPASS:
      b0 = (1 - cosw0) / 2;
      b1 = (1 - cosw0);
      b2 = (1 - cosw0) / 2;
      a0 = 1 + alpha;
      a1 = -2 * cosw0;
      a2 = 1 - alpha;
      break;

    case HIGHPASS:
      b0 = (1 + cosw0) / 2;
      b1 = -(1 + cosw0);
      b2 = (1 + cosw0) / 2;
      a0 = 1 + alpha;
      a1 = -2 * cosw0;
      a2 = 1 - alpha;
      break;

    default:
      return false;
  }

  // Normalize the coefficients so that a0 = 1.
  filter->b0 = b0 / a0;
  filter->b1 = b1 / a0;
  filter->b2 = b2 / a0;
  filter->a1 = a1 / a0;
  filter->a2 = a2 / a0;

  filter->old_input[0] = filter->old_input[1] = defaultValue;
  filter->old_output[0] = filter->old_output[1] = defaultValue;

  return true;
}

float biquadFilter_Sample(biquadFilter *filter, const float data)
{
  if (filter == 0) return -1;

  float output =
    filter->b0 * data +
    filter->b1 * filter->old_input[0] +
    filter->b2 * filter->old_input[1] -
    filter->a1 * filter->old_output[0] -
    filter->a2 * filter->old_output[1];

  filter->old_input[1] = filter->old_input[0];
  filter->old_input[0] = data;

  filter->old_output[1] = filter->old_output[0];
  filter->old_output[0] = output;

  return output;
}

#endif //BCI_BIQUADFILTER_C_INCLUDED
