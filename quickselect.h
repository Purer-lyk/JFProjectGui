//
// File: quickselect.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 14-Oct-2024 10:58:51
//

#ifndef QUICKSELECT_H
#define QUICKSELECT_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace internal {
void quickselect(::coder::array<double, 1U> &v, int n, int vlen, double *vn,
                 int *nfirst, int *nlast);

}
} // namespace coder

#endif
//
// File trailer for quickselect.h
//
// [EOF]
//
