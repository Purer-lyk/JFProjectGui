//
// File: upsconv1.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 14-Oct-2024 10:58:51
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
  static const double b[14]{
      0.00035371380000103988, 0.0018016407039998328, 0.00042957797300470274,
      -0.012550998556013784,  -0.01657454163101562,  0.038029936935034633,
      0.0806126091510659,     -0.071309219267050042, -0.22403618499416572,
      0.14390600392910627,    0.4697822874053586,    -0.72913209084655506,
      0.39653931948230575,    -0.077852054085062364};
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
    if (14 > y.size(0)) {
      m = y.size(0) - 1;
      b_y1.set_size(y.size(0) + 13);
      b_y = y.size(0);
      for (i = 0; i <= b_y + 12; i++) {
        b_y1[i] = 0.0;
      }
      i = y.size(0) - 1;
      for (int ib{0}; ib <= i; ib++) {
        double bij;
        b_y = m - ib;
        bij = y[b_y];
        for (b_i = 0; b_i < 14; b_i++) {
          int y1_tmp;
          y1_tmp = b_y + b_i;
          b_y1[y1_tmp] = b_y1[y1_tmp] + bij * b[b_i];
        }
      }
    } else {
      m = y.size(0);
      b_y1.set_size(y.size(0) + 13);
      b_y = y.size(0);
      for (i = 0; i <= b_y + 12; i++) {
        b_y1[i] = 0.0;
      }
      for (int ib{0}; ib < 14; ib++) {
        for (b_i = 0; b_i < m; b_i++) {
          int y1_tmp;
          y1_tmp = (b_i - ib) + 13;
          b_y1[y1_tmp] = b_y1[y1_tmp] + b[13 - ib] * y[b_i];
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
