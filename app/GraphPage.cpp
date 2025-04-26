#include "GraphPage.h"
#include "ui_GraphPage.h"
#include "QtDebug"

GraphPage::GraphPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GraphPage),
    m_timeLimit(0),
    m_elapsedTime(0)
{
    ui->setupUi(this);

    connect(ui->btnBack, &QPushButton::clicked, this, &GraphPage::on_btnBack_clicked);
    connect(ui->comboRange, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &GraphPage::onComboRangeChanged);

}

GraphPage::~GraphPage()
{
    delete ui;
}

void GraphPage::addBGPoint(int timeStep, double bg)
{
    if (m_elapsedTime < m_timeLimit) {
        ui->graphWidget->addBGPoint(timeStep, bg);
        m_elapsedTime++;
    }
    else {
        qDebug() << "Time limit reached, stopping graph updates.";
    }
}


void GraphPage::on_btnBack_clicked()
{
    emit backRequested();
}

void GraphPage::onComboRangeChanged(int index)
{
    m_elapsedTime = 0;

    if (index == 0) {
        m_timeLimit = 12;
    } else if (index == 1) {
        m_timeLimit = 36;
    } else if (index == 2) {
        m_timeLimit = 72;
    }

    ui->graphWidget->setTimeWindow(m_timeLimit);
    ui->graphWidget->resetGraph();

    qDebug() << "Graph reset for range:" << m_timeLimit << "seconds.";
}
