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
