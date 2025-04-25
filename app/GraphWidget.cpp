#include "GraphWidget.h"
#include <QVBoxLayout>
#include <QDebug>

GraphWidget::GraphWidget(QWidget *parent)
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

    int start = std::max(0, currentTimeStep - m_timeWindow);
    chart->axes(Qt::Horizontal).first()->setRange(start, currentTimeStep);
    chart->axes(Qt::Vertical).first()->setRange(2, 22);
}

void GraphWidget::resetGraph()
{
    bgDots->clear();
}

void GraphWidget::setTimeWindow(int seconds)
{
    m_timeWindow = seconds;
}
