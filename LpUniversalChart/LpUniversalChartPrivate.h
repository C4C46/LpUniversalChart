#pragma once
#include "lpuniversalchart_global.h"
#include "ui_lpuniversalchart.h"  
#include "ChartThread.h"
#include "lpUpdataChart.h"
#include <QThread>
#include <QDebug>
class LpUniversalChartPrivate : public QObject
{
    Q_OBJECT

public:
    LpUniversalChartPrivate(LpUniversalChart *parent);
    ~LpUniversalChartPrivate();

    void init();


signals:
    void sgUpdateData(const QString &curveName, double x, double y);
public slots:
    void updateDataChart(const QList<QPair<QString, QPair<double, double>>>& data);

private:
    Ui::LpUniversalChart ui;
    ChartThread *m_chartThread;
    QThread *m_thread;
    lpUpdataChart *m_chart;
};


