//
// File: main.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 14-Oct-2024 10:58:51
//

/*************************************************************************/
/* This automatically generated example C++ main file shows how to call  */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/

// Include Files
#include "main.h"
#include "DwtClass.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "Usbe6104.h"
#include "main_window.h"
#include "dwt.h"
#include <fstream>
#include <QMetaType>

#define TEST_FILE "../file/Data_Ch01_20240919_154124_alert.xls"

// Function Declarations
static void argInit_10000x1_real_T(double result[10000]);

static double argInit_real_T();

static void main_dwtProcess(DwtWorker *instancePtr, MainWindow *window);

static void argInitFromTxt(float result[10000]);

// Function Definitions
//
// Arguments    : double result[10000]
// Return Type  : void
//
static void argInitFromTxt(float result[10000])
{
  std::ifstream srcFile(TEST_FILE, std::ios::in);
  std::string s;
  int num = 0;
  while(std::getline(srcFile, s)){
    for(int i=0;i<s.size()-1;i++){
      if(s[i]=='\t' && s[i+1]!='\t'){
        s = s.substr(i+1, s.size()-i-1);
        break;
      }
    }
    result[num] = (float)std::stod(s);
    // printf("unusal data:%f\n", result[num]);
    // if(result[num] > 1) printf("unusal data:%lf\n", result[num]);
    num++;
  }
}

// Function Definitions
//
// Arguments    : double result[10000]
// Return Type  : void
//
static void argInit_10000x1_real_T(double result[10000])
{
  // Loop over the array to initialize each element.
  for (int idx0{0}; idx0 < 10000; idx0++) {
    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result[idx0] = argInit_real_T();
  }
}

//
// Arguments    : void
// Return Type  : double
//
static double argInit_real_T()
{
  return 0.0;
}

//
// Arguments    : DwtClass *instancePtr
// Return Type  : void
//
static void main_dwtProcess(DwtWorker *instancePtr, MainWindow *window)
{
  // coder::array<double, 1U> output;
  double dv[10000], output[10000];
  float fdv[10000], foutput[10000];
  // Initialize function 'dwtProcess' input arguments.
  // Initialize function input argument 'input'.
  // Call the entry-point 'dwtProcess'.
  // argInit_10000x1_real_T(dv);
  // instancePtr->dwtProcess(dv, output);
  argInitFromTxt(fdv);
  instancePtr->dwt(fdv, foutput);
  // for (int i{0};i<10000;i++){
  //   fdv[i] = (float)dv[i];
  //   foutput[i] = (float)output[i];
  //   printf("input data:%f\n", fdv[i]);
  // }
  // window->startSingle(fdv, foutput);
  window->startContinu();
}

//
// Arguments    : int argc
//                char **argv
// Return Type  : int
//
int main(int argc, char *argv[])
{
  qRegisterMetaType<float*>("float*");
  qRegisterMetaType<double*>("double*");
  qRegisterMetaType<QVector<qreal>>("QVector<qreal>");
  QApplication a(argc, argv);
  MainWindow *w = new MainWindow();
  DwtWorker *classInstance = new DwtWorker();
  w->show();
  // Invoke the entry-point functions.
  // You can call entry-point functions multiple times.
  main_dwtProcess(classInstance, w);
  delete classInstance;
  return a.exec();
}

//
// File trailer for main.cpp
//
// [EOF]
//
