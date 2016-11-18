#define BCI_USE_BIQUAD_FILTER
#include "..\..\BCI.h"

task main
{
  biquadFilter filter;

  // Initialize biquad filter as lowpass butterworth.
  // Sample 10 times a second, -3db cutoff freq of 1Hz
  biquadFilter_Initialize(&filter, LOWPASS, 10, 0.5);

  writeDebugStreamLine("Biquad filter example.  ");
  writeDebugStreamLine("Copy and paste results into excel and graph results");
  writeDebugStreamLine(
    "H(z) = (%f + %f*z^-1 + %f*z^-2) / (1 + %f*z^-1 + %f*z^-2)",
    filter.b0, filter.b1, filter.b2, filter.a1, filter.a2);

  // This mimics "noisy sensor data".
  float data[100];
  for (int i = 0; i < 100; i++)
  {
    // Main signal
    data[i] = sin(0.5 * PI * i / 10.0 ) +
      // "Noise"
      sin(3.6 * PI * i / 10.0) +
      sin(5.8 * PI * i / 10.0);
  }

  // Apply low pass filter to noisy sensor data.
  int i;
  for (i = 0; i < 100; i++)
  {
    float x = biquadFilter_Sample(&filter, data[i]);
    writeDebugStreamLine("%f %f", data[i], x);
  }
}
