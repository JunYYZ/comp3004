#include "GraphPage.h"
#include "ui_GraphPage.h"

GraphPage::GraphPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GraphPage)
{
    ui->setupUi(this);
}

GraphPage::~GraphPage()
{
    delete ui;
}

void GraphPage::addBGPoint(int timeStep, double bg) {
    ui->graphWidget->addBGPoint(timeStep, bg);
}

