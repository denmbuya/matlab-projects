/*
 * File: findpeaks.c
 *
 * MATLAB Coder version            : 24.2
 * C/C++ source code generated on  : 28-Oct-2025 19:34:06
 */

/* Include Files */
#include "findpeaks.h"
#include "eml_setop.h"
#include "introsort.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : const double Yin[4096]
 *                double varargin_2
 *                double Ypk_data[]
 *                double Xpk_data[]
 *                int *Xpk_size
 * Return Type  : int
 */
int findpeaks(const double Yin[4096], double varargin_2, double Ypk_data[],
              double Xpk_data[], int *Xpk_size)
{
  double yk;
  double ykfirst;
  int c_data[8192];
  int iwork_data[8192];
  int fPk_data[4096];
  int iFinite_data[4096];
  int iInfinite_data[4096];
  int iPk_data[4096];
  int Ypk_size;
  int b_i;
  int c_size;
  int i;
  int k;
  int kfirst;
  int nInf;
  int nPk;
  int qEnd;
  short tmp_data[8192];
  char dir;
  boolean_T idelete_data[8192];
  boolean_T isinfykfirst;
  Ypk_size = -1;
  nInf = -1;
  dir = 'n';
  kfirst = -1;
  ykfirst = rtInf;
  isinfykfirst = true;
  for (k = 0; k < 4096; k++) {
    boolean_T isinfyk;
    yk = Yin[k];
    if (rtIsNaN(yk)) {
      yk = rtInf;
      isinfyk = true;
    } else if (rtIsInf(yk) && (yk > 0.0)) {
      isinfyk = true;
      nInf++;
      iInfinite_data[nInf] = k + 1;
    } else {
      isinfyk = false;
    }
    if (yk != ykfirst) {
      char previousdir;
      previousdir = dir;
      if (isinfyk || isinfykfirst) {
        dir = 'n';
      } else if (yk < ykfirst) {
        dir = 'd';
        if (previousdir == 'i') {
          Ypk_size++;
          iFinite_data[Ypk_size] = kfirst + 1;
        }
      } else {
        dir = 'i';
      }
      ykfirst = yk;
      kfirst = k;
      isinfykfirst = isinfyk;
    }
  }
  nPk = 0;
  if (Ypk_size + 1 < 1) {
    Ypk_size = -1;
  }
  i = Ypk_size + 1;
  for (k = 0; k < i; k++) {
    kfirst = iFinite_data[k];
    ykfirst = Yin[kfirst - 1];
    if ((ykfirst > varargin_2) &&
        (ykfirst - fmax(Yin[kfirst - 2], Yin[kfirst]) >= 0.0)) {
      nPk++;
      iPk_data[nPk - 1] = kfirst;
    }
  }
  if (nPk < 1) {
    nPk = 0;
  }
  if (nInf + 1 < 1) {
    nInf = -1;
  }
  c_size = do_vectors(iPk_data, nPk, iInfinite_data, nInf + 1, c_data, fPk_data,
                      &Ypk_size, iFinite_data, &kfirst);
  if (c_size == 0) {
    Ypk_size = 0;
  } else {
    int sortIdx_data[8192];
    i = c_size - 1;
    for (k = 1; k <= i; k += 2) {
      ykfirst = Yin[c_data[k - 1] - 1];
      if ((ykfirst >= Yin[c_data[k] - 1]) || rtIsNaN(ykfirst)) {
        sortIdx_data[k - 1] = k;
        sortIdx_data[k] = k + 1;
      } else {
        sortIdx_data[k - 1] = k + 1;
        sortIdx_data[k] = k;
      }
    }
    if (((unsigned int)c_size & 1U) != 0U) {
      sortIdx_data[c_size - 1] = c_size;
    }
    b_i = 2;
    while (b_i < c_size) {
      kfirst = b_i << 1;
      Ypk_size = 1;
      for (nPk = b_i + 1; nPk < c_size + 1; nPk = qEnd + b_i) {
        int kEnd;
        int q;
        nInf = Ypk_size - 1;
        q = nPk;
        qEnd = Ypk_size + kfirst;
        if (qEnd > c_size + 1) {
          qEnd = c_size + 1;
        }
        k = 0;
        kEnd = qEnd - Ypk_size;
        while (k + 1 <= kEnd) {
          ykfirst = Yin[c_data[sortIdx_data[nInf] - 1] - 1];
          i = sortIdx_data[q - 1];
          if ((ykfirst >= Yin[c_data[i - 1] - 1]) || rtIsNaN(ykfirst)) {
            iwork_data[k] = sortIdx_data[nInf];
            nInf++;
            if (nInf + 1 == nPk) {
              while (q < qEnd) {
                k++;
                iwork_data[k] = sortIdx_data[q - 1];
                q++;
              }
            }
          } else {
            iwork_data[k] = i;
            q++;
            if (q == qEnd) {
              while (nInf + 1 < nPk) {
                k++;
                iwork_data[k] = sortIdx_data[nInf];
                nInf++;
              }
            }
          }
          k++;
        }
        for (k = 0; k < kEnd; k++) {
          sortIdx_data[(Ypk_size + k) - 1] = iwork_data[k];
        }
        Ypk_size = qEnd;
      }
      b_i = kfirst;
    }
    memset(&idelete_data[0], 0, (unsigned int)c_size * sizeof(boolean_T));
    for (b_i = 0; b_i < c_size; b_i++) {
      if (!idelete_data[b_i]) {
        ykfirst = (double)(c_data[sortIdx_data[b_i] - 1] - 1) + 1.0;
        for (kfirst = 0; kfirst < c_size; kfirst++) {
          Ypk_size = (c_size - kfirst) - 1;
          yk = (double)(c_data[sortIdx_data[Ypk_size] - 1] - 1) + 1.0;
          idelete_data[Ypk_size] =
              (idelete_data[Ypk_size] ||
               ((yk >= ykfirst - 10.0) && (yk <= ykfirst + 10.0)));
        }
        idelete_data[b_i] = false;
      }
    }
    Ypk_size = 0;
    kfirst = 0;
    for (b_i = 0; b_i < c_size; b_i++) {
      if (!idelete_data[b_i]) {
        Ypk_size++;
        tmp_data[kfirst] = (short)b_i;
        kfirst++;
      }
    }
    for (i = 0; i < Ypk_size; i++) {
      iwork_data[i] = sortIdx_data[tmp_data[i]];
    }
    if (Ypk_size != 0) {
      introsort(iwork_data, Ypk_size);
    }
  }
  if (Ypk_size > 4096) {
    Ypk_size = 4096;
  }
  *Xpk_size = Ypk_size;
  for (i = 0; i < Ypk_size; i++) {
    kfirst = c_data[iwork_data[i] - 1];
    Ypk_data[i] = Yin[kfirst - 1];
    Xpk_data[i] = (short)((short)(kfirst - 1) + 1);
  }
  return Ypk_size;
}

/*
 * File trailer for findpeaks.c
 *
 * [EOF]
 */
