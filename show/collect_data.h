#ifndef COLLECT_DATA_H
#define COLLECT_DATA_H

#include <QObject>
#include <QMutex>
#include <QVector>
#include "DwtClass.h"
#include "dwt.h"


#define SAMPLE_FREQUENCY 200000
#define RANGE_INDEX 1

#if RANGE_INDEX==1
  #define RANGE_VOLTAGE 2.5
#elif RANGE_INDEX==2
  #define RANGE_VOLTAGE 5
#elif RANGE_INDEX==3
  #define RANGE_VOLTAGE 10
#endif

class DataCollector : public QObject
{
    Q_OBJECT

public:
    explicit DataCollector(QObject *parent = nullptr);
    ~DataCollector();
    void startCollecting();
    void stopCollecting();

signals:
    void oriDataPoint(QVector<qreal> x, QVector<qreal> y);
    void dwtDataPoint(bool flag, QVector<qreal> x, QVector<qreal> y);
    // void repaint();

public slots:
    void continuData();
    void singleData(float *input, float *output);

private:
    int falseCount;
    bool m_collecting;
    DwtClass *dwtInstance;
    DwtWorker *dwtWorker;

    void voltageInit(short buffer[2*10000], float oriData[10000]);
    void sampleData(float oriData[10000]);
    float myFilter(float input);
    void writeFalseAlert(QVector<qreal> input, QVector<qreal> output);
};

#endif // COLLECT_DATA_H