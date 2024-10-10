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
    installEventFilters();
}

lpUpdataChart::~lpUpdataChart()
{
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

        if (x > m_maxReceivedX) {
            m_maxReceivedX = x;
        }
        if (!m_curves.contains(curveName)) {
            QwtPlotCurve* curve = new QwtPlotCurve(curveName);
            curve->attach(m_plot);
            m_curves[curveName] = curve;


            // 启用抗锯齿
            curve->setRenderHint(QwtPlotItem::RenderAntialiased, true);

            // 设置曲线宽度
            QColor color = getColorForCurve(curveName);
            QPen pen(color);
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

    // 仅当不在查看历史数据时更新X轴范围
    if (!m_isViewingHistory) {
        m_plot->setAxisScale(QwtPlot::xBottom, maxX - XAISX_RANGE, maxX);
    }


    m_plot->replot();
}

QColor lpUpdataChart::getColorForCurve(const QString& curveName) {
    static QMap<QString, QColor> colorMap;
    if (!colorMap.contains(curveName)) {
        // Generate a new color for the curve
        QColor newColor = QColor::fromHsv(qrand() % 360, 255, 255); // Random color
        colorMap[curveName] = newColor;
    }
    return colorMap[curveName];
}


void lpUpdataChart::installEventFilters() {
    m_plot->canvas()->installEventFilter(this);
}


bool lpUpdataChart::eventFilter(QObject *watched, QEvent *event) {
    if (watched == m_plot->canvas()) {
        switch (event->type()) {
        case QEvent::MouseButtonPress: {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            if (mouseEvent->button() == Qt::LeftButton) {
                m_dragStartPosition = mouseEvent->pos();
                m_xMinCurrent = m_plot->axisScaleDiv(QwtPlot::xBottom).lowerBound();
                m_xMaxCurrent = m_plot->axisScaleDiv(QwtPlot::xBottom).upperBound();
                m_isDragging = true;
                m_plot->replot(); // 重绘图表以应用更改
                return true;
            }
            else if (mouseEvent->button() == Qt::RightButton) {
                // 当用户右键点击时，退出历史查看模式
                m_isViewingHistory = false;
                resetCurvesOpacity();
                double xMax = m_maxReceivedX;
                if (xMax <= 0)
                {
                    xMax = 5;
                }
                double xMin = xMax - XAISX_RANGE; // 假设显示范围是50
                if (xMin < 0) xMin = 0; // 确保xMin不小于0
                m_plot->setAxisScale(QwtPlot::xBottom, xMin, xMax);
                m_plot->replot(); // 重绘图表以应用更改
                return true;

            }
            break;
        }
        case QEvent::MouseMove: {
            if (m_isDragging) {
                QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
                int dx = mouseEvent->pos().x() - m_dragStartPosition.x();
                m_isViewingHistory = true;
                double shift = (m_xMaxCurrent - m_xMinCurrent) * dx / m_plot->canvas()->width();
                double newMin = m_xMinCurrent - shift;
                double newMax = m_xMaxCurrent - shift;

                // 确保新的x轴范围不小于0
                if (newMin < m_lastResetX) {
                    newMin = m_lastResetX;
                    newMax = newMin + (m_xMaxCurrent - m_xMinCurrent); // 保持区间长度不变
                }

                m_plot->setAxisScale(QwtPlot::xBottom, newMin, newMax);
                m_plot->replot();
                return true;
            }
            break;
        }
        case QEvent::MouseButtonRelease: {
            if (m_isDragging) {
                m_isDragging = false;
                return true;
            }
            break;
        }
        default:
            break;
        }
    }
    return QObject::eventFilter(watched, event);
}



void lpUpdataChart::resetCurvesOpacity() {
    for (auto &curve : m_curves) {
        QColor color = curve->pen().color();
        color.setAlpha(255); // 设置为完全不透明
        curve->setPen(QPen(color, 2));
        curve->setRenderHint(QwtPlotItem::RenderAntialiased);
    }
}


QwtPlot* lpUpdataChart::plot() const
{
    return m_plot;
}