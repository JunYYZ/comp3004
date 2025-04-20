#include "GraphWidget.h"
#include <QPainter>
#include <QtMath>

GraphWidget::GraphWidget(QWidget *parent)
  : QWidget(parent)
{}

void GraphWidget::setData(const QVector<QPointF> &points)
{
    m_points = points;
    update(); // schedule repaint
}

void GraphWidget::paintEvent(QPaintEvent * /*event*/)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    // margins
    const int M = 30;
    QRectF plotArea = rect().adjusted(M, M, -M, -M);

    // draw axes
    p.drawLine(plotArea.bottomLeft(), plotArea.topLeft());
    p.drawLine(plotArea.bottomLeft(), plotArea.bottomRight());

    if (m_points.isEmpty())
        return;

    // find data bounds
    auto [minX, maxX] = std::minmax_element(m_points.begin(), m_points.end(),
        [](auto &a, auto &b){ return a.x() < b.x(); });
    auto [minY, maxY] = std::minmax_element(m_points.begin(), m_points.end(),
        [](auto &a, auto &b){ return a.y() < b.y(); });

    qreal x0 = minX->x(), x1 = maxX->x();
    qreal y0 = minY->y(), y1 = maxY->y();
    if (qFuzzyCompare(x0, x1)) x1 = x0 + 1;
    if (qFuzzyCompare(y0, y1)) y1 = y0 + 1;

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
