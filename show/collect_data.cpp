#include "collect_data.h"
#include <QThread>
#include <QTime>
#include <cmath>
#include <QDebug>
#include "Usbe6104.h"
#include "rtwtypes.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <random>
#include <fstream>

void argInitRandom(float fvector[10000]){
    std::random_device rd;  // 非确定性随机数生成器
    std::mt19937 gen(rd()); // 以 rd() 作为种子初始化 Mersenne Twister 生成器

    // 创建一个在 [1, 100] 范围内均匀分布的分布
    std::uniform_int_distribution<> distrib(0, 3);

    // // 生成随机数
    // for(int i=0;i<10000;i++){
    //     fvector[i] = (float)distrib(gen);
    //     if(i%2==0 || i<5000 || (i>6000 && i<8000)) fvector[i] = 0.0f;
    // }
    std::string floder = "../file/Data_Ch01_20240919_";
    std::vector<std::string> filename = {"154124_alert.xls", "154142.xls", 
                                        "154119_alert.xls", "154122_alert.xls",
                                        "154121_alert.xls", "154110_alert.xls"};
    int index = distrib(gen);
    std::ifstream srcFile(floder+filename[index], std::ios::in);
    std::string s;
    int num = 0;
    while(std::getline(srcFile, s)){
        for(int i=0;i<s.size()-1;i++){
        if(s[i]=='\t' && s[i+1]!='\t'){
            s = s.substr(i+1, s.size()-i-1);
            break;
        }
        }
        fvector[num] = (float)std::stod(s);
        num++;
    }
}

DataCollector::DataCollector(QObject *parent) : 
    QObject(parent), 
    m_collecting(false),
    dwtInstance(new DwtClass()),
    dwtWorker(new DwtWorker())
{}

void DataCollector::startCollecting() {
    m_collecting = true;
    continuData();
    // QMetaObject::invokeMethod(this, "continuData", Qt::QueuedConnection);
    // QMetaObject::invokeMethod(this, "singleData", Qt::QueuedConnection);
}

void DataCollector::stopCollecting() {
    m_collecting = false;
}

void DataCollector::continuData() {
    qDebug()<<"Current ID:"<<QThread::currentThreadId();

    coder::array<double, 1U> output;
    double dv[10000], result[10000];
    float fdv[10000], fresult[10000];
    // QVector<qreal> Qinput, Qoutput;

    // while(OpenUSB()!=0){printf("open Usbe6104 failed!");}
    // Set_Range(0, RANGE_INDEX);
    while (m_collecting) {
        // Qinput.clear();
        // Qoutput.clear();
        // sampleData(fdv);
        argInitRandom(fdv);
        // dwtInstance->dwtProcess(dv, output);
        dwtWorker->dwt(fdv, fresult);
        // for(int i=0;i<10000;i++){
        //     fdv[i] = (float)dv[i];
        //     fresult[i] = (float)output[i];
        //     // Qinput.append(static_cast<qreal>(dv[i]));
        //     // Qoutput.append(static_cast<qreal>(result[i]));
        // }
        singleData(fdv, fresult);
        QThread::msleep(1);
    }
    CloseUSB();
}

void DataCollector::singleData(float *input, float *output){
    // emit repaint();
    // printf("input size:%lf\n", input[9999]);
    QVector<qreal> Qinput, Qoutput, Qx;
    // qDebug()<<"Current ID:"<<QThread::currentThreadId();
    for(int i=0;i<10000;i++){
        // printf("input data:%f\n", output[i]);
        qreal x = static_cast<qreal>(i);
        Qx.append(x);
        Qinput.append(static_cast<qreal>(input[i]));
        Qoutput.append(static_cast<qreal>(output[i]));
        // emit oriDataPoint(x, input[i]);
        // emit dwtDataPoint(x, static_cast<qreal>(output[i]));
    }
    bool dischargeFlag = dwtWorker->judgeDischarge(output);
    emit oriDataPoint(Qx, Qinput);
    emit dwtDataPoint(dischargeFlag, Qx, Qoutput);
}

void DataCollector::voltageInit(short buffer[2*10000], float oriData[10000])
{
    for(int i{0};i<10000;i++){
        oriData[i] = (float)buffer[2*i]*(float)RANGE_VOLTAGE/32768.0f;
        printf("%f\n",(float)oriData[i]);
    }
}

void DataCollector::sampleData(float oriData[10000])
{
    short buffer[2*10000];
    Ad_continu_conf(0, 0, 0, SAMPLE_FREQUENCY, 0, 0, 0, 0);
    // int bufSize = ;
    while(Get_AdBuf_Size(0) < 2*10000){}
    Read_AdBuf(0, buffer, 2*10000);
    Ad_continu_stop(0);
    voltageInit(buffer, oriData);
}

DataCollector::~DataCollector(){
    delete dwtInstance;
    delete dwtWorker;
}