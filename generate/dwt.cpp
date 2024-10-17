#include "dwt.h"
#include "rtwtypes.h"
#include "DwtClass.h"
#include "coder_array.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <fstream>
#include <string>

DwtClass *instancePtr = new DwtClass();

DwtWorker::DwtWorker(){
    globalThresh = 0.5;
    interval = 3500;
    minDischarge=1;
    maxDischarge=5;
    std::string paramFile = "./param.txt";
    std::ifstream srcFile(paramFile, std::ios::in);
    std::string s, paramName, paramStr;
    while(std::getline(srcFile, s)){
        // printf("str:%s\n", s);
        for(int i=0;i<s.size()-1;i++){
            if(s[i]==' ' && s[i+1]!=' '){
                paramName = s.substr(0, i);
                paramStr = s.substr(i+1, s.size()-i-1);
                if(paramName == "globalThresh") globalThresh = std::stof(paramStr);
                else if(paramName == "interval") interval = std::stoi(paramStr);
                else if(paramName == "minDischarge") minDischarge = std::stoi(paramStr);
                else if(paramName == "maxDischarge") maxDischarge = std::stoi(paramStr);
                break;
            }
        }
    }
    printf("globalThresh:%f\n", globalThresh);
    printf("interval:%d\n", interval);
    printf("minDischarge:%d\n", minDischarge);
    printf("maxDischarge:%d\n", maxDischarge);
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
    if(globalMaxItem < globalThresh) return false;
    int count=0, realcount = 0, quit=0, bandwidth=0, lasti = -interval;
    float maxItem=0;
    for(int i=0;i<10000;i++){
        if(maxItem != 0){
            if(absOutput[i]<=maxItem/3.0f) quit++;
            else{
                quit=0;
                bandwidth++;
            }
            if(quit>50){
                if(bandwidth>10){
                    count++;
                    if(i - lasti > interval) realcount++;
                    lasti=i;
                    // printf("discharge position:%d\n",i);
                }
                maxItem=0;
                quit=0;
            }
            continue;
        }
        if(absOutput[i] > globalThresh) maxItem = absOutput[i];
    }
    printf("Discharge count:%d\n", count);
    if(count > minDischarge && count < maxDischarge && realcount > minDischarge && realcount < maxDischarge) return true;
    else return false;
}