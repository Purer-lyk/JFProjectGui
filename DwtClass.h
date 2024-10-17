//
// File: DwtClass.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 15-Oct-2024 15:57:34
//

#ifndef DWTCLASS_H
#define DWTCLASS_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
class DwtClass {
public:
  DwtClass();
  ~DwtClass();
  void dwtProcess(const double input[10000], coder::array<double, 1U> &output);
};

#endif
//
// File trailer for DwtClass.h
//
// [EOF]
//
