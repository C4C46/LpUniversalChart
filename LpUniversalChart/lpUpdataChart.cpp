#include "lpUpdataChart.h"
#pragma execution_character_set("utf-8")
lpUpdataChart::lpUpdataChart(QObject *parent)
    :QObject(parent)
{
    m_plot = new QwtPlot();
    m_plot->setCanvasBackground(Qt::white);
    m_plot->insertLegend(new QwtLegend(), QwtPlot::TopLegend);
    m_plot->setAxisTitle(QwtPlot::xBottom, "");
    m_plot->setAxisTitle(QwtPlot::yLeft, "");
    // 设置X轴和Y轴的初始范围
    m_plot->setAxisScale(QwtPlot::xBottom, 0, XAISX_RANGE); // 设置X轴的范围为0-5
    //m_plot->setCanvasBackground(QColor(14, 22, 55));

}

lpUpdataChart::~lpUpdataChart()
{
    delete m_plot; // 确保释放 m_plot
}

void lpUpdataChart::updateChart(const QList<QPair<QString, QPair<double, double>>>& data)
{
    qDebug() << "Current Thread ID: " << QThread::currentThreadId();
    //for (const auto& entry : data) {
    //    const QString& curveName = entry.first;
    //    double x = entry.second.first;
    //    double y = entry.second.second;

    //    if (!m_curves.contains(curveName)) {
    //        QwtPlotCurve* curve = new QwtPlotCurve(curveName);
    //        curve->attach(m_plot);
    //        m_curves[curveName] = curve;
    //    }

    //    QVector<QPointF>& points = m_dataPoints[curveName];
    //    points.append(QPointF(x, y));
    //    m_curves[curveName]->setSamples(points);
    //}
    //m_plot->replot();

    double maxX = 0; // 用于存储最大X值

    for (const auto& entry : data) {
        const QString& curveName = entry.first;
        double x = entry.second.first;
        double y = entry.second.second;

        if (!m_curves.contains(curveName)) {
            QwtPlotCurve* curve = new QwtPlotCurve(curveName);
            curve->attach(m_plot);
            m_curves[curveName] = curve;


            // 启用抗锯齿
            curve->setRenderHint(QwtPlotItem::RenderAntialiased, true);

            // 设置曲线宽度
            QPen pen = curve->pen();
            pen.setWidth(2); // 设置曲线宽度为2
            curve->setPen(pen);
        }

        QVector<QPointF>& points = m_dataPoints[curveName];
        points.append(QPointF(x, y));
        m_curves[curveName]->setSamples(points);

        if (x > maxX) {
            maxX = x; // 更新最大X值
        }
    }

    // 更新X轴范围以显示最新数据点
    m_plot->setAxisScale(QwtPlot::xBottom, maxX - XAISX_RANGE, maxX);

    m_plot->replot();
}

QwtPlot* lpUpdataChart::plot() const
{
    return m_plot;
}