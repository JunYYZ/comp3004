#pragma once

#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QScatterSeries>

QT_CHARTS_USE_NAMESPACE

class GraphWidget : public QWidget {
    Q_OBJECT

public:
    explicit GraphWidget(QWidget* parent = nullptr);
    void addBGPoint(int timeStep, double bg);

private:
    QChart* chart;
    QChartView* chartView;
    QScatterSeries* bgDots;
    int currentTimeStep;
};
