#pragma once

#include <qobject.h>
#include <QThread>
#include <QTimer>
#include <QQueue>
#include <QDebug>
#define XAISX_RANGE 10 //设置X轴的范围
#define METER_THRESHOLD 200
class ChartThread : public QObject
{
    Q_OBJECT

public:
    ChartThread();
    ~ChartThread();

    void stopThread();
    void threadStart();
 
signals:
    void sgupdataChart(const QList<QPair<QString, QPair<double, double>>>& data);
public slots:
    void onUpdataDataChart(const QString curveName, double x, double y);

private:
    QTimer* m_timer;
    QQueue<QPair<QString, QPair<double, double>>> m_dataQueue;

};

