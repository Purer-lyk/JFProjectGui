//
// File: DwtClass.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 15-Oct-2024 15:57:34
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
  static const double b[30]{
      6.1333599133076658E-8,  -6.3168823258836286E-7,  1.8112704079411339E-6,
      3.3629871817386934E-6,  -2.8133296266056077E-5,  2.5792699155329412E-5,
      0.00015589648992066324, -0.00035956524436251238, -0.00037348235413749945,
      0.0019433239803835008,  -0.00024175649075994896, -0.00648773456031396,
      0.0051010003604158027,  0.015083918027848276,    -0.020810050169700247,
      -0.025767007328474284,  0.054780550584460075,    0.033877143923422767,
      -0.11112093603736768,   -0.03966617655588589,    0.19014671400713157,
      0.0652829528487745,     -0.28888259656705512,    -0.19320413960920368,
      0.33900253545483178,    0.64581314035761672,     0.49263177170828681,
      0.20602386398705741,    0.0467433948927803,      0.0045385373615802619};
  static const double c_b[30]{
      -0.0045385373615802619,  0.0467433948927803,      -0.20602386398705741,
      0.49263177170828681,     -0.64581314035761672,    0.33900253545483178,
      0.19320413960920368,     -0.28888259656705512,    -0.0652829528487745,
      0.19014671400713157,     0.03966617655588589,     -0.11112093603736768,
      -0.033877143923422767,   0.054780550584460075,    0.025767007328474284,
      -0.020810050169700247,   -0.015083918027848276,   0.0051010003604158027,
      0.00648773456031396,     -0.00024175649075994896, -0.0019433239803835008,
      -0.00037348235413749945, 0.00035956524436251238,  0.00015589648992066324,
      -2.5792699155329412E-5,  -2.8133296266056077E-5,  -3.3629871817386934E-6,
      1.8112704079411339E-6,   6.3168823258836286E-7,   6.1333599133076658E-8};
  static const double d_b[30]{
      0.0045385373615802619,   0.0467433948927803,      0.20602386398705741,
      0.49263177170828681,     0.64581314035761672,     0.33900253545483178,
      -0.19320413960920368,    -0.28888259656705512,    0.0652829528487745,
      0.19014671400713157,     -0.03966617655588589,    -0.11112093603736768,
      0.033877143923422767,    0.054780550584460075,    -0.025767007328474284,
      -0.020810050169700247,   0.015083918027848276,    0.0051010003604158027,
      -0.00648773456031396,    -0.00024175649075994896, 0.0019433239803835008,
      -0.00037348235413749945, -0.00035956524436251238, 0.00015589648992066324,
      2.5792699155329412E-5,   -2.8133296266056077E-5,  3.3629871817386934E-6,
      1.8112704079411339E-6,   -6.3168823258836286E-7,  6.1333599133076658E-8};
  coder::array<double, 1U> b_y;
  coder::array<double, 1U> b_y1;
  coder::array<double, 1U> c_thresh;
  coder::array<double, 1U> xv;
  coder::array<double, 1U> y;
  coder::array<double, 1U> z;
  double xv_data[5014];
  double b_b;
  double bij;
  int I_data[10058];
  int l[10];
  int b_first[8];
  int last[8];
  int b_i;
  int i;
  int ib;
  int lx;
  int ma;
  int mc;
  int midm1;
  int vlen;
  //  选择小波基
  //  选择分解层数
  c_thresh.set_size(0);
  for (i = 0; i < 10; i++) {
    l[i] = 0;
  }
  xv.set_size(10000);
  for (b_i = 0; b_i < 10000; b_i++) {
    xv[b_i] = input[b_i];
  }
  l[9] = 10000;
  for (midm1 = 0; midm1 < 8; midm1++) {
    lx = xv.size(0);
    ma = xv.size(0) + 58;
    vlen = xv.size(0) + 58;
    if (0 <= vlen - 1) {
      std::memset(&I_data[0], 0, vlen * sizeof(int));
    }
    for (mc = 0; mc < 29; mc++) {
      I_data[mc] = 29 - mc;
    }
    for (mc = 0; mc < lx; mc++) {
      I_data[mc + 29] = mc + 1;
    }
    for (mc = 0; mc < 29; mc++) {
      I_data[(lx + mc) + 29] = lx - mc;
    }
    y.set_size(ma);
    for (b_i = 0; b_i < ma; b_i++) {
      y[b_i] = xv[I_data[b_i] - 1];
    }
    //
    mc = y.size(0);
    z.set_size(y.size(0) - 29);
    vlen = y.size(0);
    for (b_i = 0; b_i <= vlen - 30; b_i++) {
      z[b_i] = 0.0;
    }
    for (ib = 0; ib < 30; ib++) {
      for (i = 0; i <= mc - 30; i++) {
        z[i] = z[i] + b[29 - ib] * y[ib + i];
      }
    }
    //
    ma = ((xv.size(0) + 27) >> 1) + 1;
    vlen = (xv.size(0) + 27) >> 1;
    for (b_i = 0; b_i <= vlen; b_i++) {
      xv_data[b_i] = z[(b_i << 1) + 1];
    }
    //
    mc = y.size(0);
    z.set_size(y.size(0) - 29);
    vlen = y.size(0);
    for (b_i = 0; b_i <= vlen - 30; b_i++) {
      z[b_i] = 0.0;
    }
    for (ib = 0; ib < 30; ib++) {
      for (i = 0; i <= mc - 30; i++) {
        z[i] = z[i] + c_b[29 - ib] * y[ib + i];
      }
    }
    //
    xv.set_size(ma);
    for (b_i = 0; b_i < ma; b_i++) {
      xv[b_i] = xv_data[b_i];
    }
    vlen = (lx + 27) >> 1;
    b_y1.set_size((vlen + c_thresh.size(0)) + 1);
    for (b_i = 0; b_i <= vlen; b_i++) {
      b_y1[b_i] = z[(b_i << 1) + 1];
    }
    vlen = c_thresh.size(0);
    for (b_i = 0; b_i < vlen; b_i++) {
      b_y1[(b_i + ((lx + 27) >> 1)) + 1] = c_thresh[b_i];
    }
    c_thresh.set_size(b_y1.size(0));
    vlen = b_y1.size(0);
    for (b_i = 0; b_i < vlen; b_i++) {
      c_thresh[b_i] = b_y1[b_i];
    }
    l[8 - midm1] = ((lx + 27) >> 1) + 1;
  }
  b_y1.set_size(xv.size(0) + c_thresh.size(0));
  vlen = xv.size(0);
  for (b_i = 0; b_i < vlen; b_i++) {
    b_y1[b_i] = xv[b_i];
  }
  vlen = c_thresh.size(0);
  for (b_i = 0; b_i < vlen; b_i++) {
    b_y1[b_i + xv.size(0)] = c_thresh[b_i];
  }
  c_thresh.set_size(b_y1.size(0));
  vlen = b_y1.size(0);
  for (b_i = 0; b_i < vlen; b_i++) {
    c_thresh[b_i] = b_y1[b_i];
  }
  l[0] = xv.size(0);
  //  小波分解
  mc = c_thresh.size(0);
  b_y.set_size(c_thresh.size(0));
  for (midm1 = 0; midm1 < mc; midm1++) {
    b_y[midm1] = std::abs(c_thresh[midm1]);
  }
  //  估计噪声水平
  vlen = b_y.size(0);
  midm1 = 0;
  int exitg1;
  do {
    exitg1 = 0;
    if (midm1 <= vlen - 1) {
      if (std::isnan(b_y[midm1])) {
        bij = rtNaN;
        exitg1 = 1;
      } else {
        midm1++;
      }
    } else {
      midm1 = vlen >> 1;
      if ((vlen & 1) == 0) {
        coder::internal::quickselect(b_y, midm1 + 1, vlen, &bij, &mc, &lx);
        if (midm1 < mc) {
          coder::internal::quickselect(b_y, midm1, lx - 1, &b_b, &mc, &ma);
          if (std::isinf(bij)) {
            bij = (bij + b_b) / 2.0;
          } else {
            bij += (b_b - bij) / 2.0;
          }
        }
      } else {
        coder::internal::quickselect(b_y, midm1 + 1, vlen, &bij, &mc, &ma);
      }
      exitg1 = 1;
    }
  } while (exitg1 == 0);
  bij = bij / 0.025 * 4.2919320525786944;
  //  计算阈值
  b_i = c_thresh.size(0);
  for (midm1 = 0; midm1 < b_i; midm1++) {
    c_thresh[midm1] =
        c_thresh[midm1] * static_cast<double>(std::abs(c_thresh[midm1]) > bij);
  }
  //  阈值处理
  output.set_size(xv.size(0));
  b_i = xv.size(0);
  for (midm1 = 0; midm1 < b_i; midm1++) {
    output[midm1] = c_thresh[midm1];
  }
  for (int p{7}; p >= 0; p--) {
    int i1;
    boolean_T NONEMPTYD;
    for (i = 0; i < 8; i++) {
      b_first[i] = 0;
      last[i] = 0;
    }
    b_first[7] = l[0] + 1;
    last[7] = l[0] + l[1];
    for (mc = 6; mc >= 0; mc--) {
      b_first[mc] = b_first[mc + 1] + l[7 - mc];
      last[mc] = (b_first[mc] + l[8 - mc]) - 1;
    }
    if (b_first[p] > last[p]) {
      b_i = 0;
      i1 = 0;
    } else {
      b_i = b_first[p] - 1;
      i1 = last[p];
    }
    midm1 = i1 - b_i;
    NONEMPTYD = (midm1 != 0);
    i1 = output.size(0);
    if (output.size(0) != 0) {
      mc = (output.size(0) << 1) - 2;
      b_y.set_size(mc + 1);
      for (ma = 0; ma <= mc; ma++) {
        b_y[ma] = 0.0;
      }
      for (i = 0; i < i1; i++) {
        b_y[((i + 1) << 1) - 2] = output[i];
      }
      if (30 > b_y.size(0)) {
        mc = b_y.size(0) - 1;
        b_y1.set_size(b_y.size(0) + 29);
        vlen = b_y.size(0);
        for (i1 = 0; i1 <= vlen + 28; i1++) {
          b_y1[i1] = 0.0;
        }
        i1 = b_y.size(0) - 1;
        for (ib = 0; ib <= i1; ib++) {
          lx = mc - ib;
          bij = b_y[lx];
          for (i = 0; i < 30; i++) {
            vlen = lx + i;
            b_y1[vlen] = b_y1[vlen] + bij * d_b[i];
          }
        }
      } else {
        ma = b_y.size(0);
        b_y1.set_size(b_y.size(0) + 29);
        vlen = b_y.size(0);
        for (i1 = 0; i1 <= vlen + 28; i1++) {
          b_y1[i1] = 0.0;
        }
        for (ib = 0; ib < 30; ib++) {
          for (i = 0; i < ma; i++) {
            vlen = (i - ib) + 29;
            b_y1[vlen] = b_y1[vlen] + d_b[29 - ib] * b_y[i];
          }
        }
      }
      coder::wkeep1(b_y1, l[9 - p], output);
      if (NONEMPTYD) {
        b_y1.set_size(midm1);
        for (i1 = 0; i1 < midm1; i1++) {
          b_y1[i1] = c_thresh[b_i + i1];
        }
        coder::upsconv1(b_y1, static_cast<double>(l[9 - p]), b_y);
        vlen = output.size(0);
        for (b_i = 0; b_i < vlen; b_i++) {
          output[b_i] = output[b_i] + b_y[b_i];
        }
      }
    } else if (NONEMPTYD) {
      b_y1.set_size(midm1);
      for (i1 = 0; i1 < midm1; i1++) {
        b_y1[i1] = c_thresh[b_i + i1];
      }
      coder::upsconv1(b_y1, static_cast<double>(l[9 - p]), output);
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
