#include "ChartThread.h"

ChartThread::ChartThread()
{
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &ChartThread::threadStart);
    m_timer->start(100); // 每隔1秒触发一次
}

ChartThread::~ChartThread()
{
    if (m_timer->isActive()) {
        m_timer->stop();
    }

}

void ChartThread::stopThread()
{
    if (m_timer->isActive()) {
        m_timer->stop();
    }
}

void ChartThread::threadStart()
{
    qDebug() << "Current Thread ID: " << QThread::currentThreadId();
    if (!m_dataQueue.isEmpty()) {
        QList<QPair<QString, QPair<double, double>>> dataList;
        while (!m_dataQueue.isEmpty()) {
            dataList.append(m_dataQueue.dequeue());
        }
        emit sgupdataChart(dataList);
    }
}

void ChartThread::onUpdataDataChart(const QString curveName, double x, double y)
{
    m_dataQueue.enqueue(qMakePair(curveName, qMakePair(x, y)));
}
