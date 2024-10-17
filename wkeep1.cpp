//
// File: wkeep1.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 15-Oct-2024 15:57:34
//

// Include Files
#include "wkeep1.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const ::coder::array<double, 1U> &x
//                int len
//                ::coder::array<double, 1U> &y
// Return Type  : void
//
namespace coder {
void wkeep1(const ::coder::array<double, 1U> &x, int len,
            ::coder::array<double, 1U> &y)
{
  int d;
  int last;
  int nxmm;
  d = 0;
  last = x.size(0);
  if (len < x.size(0)) {
    nxmm = x.size(0) - len;
    d = nxmm >> 1;
    last = x.size(0) - d;
    if ((nxmm & 1) != 0) {
      last--;
    }
  }
  if (d + 1 > last) {
    d = 0;
    last = 0;
  }
  last -= d;
  y.set_size(last);
  for (nxmm = 0; nxmm < last; nxmm++) {
    y[nxmm] = x[d + nxmm];
  }
}

} // namespace coder

//
// File trailer for wkeep1.cpp
//
// [EOF]
//
