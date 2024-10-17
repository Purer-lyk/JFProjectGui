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
#include <string>
#include <vector>
#include <ctime>

void argInitRandom(float fvector[10000]){
    std::random_device rd;  // 非确定性随机数生成器
    std::mt19937 gen(rd()); // 以 rd() 作为种子初始化 Mersenne Twister 生成器

    // 创建一个在 [1, 100] 范围内均匀分布的分布
    std::uniform_int_distribution<> distrib(0, 3);

    // 生成随机数
    // for(int i=0;i<10000;i++){
    //     fvector[i] = (float)distrib(gen);
    //     if(i%2==0 || i<5000 || (i>6000 && i<8000)) fvector[i] = 0.0f;
    // }
    std::string floder = "../file/Data_Ch01_20240919_";
    std::string filename[6] = {"154124_alert.xls", "154142.xls", 
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
    falseCount(0),
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

void DataCollector::writeFalseAlert(QVector<qreal> input, QVector<qreal> output) {
    // std::string timeStr = snprintf()
    std::time_t now = std::time(0);
    std::tm *localTime = std::localtime(&now);
    std::string nowTimeStr = std::to_string(1+localTime->tm_mon) + std::to_string(localTime->tm_mday) + 
                            std::to_string(localTime->tm_hour) + std::to_string(localTime->tm_sec);
    std::string saveName = "../file/falseData_" + nowTimeStr + "_" + std::to_string(falseCount++) + ".xls";
    std::ofstream srcFile(saveName);
    for(int i=0;i<10000;i++){
        std::string dataStr = std::to_string(i) + "\t" + std::to_string(input[i]) + "\t" + std::to_string(output[i]);
        srcFile << dataStr <<std::endl;
    }
    srcFile.close();
}

void DataCollector::continuData() {
    qDebug()<<"Current ID:"<<QThread::currentThreadId();

    coder::array<double, 1U> output;
    double dv[10000], result[10000];
    float fdv[10000], fresult[10000];
    // QVector<qreal> Qinput, Qoutput;

    while(OpenUSB()!=0){printf("open Usbe6104 failed!\n");}
    Set_Range(0, RANGE_INDEX);
    while (m_collecting) {
        // Qinput.clear();
        // Qoutput.clear();
        sampleData(fdv);
        // argInitRandom(fdv);
        // dwtInstance->dwtProcess(dv, output);
        dwtWorker->dwt(fdv, fresult);
        singleData(fdv, fresult);
        QThread::msleep(10);
    }
    CloseUSB();
}

void DataCollector::singleData(float *input, float *output){
    // printf("input size:%lf\n", input[9999]);
    QVector<qreal> Qinput, Qoutput, Qx;
    // qDebug()<<"Current ID:"<<QThread::currentThreadId();
    for(int i=0;i<10000;i++){
        // printf("input data:%f\n", output[i]);
        qreal x = static_cast<qreal>(i);
        Qx.append(x);
        Qinput.append(static_cast<qreal>(input[i]));
        Qoutput.append(static_cast<qreal>(output[i]));
    }
    bool dischargeFlag = dwtWorker->judgeDischarge(output);
    if(dischargeFlag) writeFalseAlert(Qinput, Qoutput);
    emit oriDataPoint(Qx, Qinput);
    emit dwtDataPoint(dischargeFlag, Qx, Qoutput);
}

void DataCollector::voltageInit(short buffer[2*10000], float oriData[10000])
{
    for(int i{0};i<10000;i++){
        oriData[i] = (float)buffer[2*i]*(float)RANGE_VOLTAGE/32768.0f;
        oriData[i] = myFilter(oriData[i]);
        // printf("%f\n",(float)oriData[i]);
    }
}

float DataCollector::myFilter(float input)
{
    static std::vector<float> Filterx(11-1, 0); // 输入延迟线
    static std::vector<float> Filtery(11-1, 0); // 输出延迟线

    float Filtera[11] = {1.0,
                        -5.53610687,
                        14.51983945,
                        -23.96210116,
                        27.69100998,
                        -23.40272218,
                        14.60528446,
                        -6.63575238,
                        2.10379443,
                        -0.42153555,
                        0.04070949};
    float Filterb[11] = {0.0069332,
                        0.0,
                        -0.03466598,
                        0.0,
                        0.06933196,
                        0.0,
                        -0.06933196,
                        0.0,
                        0.03466598,
                        0.0,
                        -0.0069332};
    float output = 0;
    
    // 计算分子部分
	output += Filterb[0] * input;
    for (int i = 1; i < 11; ++i) {
        output += Filterb[i] * Filterx[i-1];
    }

    // 计算分母部分，除了a[0]（通常为1）
    for (int j = 1; j < 11; ++j) {
        output -= Filtera[j] * Filtery[j-1];
    }

	// 更新延迟线
    Filterx.insert(Filterx.begin(), input);
    Filterx.pop_back(); // 移除最旧的输入值
    Filtery.insert(Filtery.begin(), output);
    Filtery.pop_back(); // 移除最旧的输入值

    return output;
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