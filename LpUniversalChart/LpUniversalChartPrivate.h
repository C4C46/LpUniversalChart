#pragma once
#include "lpuniversalchart_global.h"
#include "ui_lpuniversalchart.h"  
#include "ChartThread.h"
#include <QThread>
class LpUniversalChartPrivate : public QObject
{
    Q_OBJECT

public:
    LpUniversalChartPrivate(LpUniversalChart *parent);
    ~LpUniversalChartPrivate();

    void init();
    void updateDataChart(const QString &curveName, double x, double y);

signals:
    void sgUpdateData(const QString &curveName, double x, double y);


private:
    Ui::LpUniversalChart ui;
    ChartThread *m_chartThread;
    QThread *m_thread;
};


