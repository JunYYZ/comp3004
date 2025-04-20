#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QWidget>
#include <QVector>
#include <QPointF>

/// Simple line‑plot widget: draws axes and a polyline of the supplied points.
class GraphWidget : public QWidget {
    Q_OBJECT

public:
    explicit GraphWidget(QWidget *parent = nullptr);

    /// Supply new (x=time‑seconds, y=BG‑mmol/L) points and repaint
    void setData(const QVector<QPointF> &points);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QVector<QPointF> m_points;
};

#endif // GRAPHWIDGET_H
