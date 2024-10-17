#ifndef DWT_H
#define DWT_H

class DwtWorker{

public:
    DwtWorker();
    ~DwtWorker();

    void dwt(float input[10000], float output[10000]);

    bool judgeDischarge(float output[10000]);

private:
    float globalThresh;
    int interval, minDischarge, maxDischarge;
};

#endif