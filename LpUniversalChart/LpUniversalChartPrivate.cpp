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
}

void LpUniversalChartPrivate::init()
{
    m_chartThread = new ChartThread();
    m_thread = new QThread(this);
    m_chartThread->moveToThread(m_thread);

    connect(this, &LpUniversalChartPrivate::sgUpdateData, m_chartThread, &ChartThread::onUpdataDataChart);
}

void LpUniversalChartPrivate::updateDataChart(const QString & curveName, double x, double y)
{

}
