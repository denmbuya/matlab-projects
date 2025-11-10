/*
 * File: fftshift.c
 *
 * MATLAB Coder version            : 24.2
 * C/C++ source code generated on  : 28-Oct-2025 19:34:06
 */

/* Include Files */
#include "fftshift.h"
#include "rt_nonfinite.h"

/* Function Definitions */
/*
 * Arguments    : creal_T x[4096]
 * Return Type  : void
 */
void fftshift(creal_T x[4096])
{
  int dim;
  int j;
  int k;
  for (dim = 0; dim < 2; dim++) {
    int ic;
    if (dim + 1 <= 1) {
      ic = 4096;
    } else {
      ic = 1;
    }
    if (ic > 1) {
      int midoffset;
      int vlend2;
      int vstride;
      vlend2 = ic / 2;
      vstride = 1;
      for (k = 0; k < dim; k++) {
        vstride <<= 12;
      }
      midoffset = vlend2 * vstride - 1;
      if (vlend2 << 1 == ic) {
        int i1;
        i1 = 0;
        for (j = 0; j < vstride; j++) {
          int ib;
          i1++;
          ib = i1 + midoffset;
          for (k = 0; k < vlend2; k++) {
            double xtmp_im;
            double xtmp_re;
            int i;
            int xtmp_re_tmp;
            ic = k * vstride;
            xtmp_re_tmp = (i1 + ic) - 1;
            xtmp_re = x[xtmp_re_tmp].re;
            xtmp_im = x[xtmp_re_tmp].im;
            i = ib + ic;
            x[xtmp_re_tmp] = x[i];
            x[i].re = xtmp_re;
            x[i].im = xtmp_im;
          }
        }
      } else {
        int i1;
        i1 = 0;
        for (j = 0; j < vstride; j++) {
          double xtmp_im;
          double xtmp_re;
          int ib;
          i1++;
          ib = i1 + midoffset;
          xtmp_re = x[ib].re;
          xtmp_im = x[ib].im;
          for (k = 0; k < vlend2; k++) {
            int i;
            ic = ib + vstride;
            i = (i1 + k * vstride) - 1;
            x[ib] = x[i];
            x[i] = x[ic];
            ib = ic;
          }
          x[ib].re = xtmp_re;
          x[ib].im = xtmp_im;
        }
      }
    }
  }
}

/*
 * File trailer for fftshift.c
 *
 * [EOF]
 */
