/*
 * File: computeSpectrumMetrics_emxutil.h
 *
 * MATLAB Coder version            : 24.2
 * C/C++ source code generated on  : 28-Oct-2025 19:34:06
 */

#ifndef COMPUTESPECTRUMMETRICS_EMXUTIL_H
#define COMPUTESPECTRUMMETRICS_EMXUTIL_H

/* Include Files */
#include "computeSpectrumMetrics_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
extern void emxEnsureCapacity_real_T(emxArray_real_T *emxArray, int oldNumel);

extern void emxFree_real_T(emxArray_real_T **pEmxArray);

extern void emxInit_real_T(emxArray_real_T **pEmxArray, int numDimensions);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for computeSpectrumMetrics_emxutil.h
 *
 * [EOF]
 */
