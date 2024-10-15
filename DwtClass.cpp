//
// File: DwtClass.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 14-Oct-2024 10:58:51
//

// Include Files
#include "DwtClass.h"
#include "quickselect.h"
#include "rt_nonfinite.h"
#include "upsconv1.h"
#include "wkeep1.h"
#include "coder_array.h"
#include <cmath>
#include <cstring>

// Function Definitions
//
// Arguments    : void
// Return Type  : void
//
DwtClass::DwtClass()
{
}

//
// Arguments    : void
// Return Type  : void
//
DwtClass::~DwtClass()
{
  // (no terminate code required)
}

//
// Arguments    : const double input[10000]
//                coder::array<double, 1U> &output
// Return Type  : void
//
void DwtClass::dwtProcess(const double input[10000],
                          coder::array<double, 1U> &output)
{
  static const double b[14]{
      0.00035371380000103988, -0.0018016407039998328, 0.00042957797300470274,
      0.012550998556013784,   -0.01657454163101562,   -0.038029936935034633,
      0.0806126091510659,     0.071309219267050042,   -0.22403618499416572,
      -0.14390600392910627,   0.4697822874053586,     0.72913209084655506,
      0.39653931948230575,    0.077852054085062364};
  static const double b_b[14]{
      -0.077852054085062364, 0.39653931948230575,   -0.72913209084655506,
      0.4697822874053586,    0.14390600392910627,   -0.22403618499416572,
      -0.071309219267050042, 0.0806126091510659,    0.038029936935034633,
      -0.01657454163101562,  -0.012550998556013784, 0.00042957797300470274,
      0.0018016407039998328, 0.00035371380000103988};
  static const double c_b[14]{
      0.077852054085062364,   0.39653931948230575,   0.72913209084655506,
      0.4697822874053586,     -0.14390600392910627,  -0.22403618499416572,
      0.071309219267050042,   0.0806126091510659,    -0.038029936935034633,
      -0.01657454163101562,   0.012550998556013784,  0.00042957797300470274,
      -0.0018016407039998328, 0.00035371380000103988};
  coder::array<double, 1U> a__4;
  coder::array<double, 1U> b_y;
  coder::array<double, 1U> b_y1;
  coder::array<double, 1U> c_thresh;
  coder::array<double, 1U> xv;
  coder::array<double, 1U> y;
  coder::array<double, 1U> z;
  double xv_data[5006];
  double bij;
  double tmp;
  int I_data[10026];
  int l[6];
  int b_first[4];
  int last[4];
  int b_i;
  int i;
  int ib;
  int k;
  int ma;
  int mc;
  int midm1;
  int vlen;
  //  选择小波基
  //  选择分解层数
  c_thresh.set_size(0);
  for (i = 0; i < 6; i++) {
    l[i] = 0;
  }
  xv.set_size(10000);
  for (b_i = 0; b_i < 10000; b_i++) {
    xv[b_i] = input[b_i];
  }
  l[5] = 10000;
  for (k = 0; k < 4; k++) {
    midm1 = xv.size(0);
    ma = xv.size(0) + 26;
    i = xv.size(0) + 26;
    if (0 <= i - 1) {
      std::memset(&I_data[0], 0, i * sizeof(int));
    }
    for (mc = 0; mc < 13; mc++) {
      I_data[mc] = 13 - mc;
    }
    for (mc = 0; mc < midm1; mc++) {
      I_data[mc + 13] = mc + 1;
    }
    for (mc = 0; mc < 13; mc++) {
      I_data[(midm1 + mc) + 13] = midm1 - mc;
    }
    y.set_size(ma);
    for (b_i = 0; b_i < ma; b_i++) {
      y[b_i] = xv[I_data[b_i] - 1];
    }
    mc = y.size(0);
    z.set_size(y.size(0) - 13);
    i = y.size(0);
    for (b_i = 0; b_i <= i - 14; b_i++) {
      z[b_i] = 0.0;
    }
    for (ib = 0; ib < 14; ib++) {
      for (i = 0; i <= mc - 14; i++) {
        z[i] = z[i] + b[13 - ib] * y[ib + i];
      }
    }
    vlen = ((xv.size(0) + 11) >> 1) + 1;
    i = (xv.size(0) + 11) >> 1;
    for (b_i = 0; b_i <= i; b_i++) {
      xv_data[b_i] = z[(b_i << 1) + 1];
    }
    mc = y.size(0);
    z.set_size(y.size(0) - 13);
    i = y.size(0);
    for (b_i = 0; b_i <= i - 14; b_i++) {
      z[b_i] = 0.0;
    }
    for (ib = 0; ib < 14; ib++) {
      for (i = 0; i <= mc - 14; i++) {
        z[i] = z[i] + b_b[13 - ib] * y[ib + i];
      }
    }
    xv.set_size(vlen);
    for (b_i = 0; b_i < vlen; b_i++) {
      xv[b_i] = xv_data[b_i];
    }
    i = (midm1 + 11) >> 1;
    b_y1.set_size((i + c_thresh.size(0)) + 1);
    for (b_i = 0; b_i <= i; b_i++) {
      b_y1[b_i] = z[(b_i << 1) + 1];
    }
    i = c_thresh.size(0);
    for (b_i = 0; b_i < i; b_i++) {
      b_y1[(b_i + ((midm1 + 11) >> 1)) + 1] = c_thresh[b_i];
    }
    c_thresh.set_size(b_y1.size(0));
    i = b_y1.size(0);
    for (b_i = 0; b_i < i; b_i++) {
      c_thresh[b_i] = b_y1[b_i];
    }
    l[4 - k] = ((midm1 + 11) >> 1) + 1;
  }
  b_y1.set_size(xv.size(0) + c_thresh.size(0));
  i = xv.size(0);
  for (b_i = 0; b_i < i; b_i++) {
    b_y1[b_i] = xv[b_i];
  }
  i = c_thresh.size(0);
  for (b_i = 0; b_i < i; b_i++) {
    b_y1[b_i + xv.size(0)] = c_thresh[b_i];
  }
  c_thresh.set_size(b_y1.size(0));
  i = b_y1.size(0);
  for (b_i = 0; b_i < i; b_i++) {
    c_thresh[b_i] = b_y1[b_i];
  }
  l[0] = xv.size(0);
  //  小波分解
  mc = c_thresh.size(0);
  b_y.set_size(c_thresh.size(0));
  for (k = 0; k < mc; k++) {
    b_y[k] = std::abs(c_thresh[k]);
  }
  //  估计噪声水平
  vlen = b_y.size(0);
  if (b_y.size(0) == 0) {
    bij = rtNaN;
  } else {
    k = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (k <= vlen - 1) {
        if (std::isnan(b_y[k])) {
          bij = rtNaN;
          exitg1 = 1;
        } else {
          k++;
        }
      } else {
        if (vlen <= 4) {
          if (vlen == 0) {
            bij = rtNaN;
          } else if (vlen == 1) {
            bij = b_y[0];
          } else if (vlen == 2) {
            if (std::isinf(b_y[0])) {
              bij = (b_y[0] + b_y[1]) / 2.0;
            } else {
              bij = b_y[0] + (b_y[1] - b_y[0]) / 2.0;
            }
          } else if (vlen == 3) {
            if (b_y[0] < b_y[1]) {
              if (b_y[1] < b_y[2]) {
                ma = 1;
              } else if (b_y[0] < b_y[2]) {
                ma = 2;
              } else {
                ma = 0;
              }
            } else if (b_y[0] < b_y[2]) {
              ma = 0;
            } else if (b_y[1] < b_y[2]) {
              ma = 2;
            } else {
              ma = 1;
            }
            bij = b_y[ma];
          } else {
            if (b_y[0] < b_y[1]) {
              if (b_y[1] < b_y[2]) {
                mc = 0;
                ma = 1;
                vlen = 2;
              } else if (b_y[0] < b_y[2]) {
                mc = 0;
                ma = 2;
                vlen = 1;
              } else {
                mc = 2;
                ma = 0;
                vlen = 1;
              }
            } else if (b_y[0] < b_y[2]) {
              mc = 1;
              ma = 0;
              vlen = 2;
            } else if (b_y[1] < b_y[2]) {
              mc = 1;
              ma = 2;
              vlen = 0;
            } else {
              mc = 2;
              ma = 1;
              vlen = 0;
            }
            if (b_y[mc] < b_y[3]) {
              if (b_y[3] < b_y[vlen]) {
                if (std::isinf(b_y[ma])) {
                  bij = (b_y[ma] + b_y[3]) / 2.0;
                } else {
                  bij = b_y[ma] + (b_y[3] - b_y[ma]) / 2.0;
                }
              } else if (std::isinf(b_y[ma])) {
                bij = (b_y[ma] + b_y[vlen]) / 2.0;
              } else {
                bij = b_y[ma] + (b_y[vlen] - b_y[ma]) / 2.0;
              }
            } else if (std::isinf(b_y[mc])) {
              bij = (b_y[mc] + b_y[ma]) / 2.0;
            } else {
              bij = b_y[mc] + (b_y[ma] - b_y[mc]) / 2.0;
            }
          }
        } else {
          midm1 = vlen >> 1;
          if ((vlen & 1) == 0) {
            a__4.set_size(b_y.size(0));
            i = b_y.size(0);
            for (b_i = 0; b_i < i; b_i++) {
              a__4[b_i] = b_y[b_i];
            }
            coder::internal::quickselect(a__4, midm1 + 1, vlen, &bij, &mc, &ma);
            if (midm1 < mc) {
              coder::internal::quickselect(a__4, midm1, ma - 1, &tmp, &mc,
                                           &vlen);
              if (std::isinf(bij)) {
                bij = (bij + tmp) / 2.0;
              } else {
                bij += (tmp - bij) / 2.0;
              }
            }
          } else {
            a__4.set_size(b_y.size(0));
            i = b_y.size(0);
            for (b_i = 0; b_i < i; b_i++) {
              a__4[b_i] = b_y[b_i];
            }
            coder::internal::quickselect(a__4, midm1 + 1, vlen, &bij, &mc, &ma);
          }
        }
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  bij = bij / 0.1 * 4.2919320525786944;
  //  计算阈值
  b_i = c_thresh.size(0);
  for (k = 0; k < b_i; k++) {
    double x;
    tmp = std::abs(c_thresh[k]) - bij;
    tmp = (tmp + std::abs(tmp)) / 2.0;
    x = c_thresh[k];
    if (c_thresh[k] < 0.0) {
      x = -1.0;
    } else if (c_thresh[k] > 0.0) {
      x = 1.0;
    } else if (c_thresh[k] == 0.0) {
      x = 0.0;
    }
    c_thresh[k] = x * tmp;
  }
  //  阈值处理
  output.set_size(xv.size(0));
  b_i = xv.size(0);
  for (k = 0; k < b_i; k++) {
    output[k] = c_thresh[k];
  }
  b_first[3] = l[0] + 1;
  mc = l[0] + l[1];
  last[3] = mc;
  b_first[2] = mc + 1;
  mc = (mc + l[2]) + 1;
  last[2] = mc - 1;
  b_first[1] = mc;
  mc += l[3];
  last[1] = mc - 1;
  b_first[0] = mc;
  last[0] = (mc + l[4]) - 1;
  for (k = 3; k >= 0; k--) {
    int i1;
    boolean_T NONEMPTYD;
    if (b_first[k] > last[k]) {
      b_i = 0;
      i1 = 0;
    } else {
      b_i = b_first[k] - 1;
      i1 = last[k];
    }
    midm1 = i1 - b_i;
    NONEMPTYD = (midm1 != 0);
    i1 = output.size(0);
    if (output.size(0) != 0) {
      mc = (output.size(0) << 1) - 2;
      b_y.set_size(mc + 1);
      for (vlen = 0; vlen <= mc; vlen++) {
        b_y[vlen] = 0.0;
      }
      for (i = 0; i < i1; i++) {
        b_y[((i + 1) << 1) - 2] = output[i];
      }
      if (14 > b_y.size(0)) {
        ma = b_y.size(0) - 1;
        b_y1.set_size(b_y.size(0) + 13);
        i = b_y.size(0);
        for (i1 = 0; i1 <= i + 12; i1++) {
          b_y1[i1] = 0.0;
        }
        i1 = b_y.size(0) - 1;
        for (ib = 0; ib <= i1; ib++) {
          mc = ma - ib;
          bij = b_y[mc];
          for (i = 0; i < 14; i++) {
            vlen = mc + i;
            b_y1[vlen] = b_y1[vlen] + bij * c_b[i];
          }
        }
      } else {
        ma = b_y.size(0);
        b_y1.set_size(b_y.size(0) + 13);
        i = b_y.size(0);
        for (i1 = 0; i1 <= i + 12; i1++) {
          b_y1[i1] = 0.0;
        }
        for (ib = 0; ib < 14; ib++) {
          for (i = 0; i < ma; i++) {
            vlen = (i - ib) + 13;
            b_y1[vlen] = b_y1[vlen] + c_b[13 - ib] * b_y[i];
          }
        }
      }
      coder::wkeep1(b_y1, l[5 - k], output);
      if (NONEMPTYD) {
        b_y1.set_size(midm1);
        for (i1 = 0; i1 < midm1; i1++) {
          b_y1[i1] = c_thresh[b_i + i1];
        }
        coder::upsconv1(b_y1, static_cast<double>(l[5 - k]), b_y);
        i = output.size(0);
        for (b_i = 0; b_i < i; b_i++) {
          output[b_i] = output[b_i] + b_y[b_i];
        }
      }
    } else if (NONEMPTYD) {
      b_y1.set_size(midm1);
      for (i1 = 0; i1 < midm1; i1++) {
        b_y1[i1] = c_thresh[b_i + i1];
      }
      coder::upsconv1(b_y1, static_cast<double>(l[5 - k]), output);
    } else {
      output.set_size(0);
    }
  }
  //  小波重构
}

//
// File trailer for DwtClass.cpp
//
// [EOF]
//
