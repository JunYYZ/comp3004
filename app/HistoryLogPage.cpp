#include "HistoryLogPage.h"
#include "ui_HistoryLogPage.h"
#include "mainWindow.h"
#include "Pump.h"
#include "HistoryLog.h"

#include <QTableWidgetItem>
#include <QPushButton>
#include <QDateTime>

HistoryLogPage::HistoryLogPage(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::HistoryLogPage)
  , m_mainWindow(qobject_cast<mainWindow*>(parent))
  , m_pump(m_mainWindow ? m_mainWindow->pump() : nullptr)
{
    ui->setupUi(this);

    // two columns
    ui->listHistory->setColumnCount(2);
    ui->listHistory->setHorizontalHeaderLabels({ "Time", "Event" });

    // load existing
    for (auto& e : m_pump->history()) {
        int r = ui->listHistory->rowCount();
        ui->listHistory->insertRow(r);
        ui->listHistory->setItem(r, 0,
          new QTableWidgetItem(e.timestamp().toString("hh:mm:ss")));
        ui->listHistory->setItem(r, 1,
          new QTableWidgetItem(e.description()));
    }

    // live updates
    connect(m_pump,
            &Pump::pumpLog,
            this,
            &HistoryLogPage::addEntry);

    connect(ui->btnClear, &QPushButton::clicked, this, &HistoryLogPage::on_btnClear_clicked);
    connect(ui->btnBack,  &QPushButton::clicked, this, &HistoryLogPage::on_btnBack_clicked);
}

HistoryLogPage::~HistoryLogPage()
{
    delete ui;
}

void HistoryLogPage::addEntry(const QString& msg)
{
    int r = ui->listHistory->rowCount();
    ui->listHistory->insertRow(r);
    ui->listHistory->setItem(r, 0,
      new QTableWidgetItem(QDateTime::currentDateTime().toString("hh:mm:ss")));
    ui->listHistory->setItem(r, 1,
      new QTableWidgetItem(msg));
}

void HistoryLogPage::on_btnClear_clicked()
{
    ui->listHistory->setRowCount(0);
    // if you want to clear pump‐side history too:
    // m_pump->clearHistory();
}

void HistoryLogPage::on_btnBack_clicked()
{
    this->hide();
    m_mainWindow->show();
}
