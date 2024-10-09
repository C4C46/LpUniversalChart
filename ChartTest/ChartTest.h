#pragma once

#include <QtWidgets/QWidget>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QApplication>
#include <QTimer>
#include <QDateTime>
#include "ui_ChartTest.h"
#include "lpuniversalchart_global.h"

class LpUniversalChart;

class ChartTest : public QMainWindow
{
    Q_OBJECT

public:
    ChartTest(QMainWindow *parent = nullptr);
    ~ChartTest();

private slots:
    void sendData();

private:
    Ui::ChartTestClass ui;
    LpUniversalChart *m_Chart;
    QTimer* m_timer;
    double m_xValue;
};
