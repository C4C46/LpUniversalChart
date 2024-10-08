#pragma once

#include <QtWidgets/QWidget>
#include <QHBoxLayout>
#include "ui_ChartTest.h"
#include "lpuniversalchart_global.h"

class LpUniversalChart;

class ChartTest : public QWidget
{
    Q_OBJECT

public:
    ChartTest(QWidget *parent = nullptr);
    ~ChartTest();

private:
    Ui::ChartTestClass ui;
    LpUniversalChart *m_Chart;
};
