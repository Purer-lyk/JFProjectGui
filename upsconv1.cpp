//
// File: upsconv1.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 15-Oct-2024 15:57:34
//

// Include Files
#include "upsconv1.h"
#include "rt_nonfinite.h"
#include "wkeep1.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const ::coder::array<double, 1U> &x
//                double s
//                ::coder::array<double, 1U> &y
// Return Type  : void
//
namespace coder {
void upsconv1(const ::coder::array<double, 1U> &x, double s,
              ::coder::array<double, 1U> &y)
{
  static const double b[30]{
      6.1333599133076658E-8,  6.3168823258836286E-7,   1.8112704079411339E-6,
      -3.3629871817386934E-6, -2.8133296266056077E-5,  -2.5792699155329412E-5,
      0.00015589648992066324, 0.00035956524436251238,  -0.00037348235413749945,
      -0.0019433239803835008, -0.00024175649075994896, 0.00648773456031396,
      0.0051010003604158027,  -0.015083918027848276,   -0.020810050169700247,
      0.025767007328474284,   0.054780550584460075,    -0.033877143923422767,
      -0.11112093603736768,   0.03966617655588589,     0.19014671400713157,
      -0.0652829528487745,    -0.28888259656705512,    0.19320413960920368,
      0.33900253545483178,    -0.64581314035761672,    0.49263177170828681,
      -0.20602386398705741,   0.0467433948927803,      -0.0045385373615802619};
  array<double, 1U> b_y1;
  if (x.size(0) == 0) {
    y.set_size(1);
    y[0] = 0.0;
  } else {
    int b_i;
    int b_y;
    int i;
    int m;
    m = x.size(0);
    b_y = (x.size(0) << 1) - 2;
    y.set_size(b_y + 1);
    for (i = 0; i <= b_y; i++) {
      y[i] = 0.0;
    }
    for (b_i = 0; b_i < m; b_i++) {
      y[((b_i + 1) << 1) - 2] = x[b_i];
    }
    if (30 > y.size(0)) {
      m = y.size(0) - 1;
      b_y1.set_size(y.size(0) + 29);
      b_y = y.size(0);
      for (i = 0; i <= b_y + 28; i++) {
        b_y1[i] = 0.0;
      }
      i = y.size(0) - 1;
      for (int ib{0}; ib <= i; ib++) {
        double bij;
        b_y = m - ib;
        bij = y[b_y];
        for (b_i = 0; b_i < 30; b_i++) {
          int y1_tmp;
          y1_tmp = b_y + b_i;
          b_y1[y1_tmp] = b_y1[y1_tmp] + bij * b[b_i];
        }
      }
    } else {
      m = y.size(0);
      b_y1.set_size(y.size(0) + 29);
      b_y = y.size(0);
      for (i = 0; i <= b_y + 28; i++) {
        b_y1[i] = 0.0;
      }
      for (int ib{0}; ib < 30; ib++) {
        for (b_i = 0; b_i < m; b_i++) {
          int y1_tmp;
          y1_tmp = (b_i - ib) + 29;
          b_y1[y1_tmp] = b_y1[y1_tmp] + b[29 - ib] * y[b_i];
        }
      }
    }
    wkeep1(b_y1, static_cast<int>(s), y);
  }
}

} // namespace coder

//
// File trailer for upsconv1.cpp
//
// [EOF]
//
