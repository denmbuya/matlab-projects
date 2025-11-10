/*
 * File: introsort.c
 *
 * MATLAB Coder version            : 24.2
 * C/C++ source code generated on  : 28-Oct-2025 19:34:06
 */

/* Include Files */
#include "introsort.h"
#include "heapsort.h"
#include "insertionsort.h"
#include "rt_nonfinite.h"

/* Type Definitions */
#ifndef typedef_struct_T
#define typedef_struct_T
typedef struct {
  int xstart;
  int xend;
  int depth;
} struct_T;
#endif /* typedef_struct_T */

/* Function Definitions */
/*
 * Arguments    : int x_data[]
 *                int xend
 * Return Type  : void
 */
void introsort(int x_data[], int xend)
{
  struct_T frame;
  int pmax;
  int pmin;
  if (xend > 1) {
    if (xend <= 32) {
      insertionsort(x_data, 1, xend);
    } else {
      struct_T st_d_data[120];
      int MAXDEPTH;
      int pow2p;
      int st_n;
      int xmid;
      boolean_T exitg1;
      pmax = 31;
      pmin = 0;
      exitg1 = false;
      while ((!exitg1) && (pmax - pmin > 1)) {
        xmid = (pmin + pmax) >> 1;
        pow2p = 1 << xmid;
        if (pow2p == xend) {
          pmax = xmid;
          exitg1 = true;
        } else if (pow2p > xend) {
          pmax = xmid;
        } else {
          pmin = xmid;
        }
      }
      MAXDEPTH = (pmax - 1) << 1;
      frame.xstart = 1;
      frame.xend = xend;
      frame.depth = 0;
      st_d_data[0] = frame;
      st_n = 1;
      while (st_n > 0) {
        frame = st_d_data[st_n - 1];
        st_n--;
        pmin = frame.xend - frame.xstart;
        if (pmin + 1 <= 32) {
          insertionsort(x_data, frame.xstart, frame.xend);
        } else if (frame.depth == MAXDEPTH) {
          b_heapsort(x_data, frame.xstart, frame.xend);
        } else {
          int t;
          xmid = (frame.xstart + pmin / 2) - 1;
          pmin = x_data[frame.xstart - 1];
          if (x_data[xmid] < pmin) {
            x_data[frame.xstart - 1] = x_data[xmid];
            x_data[xmid] = pmin;
          }
          pmin = x_data[frame.xstart - 1];
          pmax = x_data[frame.xend - 1];
          if (pmax < pmin) {
            x_data[frame.xstart - 1] = pmax;
            x_data[frame.xend - 1] = pmin;
          }
          pmin = x_data[frame.xend - 1];
          if (pmin < x_data[xmid]) {
            t = x_data[xmid];
            x_data[xmid] = pmin;
            x_data[frame.xend - 1] = t;
          }
          pow2p = x_data[xmid];
          x_data[xmid] = x_data[frame.xend - 2];
          x_data[frame.xend - 2] = pow2p;
          pmax = frame.xstart - 1;
          pmin = frame.xend - 2;
          int exitg2;
          do {
            exitg2 = 0;
            for (pmax++; x_data[pmax] < pow2p; pmax++) {
            }
            for (pmin--; pow2p < x_data[pmin]; pmin--) {
            }
            if (pmax + 1 >= pmin + 1) {
              exitg2 = 1;
            } else {
              t = x_data[pmax];
              x_data[pmax] = x_data[pmin];
              x_data[pmin] = t;
            }
          } while (exitg2 == 0);
          x_data[frame.xend - 2] = x_data[pmax];
          x_data[pmax] = pow2p;
          if (pmax + 2 < frame.xend) {
            st_d_data[st_n].xstart = pmax + 2;
            st_d_data[st_n].xend = frame.xend;
            st_d_data[st_n].depth = frame.depth + 1;
            st_n++;
          }
          if (frame.xstart < pmax + 1) {
            st_d_data[st_n].xstart = frame.xstart;
            st_d_data[st_n].xend = pmax + 1;
            st_d_data[st_n].depth = frame.depth + 1;
            st_n++;
          }
        }
      }
    }
  }
}

/*
 * File trailer for introsort.c
 *
 * [EOF]
 */
