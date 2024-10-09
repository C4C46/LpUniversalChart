#pragma once
#include <qobject.h>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_panner.h>
#include <qwt_scale_div.h>
#include <qwt_plot_magnifier.h>
#include <qwt_text.h>
#include <qwt_legend.h>
#include <qwt_legend_label.h>
#include <qwt_plot_marker.h>
#include <QList>
#include <QPair>
#include <QMap>
#include <QVector>
#include <QPointF>
#include <QDebug>
#include "ChartThread.h"
class lpUpdataChart : public QObject
{
    Q_OBJECT

public:
    lpUpdataChart(QObject *parent);
    ~lpUpdataChart();

    void updateChart(const QList<QPair<QString, QPair<double, double>>>& data);

    QwtPlot * plot() const;

private:
    QwtPlot *m_plot;
    QMap<QString, QVector<QPointF>> m_dataPoints; // 存储数据点
    QMap<QString, QwtPlotCurve*> m_curves; // 存储曲线的映射
};

