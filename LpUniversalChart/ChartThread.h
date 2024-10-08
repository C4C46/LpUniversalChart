#pragma once

#include <qobject.h>
#include <QThread>
class ChartThread : public QObject
{
    Q_OBJECT

public:
    ChartThread();
    ~ChartThread();

    void stopThread();
    void threadStart();
 
signals:
    void sgupdataChart();
public slots:
    void onUpdataDataChart(const QString curveName, double x, double y);

};

