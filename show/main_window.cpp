#include "main_window.h"
// #include "./ui_mainwindow.h"
//ui_mainwindow.h对应qtcreator中的mainwindow.ui图形化创建的窗口

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    wid(new QWidget(this)),
    vlayout(new QVBoxLayout()),
    oriChart(new QChart()),
    oriSeries(new QLineSeries()),
    oriChartView(new QChartView(oriChart)),
    dwtChart(new QChart()),
    dwtSeries(new QLineSeries()),
    dwtChartView(new QChartView(dwtChart)),
    collectThread(new QThread()),
    dataCollector(new DataCollector()),
    customplot(new QCustomPlot()),
    customplot2(new QCustomPlot())
{
    this->setCentralWidget(wid);

    // QValueAxis *axisX1 = new QValueAxis();
    // axisX1->setRange(0, 10000); // 设置 X 轴的范围
    // QValueAxis *axisY1 = new QValueAxis();
    // axisY1->setRange(-RANGE_VOLTAGE, RANGE_VOLTAGE); // 设置 Y 轴的范围
    // QValueAxis *axisX2 = new QValueAxis();
    // axisX2->setRange(0, 10000); // 设置 X 轴的范围
    // QValueAxis *axisY2 = new QValueAxis();
    // axisY2->setRange(-RANGE_VOLTAGE, RANGE_VOLTAGE); // 设置 Y 轴的范围

    // oriChart->addSeries(oriSeries);
    // oriChart->addAxis(axisX1, Qt::AlignBottom);
    // oriChart->addAxis(axisY1, Qt::AlignLeft);
    // oriSeries->attachAxis(axisX1);
    // oriSeries->attachAxis(axisY1);
    // oriChart->setTitle("Origin Data");
    // oriChart->setAnimationOptions(QChart::SeriesAnimations);
    // oriChartView->setRenderHint(QPainter::Antialiasing);
    // vlayout->addWidget(oriChartView);

    // dwtChart->addSeries(dwtSeries);
    // dwtChart->addAxis(axisX2, Qt::AlignBottom);
    // dwtChart->addAxis(axisY2, Qt::AlignLeft);
    // dwtSeries->attachAxis(axisX2);
    // dwtSeries->attachAxis(axisY2);
    // dwtChart->setTitle("Dwt Output");
    // dwtChart->setAnimationOptions(QChart::SeriesAnimations);
    // dwtChartView->setRenderHint(QPainter::Antialiasing);
    // vlayout->addWidget(dwtChartView);

    customplot->addGraph();
    customplot->setMinimumSize(1200, 300);
    customplot->xAxis->setRange(0, 10000);
    customplot->yAxis->setRange(-RANGE_VOLTAGE, RANGE_VOLTAGE);
    vlayout->addWidget(customplot);

    customplot2->addGraph();
    customplot2->setMinimumSize(1200, 300);
    customplot2->xAxis->setRange(0, 10000);
    customplot2->yAxis->setRange(-RANGE_VOLTAGE, RANGE_VOLTAGE);
    vlayout->addWidget(customplot2);

    wid->setLayout(vlayout);

    // 移动数据采集器到子线程
    dataCollector->moveToThread(collectThread);

    // 连接信号和槽
    connect(this, &MainWindow::startContinuData, dataCollector, &DataCollector::startCollecting);
    connect(this, &MainWindow::startSingleData, dataCollector, &DataCollector::singleData);
    connect(dataCollector, &DataCollector::oriDataPoint, this, &MainWindow::updateOriData);
    connect(dataCollector, &DataCollector::dwtDataPoint, this, &MainWindow::updateDwtData);
    connect(this, &MainWindow::requestStop, dataCollector, &DataCollector::stopCollecting);
    qDebug()<<"Main ID:"<<QThread::currentThreadId();
    collectThread->start();
}

// void MainWindow::setData(double oriData[10000], coder::array<double, 1U> &result)
// {
//     // update origin data
//     oriSeries->clear();
//     int count = oriSeries->points().size();
//     for(int i=0;i<10000;i++){
//         oriSeries->append(i, oriData[i]);
//         // count++;
//         // if(count>10000){
//         //     oriSeries->remove(0);
//         //     count--;
//         // }
//         QApplication::processEvents();
//     }

//     // update dwt result
//     dwtSeries->clear();
//     count = dwtSeries->points().size();
//     for(int i=0;i<10000;i++){
//         dwtSeries->append(i, result[i]);
//         // count++;
//         // if(count>10000){
//         //     dwtSeries->remove(0);
//         //     count--;
//         // }
//         QApplication::processEvents();
//     }
// }

void MainWindow::updateOriData(QVector<qreal> x, QVector<qreal> y){
    // oriSeries->append(x, y);
    // // printf("size of oriSeries:%d\n", oriSeries->points().size());
    // if(oriSeries->points().size() > 10000){
    //     oriSeries->remove(0);
    // }
    // if(customplot->graph(0)->dataCount() >= 10000) customplot->graph(0)->data()->remove(0);
    // customplot->graph(0)->data()->clear();
    customplot->graph(0)->setData(x, y);
    // customplot->graph(0)->addData(x, y);
    // if(customplot->graph(0)->dataCount() % 100 == 0) 
    customplot->replot();
}

void MainWindow::updateDwtData(bool judge, QVector<qreal> x, QVector<qreal> y){
    // QCPLayoutGrid *layout = customplot->plotLayout();
    // QCPTextElement *title = new QCPTextElement(customplot, "My Title");
    // layout->addElement(title);
    // dwtSeries->append(x, y);
    // if(dwtSeries->points().size() > 10000){
    //     dwtSeries->remove(0);
    // }
    // if(customplot2->graph(0)->dataCount() >= 10000) customplot2->graph(0)->data()->remove(0);
    // customplot2->graph(0)->data()->clear();
    if(judge) printf("true\n");
    else printf("false\n");
    customplot2->graph(0)->setData(x, y);
    // if(customplot2->graph(0)->dataCount()%100==0) customplot2->replot();
    customplot2->replot();
}

void MainWindow::startContinu(){
    emit startContinuData();
}

void MainWindow::startSingle(float *input, float *output){
    // QVector<qreal> Qinput, Qoutput;
    // for(int i{0};i<10000;i++){
        // if(input[i] > 1) printf("unusal data:%lf\n", input[i]);
        // Qinput.append(static_cast<qreal>(input[i]));
        // Qoutput.append(static_cast<qreal>(output[i]));
    // }
    // printf("data9999:%f", input[9999]);
    emit startSingleData(input, output);
}

// void MainWindow::clearSeries(){
//     oriSeries->clear();
//     dwtSeries->clear();
// }

MainWindow::~MainWindow()
{
    emit requestStop();
    collectThread->quit();
    collectThread->wait();
}