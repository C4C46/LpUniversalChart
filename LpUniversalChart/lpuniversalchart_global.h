#pragma once

#include <QtCore/qglobal.h>
#include <QWidget>

#ifndef BUILD_STATIC
# if defined(LPUNIVERSALCHART_LIB)
#  define LPUNIVERSALCHART_EXPORT Q_DECL_EXPORT
# else
#  define LPUNIVERSALCHART_EXPORT Q_DECL_IMPORT
# endif
#else
# define LPUNIVERSALCHART_EXPORT
#endif


class LpUniversalChartPrivate;

class LPUNIVERSALCHART_EXPORT LpUniversalChart : public QWidget
{
    Q_OBJECT
public:
    LpUniversalChart(QWidget *parent = nullptr);
    ~LpUniversalChart();

    void DataChart(const QString &curveName, double x, double y);//名称和对应坐标

private:
    QSharedPointer<LpUniversalChartPrivate> d_ptr;
};

