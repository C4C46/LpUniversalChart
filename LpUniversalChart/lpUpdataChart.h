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
    QColor getColorForCurve(const QString & curveName);
    void installEventFilters();
    void resetCurvesOpacity();
    QwtPlot * plot() const;

protected:
    bool eventFilter(QObject * watched, QEvent * event) override;



private:
    QwtPlot *m_plot;
    QMap<QString, QVector<QPointF>> m_dataPoints; // 存储数据点
    QMap<QString, QwtPlotCurve*> m_curves; // 存储曲线的映射
    QPoint m_dragStartPosition; // 用于跟踪拖动开始时的鼠标位置
    double m_xMinCurrent, m_xMaxCurrent; // 用于跟踪当前图表的X轴范围
    bool m_isDragging = false; // 标记是否正在拖动
    bool m_isViewingHistory = false;
    double m_lastResetX = 0; // 用于记录上次重置的x值
    double m_maxReceivedX = 0; //存储接收到的最大X值
};

