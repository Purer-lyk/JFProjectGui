#ifndef MAIN_WINDOW_H 
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QChart>
#include <QLineSeries>
#include <QChartView>
#include <QVBoxLayout>
#include <QValueAxis>
#include <QApplication>
#include "coder_array.h"
#include "collect_data.h"
#include "qcustomplot.h"
#include <QThread>
#include <QDebug>

QT_BEGIN_NAMESPACE
// namespace Ui { class MainWindow; }
using namespace QtCharts;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void Start();
    void Stop();
    void startContinu();
    void startSingle(float *input, float *output);

signals:
    void requestStop();
    void startContinuData();
    void startSingleData(float *input, float *output);

private slots:
    // void clearSeries();
    void updateOriData(QVector<qreal> x, QVector<qreal> y);
    void updateDwtData(bool judge, QVector<qreal> x, QVector<qreal> y);

private:
    // Ui::MainWindow *ui;
    QWidget *wid;
    QVBoxLayout *vlayout;
    QChart *oriChart, *dwtChart;
    QLineSeries *oriSeries, *dwtSeries;
    QChartView *oriChartView, *dwtChartView;
    QThread *collectThread;
    DataCollector *dataCollector;
    QCustomPlot *customplot, *customplot2;
    QLabel *messageDischarge;
    QScrollArea *messageArea;
    int falsecount;
};

#endif //MAIN_WINDOW_H