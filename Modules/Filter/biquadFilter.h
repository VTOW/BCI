// Biquad filter is a standard 2nd-order filter
#ifndef BCI_BIQUADFILTER_H_INCLUDED
#define BCI_BIQUADFILTER_H_INCLUDED

// Biquad filter is a standard 2nd-order filter
// The transfer function follows the following format:
// H(z) = (b0 + b1*z^-1 + b2*z^-2) / (1 + a1*z^-1 + a2*z^-2)
typedef struct biquadFilter_t
{
  float b0, b1, b2, a1, a2;

  float old_input[2];
  float old_output[2];
} biquadFilter;

// The response of the filter, default is butterworth.
enum BiquadFilterType
{
  LOWPASS,
  HIGHPASS
};

// Initializes biquad filter.
// Sample Freq and cutoff freq is in hertz.
// Ex. If you sample a gyroscope 100 times a second, sample
//     freq is 100 and cutoff freq is the -3db point for the
//     filter, such as 40.
/**
 * Initializes a biquadFilter
 * @param  filter       biquadFilter to initialize
 * @param  type         Response type of filter
 * @param  sampleFreq   Sample frequency (Hz)
 * @param  cutoffFreq   Cutoff frequency (Hz)
 * @param  defaultValue Default value
 * @return
 */
bool biquadFilter_Initialize(
    biquadFilter *filter,
    const enum BiquadFilterType type,
    const float sampleFreq,
    const float cutoffFreq,
    const float defaultValue = 0.0);

/**
 * Filters an input and returns the filtered value
 * @param  filter biquadFilter to use
 * @param  data   New data to filter
 * @return        Filtered version of input data
 */
float biquadFilter_Sample(biquadFilter *filter, const float data);

#endif //BCI_BIQUADFILTER_H_INCLUDED
