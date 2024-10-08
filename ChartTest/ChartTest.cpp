#include "ChartTest.h"

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
}

ChartTest::~ChartTest()
{
    delete m_Chart;
}
