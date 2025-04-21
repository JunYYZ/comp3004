#include "GraphWidget.h"
#include <QVBoxLayout>
#include <QDebug>

GraphWidget::GraphWidget(QWidget* parent)
    : QWidget(parent), currentTimeStep(0)
{
    bgDots = new QScatterSeries();
    bgDots->setName("BG (mmol/L)");
    bgDots->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    bgDots->setMarkerSize(8.0);

    chart = new QChart();
    chart->addSeries(bgDots);
    chart->createDefaultAxes();
    chart->setTitle("BG vs Time");
    chart->axes(Qt::Vertical).first()->setTitleText("BG (mmol/L)");
    chart->axes(Qt::Horizontal).first()->setTitleText("Time");

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(chartView);
    setLayout(layout);
}

void GraphWidget::addBGPoint(int timeStep, double bg)
{
    qDebug() << "[Graph] Logging BG:" << bg << "at time:" << timeStep;
    bgDots->append(timeStep, bg);
    currentTimeStep = timeStep;

    chart->axes(Qt::Horizontal).first()->setRange(0, currentTimeStep + 1);
    chart->axes(Qt::Vertical).first()->setRange(2, 22);
}
