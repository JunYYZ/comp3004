#ifndef GRAPHPAGE_H
#define GRAPHPAGE_H

#include <QWidget>
#include <GraphWidget.h>

namespace Ui {
class GraphPage;
}

class GraphPage : public QWidget
{
    Q_OBJECT

public:
    explicit GraphPage(QWidget *parent = nullptr);
    ~GraphPage();

    void logDataPoint(int time, double glucose);
    void addBGPoint(int timeStep, double bg);
signals:
    /// user tapped back
    void backRequested();

private slots:
    void on_btnBack_clicked();

private:
    Ui::GraphPage *ui;
};

#endif // GRAPHPAGE_H
