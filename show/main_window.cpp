#include "main_window.h"
#include <QString>

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
    customplot2(new QCustomPlot()),
    messageDischarge(new QLabel()),
    messageArea(new QScrollArea()),
    falsecount(0)
{
    this->setCentralWidget(wid);

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

    QFont *font = new QFont();
    font->setBold(true);
    font->setPointSize(25);
    font->setFamily("Times New Roman");
    messageArea->setWidget(messageDischarge);
    messageArea->setWidgetResizable(true);
    messageArea->setFixedHeight(100);
    messageArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    messageArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    messageDischarge->setAlignment(Qt::AlignCenter);
    messageDischarge->setFont(*font);
    messageDischarge->setStyleSheet("QLabel{Color: red;}");
    vlayout->addWidget(messageArea);

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



void MainWindow::updateOriData(QVector<qreal> x, QVector<qreal> y){
    customplot->graph(0)->setData(x, y);
    // customplot->graph(0)->addData(x, y);
    // if(customplot->graph(0)->dataCount() % 100 == 0) 
    customplot->replot();
}

void MainWindow::updateDwtData(bool judge, QVector<qreal> x, QVector<qreal> y){
    if(judge){
        falsecount++;
        messageDischarge->setText("true");
        printf("%s\n", "true");
        messageArea->setBackgroundRole(QPalette::Dark);
    }
    else{
        QString countStr = QString::number(falsecount);
        messageDischarge->setText("false total incorrect:" + countStr);
        messageArea->setBackgroundRole(QPalette::NoRole);
    }
    customplot2->graph(0)->setData(x, y);
    // if(customplot2->graph(0)->dataCount()%100==0) customplot2->replot();
    customplot2->replot();
}

void MainWindow::startContinu(){
    emit startContinuData();
}

void MainWindow::startSingle(float *input, float *output){
    emit startSingleData(input, output);
}

MainWindow::~MainWindow()
{
    emit requestStop();
    collectThread->quit();
    collectThread->wait();
}