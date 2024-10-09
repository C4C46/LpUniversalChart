#include "ChartTest.h"
#pragma execution_character_set("utf-8")
ChartTest::ChartTest(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    m_Chart = new LpUniversalChart(this);

    // 创建一个水平布局
    QHBoxLayout *layout = new QHBoxLayout(ui.widget);

    // 将 LpUniversalChart 添加到布局中
    layout->addWidget(m_Chart);

    // 设置布局到 ChartTest
    setLayout(layout);

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &ChartTest::sendData);
    m_timer->start(100);
}

ChartTest::~ChartTest()
{
    delete m_Chart;
}


void ChartTest::sendData()
{
    QString curveName = "测试名称";
    double y = qrand() % 100; // 随机生成 y 值

    // 调用 LpUniversalChart 的 DataChart 方法
    m_Chart->DataChart(curveName, m_xValue, y);

    // 递增 x 值
    m_xValue += 0.1;
}