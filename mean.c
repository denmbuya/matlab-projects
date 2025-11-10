/*
 * File: mean.c
 *
 * MATLAB Coder version            : 24.2
 * C/C++ source code generated on  : 28-Oct-2025 19:34:06
 */

/* Include Files */
#include "mean.h"
#include "rt_nonfinite.h"

/* Function Definitions */
/*
 * Arguments    : const double x[1024]
 * Return Type  : double
 */
double b_mean(const double x[1024])
{
  double y;
  int k;
  y = x[0];
  for (k = 0; k < 1023; k++) {
    y += x[k + 1];
  }
  y /= 1024.0;
  return y;
}

/*
 * Arguments    : const double x[4096]
 * Return Type  : double
 */
double mean(const double x[4096])
{
  double accumulatedData;
  double y;
  int ib;
  int k;
  accumulatedData = x[0];
  for (k = 0; k < 1023; k++) {
    accumulatedData += x[k + 1];
  }
  for (ib = 0; ib < 3; ib++) {
    int xblockoffset;
    xblockoffset = (ib + 1) << 10;
    y = x[xblockoffset];
    for (k = 0; k < 1023; k++) {
      y += x[(xblockoffset + k) + 1];
    }
    accumulatedData += y;
  }
  return accumulatedData / 4096.0;
}

/*
 * File trailer for mean.c
 *
 * [EOF]
 */
