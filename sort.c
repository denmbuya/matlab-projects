/*
 * File: sort.c
 *
 * MATLAB Coder version            : 24.2
 * C/C++ source code generated on  : 28-Oct-2025 19:34:06
 */

/* Include Files */
#include "sort.h"
#include "rt_nonfinite.h"
#include "sortIdx.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : double x[4096]
 * Return Type  : void
 */
void sort(double x[4096])
{
  double xwork[4096];
  double x4[4];
  int idx[4096];
  int iwork[4096];
  int b;
  int b_b;
  int i;
  int i1;
  int i3;
  int i4;
  int ib;
  int k;
  int nNaNs;
  int offset;
  int quartetOffset;
  short idx4[4];
  memset(&idx[0], 0, 4096U * sizeof(int));
  x4[0] = 0.0;
  idx4[0] = 0;
  x4[1] = 0.0;
  idx4[1] = 0;
  x4[2] = 0.0;
  idx4[2] = 0;
  x4[3] = 0.0;
  idx4[3] = 0;
  nNaNs = 0;
  ib = 0;
  for (k = 0; k < 4096; k++) {
    if (rtIsNaN(x[k])) {
      idx[4095 - nNaNs] = k + 1;
      xwork[4095 - nNaNs] = x[k];
      nNaNs++;
    } else {
      ib++;
      idx4[ib - 1] = (short)(k + 1);
      x4[ib - 1] = x[k];
      if (ib == 4) {
        double d;
        double d1;
        quartetOffset = k - nNaNs;
        if (x4[0] <= x4[1]) {
          i1 = 1;
          ib = 2;
        } else {
          i1 = 2;
          ib = 1;
        }
        if (x4[2] <= x4[3]) {
          i3 = 3;
          i4 = 4;
        } else {
          i3 = 4;
          i4 = 3;
        }
        d = x4[i1 - 1];
        d1 = x4[i3 - 1];
        if (d <= d1) {
          d = x4[ib - 1];
          if (d <= d1) {
            i = i1;
            offset = ib;
            i1 = i3;
            ib = i4;
          } else if (d <= x4[i4 - 1]) {
            i = i1;
            offset = i3;
            i1 = ib;
            ib = i4;
          } else {
            i = i1;
            offset = i3;
            i1 = i4;
          }
        } else {
          d1 = x4[i4 - 1];
          if (d <= d1) {
            if (x4[ib - 1] <= d1) {
              i = i3;
              offset = i1;
              i1 = ib;
              ib = i4;
            } else {
              i = i3;
              offset = i1;
              i1 = i4;
            }
          } else {
            i = i3;
            offset = i4;
          }
        }
        idx[quartetOffset - 3] = idx4[i - 1];
        idx[quartetOffset - 2] = idx4[offset - 1];
        idx[quartetOffset - 1] = idx4[i1 - 1];
        idx[quartetOffset] = idx4[ib - 1];
        x[quartetOffset - 3] = x4[i - 1];
        x[quartetOffset - 2] = x4[offset - 1];
        x[quartetOffset - 1] = x4[i1 - 1];
        x[quartetOffset] = x4[ib - 1];
        ib = 0;
      }
    }
  }
  if (ib > 0) {
    signed char perm[4];
    perm[1] = 0;
    perm[2] = 0;
    perm[3] = 0;
    if (ib == 1) {
      perm[0] = 1;
    } else if (ib == 2) {
      if (x4[0] <= x4[1]) {
        perm[0] = 1;
        perm[1] = 2;
      } else {
        perm[0] = 2;
        perm[1] = 1;
      }
    } else if (x4[0] <= x4[1]) {
      if (x4[1] <= x4[2]) {
        perm[0] = 1;
        perm[1] = 2;
        perm[2] = 3;
      } else if (x4[0] <= x4[2]) {
        perm[0] = 1;
        perm[1] = 3;
        perm[2] = 2;
      } else {
        perm[0] = 3;
        perm[1] = 1;
        perm[2] = 2;
      }
    } else if (x4[0] <= x4[2]) {
      perm[0] = 2;
      perm[1] = 1;
      perm[2] = 3;
    } else if (x4[1] <= x4[2]) {
      perm[0] = 2;
      perm[1] = 3;
      perm[2] = 1;
    } else {
      perm[0] = 3;
      perm[1] = 2;
      perm[2] = 1;
    }
    i = (unsigned char)ib;
    for (k = 0; k < i; k++) {
      quartetOffset = ((k - nNaNs) - ib) + 4096;
      offset = perm[k];
      idx[quartetOffset] = idx4[offset - 1];
      x[quartetOffset] = x4[offset - 1];
    }
  }
  quartetOffset = (nNaNs >> 1) + 4096;
  for (k = 0; k <= quartetOffset - 4097; k++) {
    ib = (k - nNaNs) + 4096;
    i1 = idx[ib];
    idx[ib] = idx[4095 - k];
    idx[4095 - k] = i1;
    x[ib] = xwork[4095 - k];
    x[4095 - k] = xwork[ib];
  }
  if (((unsigned int)nNaNs & 1U) != 0U) {
    i = quartetOffset - nNaNs;
    x[i] = xwork[i];
  }
  memset(&iwork[0], 0, 4096U * sizeof(int));
  quartetOffset = 2;
  if (4096 - nNaNs > 1) {
    int nBlocks;
    nBlocks = (4096 - nNaNs) >> 8;
    if (nBlocks > 0) {
      for (b = 0; b < nBlocks; b++) {
        double b_xwork[256];
        short b_iwork[256];
        offset = (b << 8) - 1;
        for (b_b = 0; b_b < 6; b_b++) {
          int bLen;
          int bLen2;
          bLen = 1 << (b_b + 2);
          bLen2 = bLen << 1;
          i = 256 >> (b_b + 3);
          for (k = 0; k < i; k++) {
            i1 = (offset + k * bLen2) + 1;
            for (i3 = 0; i3 < bLen2; i3++) {
              ib = i1 + i3;
              b_iwork[i3] = (short)idx[ib];
              b_xwork[i3] = x[ib];
            }
            i4 = 0;
            quartetOffset = bLen;
            ib = i1 - 1;
            int exitg1;
            do {
              exitg1 = 0;
              ib++;
              if (b_xwork[i4] <= b_xwork[quartetOffset]) {
                idx[ib] = b_iwork[i4];
                x[ib] = b_xwork[i4];
                if (i4 + 1 < bLen) {
                  i4++;
                } else {
                  exitg1 = 1;
                }
              } else {
                idx[ib] = b_iwork[quartetOffset];
                x[ib] = b_xwork[quartetOffset];
                if (quartetOffset + 1 < bLen2) {
                  quartetOffset++;
                } else {
                  ib -= i4;
                  for (i3 = i4 + 1; i3 <= bLen; i3++) {
                    quartetOffset = ib + i3;
                    idx[quartetOffset] = b_iwork[i3 - 1];
                    x[quartetOffset] = b_xwork[i3 - 1];
                  }
                  exitg1 = 1;
                }
              }
            } while (exitg1 == 0);
          }
        }
      }
      quartetOffset = nBlocks << 8;
      ib = 4096 - (nNaNs + quartetOffset);
      if (ib > 0) {
        memset(&iwork[0], 0, 4096U * sizeof(int));
        merge_block(idx, x, quartetOffset, ib, 2, iwork, xwork);
      }
      quartetOffset = 8;
    }
    merge_block(idx, x, 0, 4096 - nNaNs, quartetOffset, iwork, xwork);
  }
}

/*
 * File trailer for sort.c
 *
 * [EOF]
 */
