//
// File: _coder_dwtProcess_api.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 14-Oct-2024 10:58:51
//

#ifndef _CODER_DWTPROCESS_API_H
#define _CODER_DWTPROCESS_API_H

// Include Files
#include "coder_array_mex.h"
#include "emlrt.h"
#include "tmwtypes.h"
#include <algorithm>
#include <cstring>

// Variable Declarations
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

// Function Declarations
void dwtProcess(real_T input[10000], coder::array<real_T, 1U> *output);

void dwtProcess_api(const mxArray *prhs, const mxArray **plhs);

void dwtProcess_atexit();

void dwtProcess_initialize();

void dwtProcess_terminate();

void dwtProcess_xil_shutdown();

void dwtProcess_xil_terminate();

#endif
//
// File trailer for _coder_dwtProcess_api.h
//
// [EOF]
//
