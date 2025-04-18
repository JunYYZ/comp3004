#ifndef GRAPHPAGE_H
#define GRAPHPAGE_H

#include <QWidget>

namespace Ui {
class GraphPage;
}

class GraphPage : public QWidget
{
    Q_OBJECT

public:
    explicit GraphPage(QWidget *parent = nullptr);
    ~GraphPage();

private:
    Ui::GraphPage *ui;
};

#endif // GRAPHPAGE_H
