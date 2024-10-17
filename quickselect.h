//
// File: quickselect.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 15-Oct-2024 15:57:34
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
