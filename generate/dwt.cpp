#include "dwt.h"
#include "rtwtypes.h"
#include "DwtClass.h"
#include "coder_array.h"
#include "rt_nonfinite.h"
#include <cmath>

DwtClass *instancePtr = new DwtClass();

DwtWorker::DwtWorker(){
    
}

DwtWorker::~DwtWorker(){
    delete instancePtr;
}

void DwtWorker::dwt(float input[10000], float output[10000]){
    coder::array<double, 1U> result;
    double dv[10000];
    for(int i=0;i<10000;i++){
        dv[i] = (double)input[i];
        // printf("unusal data:%lf\n", dv[i]);
    }
    instancePtr->dwtProcess(dv, result);
    for(int i=0;i<10000;i++){
        output[i] = (float)result[i];
        // if(output[i]>0.2) printf("unusal data:%f\n", output[i]);
    }
}

bool DwtWorker::judgeDischarge(float output[10000]){
    float absOutput[10000];
    float globalMaxItem = abs(output[0]);
    for(int i=0;i<10000;i++){
        absOutput[i] = abs(output[i]);
        if(absOutput[i] > globalMaxItem) globalMaxItem = absOutput[i];
    }
    if(globalMaxItem < 0.2) return false;
    int count=0, quit=0, bandwidth=0;
    float maxItem=0;
    for(int i=0;i<10000;i++){
        if(maxItem != 0){
            if(absOutput[i]<=0.1) quit++;
            else{
                quit=0;
                bandwidth++;
            }
            if(quit>50){
                if(bandwidth>10){
                    count++;
                    // printf("discharge position:%d\n",i);
                }
                maxItem=0;
                quit=0;
            }
            continue;
        }
        if(absOutput[i] > globalMaxItem*0.6) maxItem = absOutput[i];
    }
    printf("Discharge count:%d\n", count);
    if(count > 0 && count < 5) return true;
    else return false;
}