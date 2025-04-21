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
ed:
    void paintEvent(QPaintEvent *event) override;

private:
    QVector<QPointF> m_points;
};

#endif // GRAPHWIDGET_H
