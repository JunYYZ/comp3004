#include "GraphPage.h"
#include "ui_GraphPage.h"

GraphPage::GraphPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GraphPage)
{
    ui->setupUi(this);
    connect(ui->btnBack,  &QPushButton::clicked,
            this, &GraphPage::on_btnBack_clicked);
}

GraphPage::~GraphPage()
{
    delete ui;
}

void GraphPage::addBGPoint(int timeStep, double bg) {
    ui->graphWidget->addBGPoint(timeStep, bg);
}

void GraphPage::on_btnBack_clicked()
{
    emit backRequested();
}
