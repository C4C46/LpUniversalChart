#include "ChartThread.h"

ChartThread::ChartThread()
{

}

ChartThread::~ChartThread()
{

}

void ChartThread::stopThread()
{
}

void ChartThread::threadStart()
{
    emit sgupdataChart();
}

void ChartThread::onUpdataDataChart(const QString curveName, double x, double y)
{
    threadStart();
}
