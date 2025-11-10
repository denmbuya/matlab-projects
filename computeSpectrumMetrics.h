/*
 * File: computeSpectrumMetrics.h
 *
 * MATLAB Coder version            : 24.2
 * C/C++ source code generated on  : 28-Oct-2025 19:34:06
 */

#ifndef COMPUTESPECTRUMMETRICS_H
#define COMPUTESPECTRUMMETRICS_H

/* Include Files */
#include "computeSpectrumMetrics_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
extern void
computeSpectrumMetrics(const creal_T b_signal[4096], double sampling_freq,
                       const double prevWaterfall[819200], int mode,
                       double *rssi, double *snr, double f_axis[4096],
                       double S_db[4096], emxArray_real_T *peaks,
                       double bandMask[12288], double waterfall[819200]);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for computeSpectrumMetrics.h
 *
 * [EOF]
 */
