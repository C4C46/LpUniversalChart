#include "LpUniversalChartPrivate.h"

#pragma execution_character_set("utf-8")
LpUniversalChartPrivate::LpUniversalChartPrivate(LpUniversalChart *parent)
    :QObject(parent)
{
    ui.setupUi(parent);
    init();

}

LpUniversalChartPrivate::~LpUniversalChartPrivate()
{
    // 停止线程
    if (m_thread->isRunning()) {
        m_thread->quit();
        m_thread->wait(); // 等待线程退出
    }

    // 删除动态分配的对象
    delete m_chartThread;
    delete m_thread;
    delete m_chart;
}

void LpUniversalChartPrivate::init()
{

    qRegisterMetaType<QList<QPair<QString, QPair<double, double>>>>("QList<QPair<QString, QPair<double, double>>>");
    m_chartThread = new ChartThread();
    m_thread = new QThread(this);
    m_chartThread->moveToThread(m_thread);
    m_chart = new lpUpdataChart(this);

    connect(this, &LpUniversalChartPrivate::sgUpdateData, m_chartThread, &ChartThread::onUpdataDataChart);
    connect(m_chartThread, &ChartThread::sgupdataChart, this, &LpUniversalChartPrivate::updateDataChart);
    m_thread->start();

    // 添加 QwtPlot 到 widget 的布局
    QVBoxLayout *layout = new QVBoxLayout(ui.widget);
    layout->addWidget(m_chart->plot());
    ui.widget->setLayout(layout);
}

void LpUniversalChartPrivate::updateDataChart(const QList<QPair<QString, QPair<double, double>>>& data)
{
    qDebug() << "Current Thread ID: " << QThread::currentThreadId();
    m_chart->updateChart(data);
}
