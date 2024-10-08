#include "lpuniversalchart_global.h"
#include "LpUniversalChartPrivate.h"
LpUniversalChart::LpUniversalChart(QWidget *parent)
    :QWidget(parent), d_ptr(new LpUniversalChartPrivate(this))
{

}

LpUniversalChart::~LpUniversalChart()
{
}

void LpUniversalChart::DataChart(const QString & curveName, double x, double y)
{
    d_ptr->emit sgUpdateData(curveName, x, y);

}
