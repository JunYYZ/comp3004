#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QScatterSeries>

QT_CHARTS_USE_NAMESPACE

class GraphWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GraphWidget(QWidget *parent = nullptr);
    void addBGPoint(int timeStep, double bg);
    void resetGraph();
    void setTimeWindow(int seconds);

private:
    QChart *chart;
    QChartView *chartView;
    QScatterSeries *bgDots;
    int currentTimeStep;
    int m_timeWindow = 12;
};

#endif // GRAPHWIDGET_H
