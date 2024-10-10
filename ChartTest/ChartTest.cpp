﻿#include "ChartTest.h"
#pragma execution_character_set("utf-8")
ChartTest::ChartTest(QMainWindow *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    m_Chart = new LpUniversalChart(this);

    ui.dockWidget->setWidget(m_Chart);


    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &ChartTest::sendData);
    m_timer->start(10);
}

ChartTest::~ChartTest()
{
    delete m_Chart;
}


void ChartTest::sendData()
{
    QString curveName = "测试名称";
    double y = qrand() % 100; // 随机生成 y 值
        // 递增 x 值
    m_xValue += 1;
    // 调用 LpUniversalChart 的 DataChart 方法
    m_Chart->DataChart(curveName, m_xValue, y);


}