/*
 * File: insertionsort.c
 *
 * MATLAB Coder version            : 24.2
 * C/C++ source code generated on  : 28-Oct-2025 19:34:06
 */

/* Include Files */
#include "insertionsort.h"
#include "rt_nonfinite.h"

/* Function Definitions */
/*
 * Arguments    : int x_data[]
 *                int xstart
 *                int xend
 * Return Type  : void
 */
void insertionsort(int x_data[], int xstart, int xend)
{
  int i;
  int k;
  i = xstart + 1;
  for (k = i; k <= xend; k++) {
    int idx;
    int xc;
    boolean_T exitg1;
    xc = x_data[k - 1];
    idx = k - 1;
    exitg1 = false;
    while ((!exitg1) && (idx >= xstart)) {
      int i1;
      i1 = x_data[idx - 1];
      if (xc < i1) {
        x_data[idx] = i1;
        idx--;
      } else {
        exitg1 = true;
      }
    }
    x_data[idx] = xc;
  }
}

/*
 * File trailer for insertionsort.c
 *
 * [EOF]
 */
