// HistoryLogPage.cpp

#include "HistoryLogPage.h"
#include "ui_HistoryLogPage.h"
#include "Pump.h"
#include "HistoryLog.h"
#include <QTableWidgetItem>
#include <QDateTime>
#include <QPushButton>

// ——————————————————————————
// ** 1) Default ctor: **
// delegate to the Pump‑taking ctor with a nullptr pump
HistoryLogPage::HistoryLogPage(QWidget* parent)
  : HistoryLogPage(nullptr, parent)
{}

// ——————————————————————————
// ** 2) Your existing “real” ctor: **
HistoryLogPage::HistoryLogPage(Pump* pump, QWidget* parent)
  : QWidget(parent)
  , ui(new Ui::HistoryLogPage)
  , m_pump(pump)
{
    ui->setupUi(this);

    // two columns: Time | Event
    ui->listHistory->setColumnCount(2);
    ui->listHistory->setHorizontalHeaderLabels({ "Time", "Event" });

    // only load if we actually have a pump pointer
    if (m_pump) {
      for (auto& e : m_pump->history()) {
        int r = ui->listHistory->rowCount();
        ui->listHistory->insertRow(r);
        ui->listHistory->setItem(
            r, 0,
            new QTableWidgetItem(e.timestamp().toString("hh:mm:ss")));
        ui->listHistory->setItem(
            r, 1,
            new QTableWidgetItem(e.description()));
      }
      connect(m_pump,
              &Pump::pumpLog,
              this,
              &HistoryLogPage::addEntry);
    }

    connect(ui->btnClear, &QPushButton::clicked,
            this, &HistoryLogPage::on_btnClear_clicked);
    connect(ui->btnBack,  &QPushButton::clicked,
            this, &HistoryLogPage::on_btnBack_clicked);
}

HistoryLogPage::~HistoryLogPage()
{
    delete ui;
}

void HistoryLogPage::addEntry(const QString& msg)
{
    int r = ui->listHistory->rowCount();
    ui->listHistory->insertRow(r);
    ui->listHistory->setItem(
        r, 0,
        new QTableWidgetItem(
            QDateTime::currentDateTime().toString("hh:mm:ss")));
    ui->listHistory->setItem(
        r, 1,
        new QTableWidgetItem(msg));
}

void HistoryLogPage::on_btnClear_clicked()
{
    ui->listHistory->setRowCount(0);
    // if you want to wipe the pump’s own history too:
    // if (m_pump) m_pump->clearHistory();
}

void HistoryLogPage::on_btnBack_clicked()
{
    emit backRequested();
}
