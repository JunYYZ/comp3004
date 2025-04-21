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
y1 = y0 + 1;

    // map data → screen
    QPolygonF poly;
    for (auto &pt : m_points) {
        qreal x = plotArea.left()
                + (pt.x() - x0) / (x1 - x0) * plotArea.width();
        qreal y = plotArea.bottom()
                - (pt.y() - y0) / (y1 - y0) * plotArea.height();
        poly.append(QPointF(x, y));
    }

    // draw the line
    p.setPen(QPen(Qt::blue, 2));
    p.drawPolyline(poly);

    // optional: draw min/max labels
    p.setPen(Qt::black);
    p.drawText(plotArea.left() - 25, plotArea.bottom(), QString::number(y0));
    p.drawText(plotArea.left() - 25, plotArea.top()+5, QString::number(y1));
    p.drawText(plotArea.left(), plotArea.bottom()+20, QString::number(x0));
    p.drawText(plotArea.right()-20, plotArea.bottom()+20, QString::number(x1));
}
