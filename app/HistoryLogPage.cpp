// HistoryLogPage.cpp

#include "HistoryLogPage.h"
#include "ui_HistoryLogPage.h"
#include "Pump.h"
#include "HistoryLog.h"

#include <QTableWidgetItem>
#include <QPushButton>

HistoryLogPage::HistoryLogPage(QWidget* parent)
  : HistoryLogPage(nullptr, parent)
{}

HistoryLogPage::HistoryLogPage(Pump* pump, QWidget* parent)
  : QWidget(parent)
  , ui(new Ui::HistoryLogPage)
  , m_pump(pump)
{
    ui->setupUi(this);

    // two columns: Time | Event
    ui->listHistory->setColumnCount(2);
    ui->listHistory->setHorizontalHeaderLabels({ "Time", "Event" });

    // if we have a pump, preload its history and listen for new logs
    if (m_pump) {
        for (const auto &e : m_pump->history()) {
            int r = ui->listHistory->rowCount();
            ui->listHistory->insertRow(r);
            // NOTE: these old events will be stamped at "00:00"
            ui->listHistory->setItem(r, 0,
                new QTableWidgetItem("00:00"));
            ui->listHistory->setItem(r, 1,
                new QTableWidgetItem(e.description()));
        }
        connect(m_pump,
                &Pump::pumpLog,
                this,
                &HistoryLogPage::addEntry);
    }

    // wire up Clear & Back
    connect(ui->btnClear, &QPushButton::clicked,
            this, &HistoryLogPage::on_btnClear_clicked);
    connect(ui->btnBack,  &QPushButton::clicked,
            this, &HistoryLogPage::on_btnBack_clicked);
}

HistoryLogPage::~HistoryLogPage()
{
    delete ui;
}

void HistoryLogPage::setSimulationClock(SimulationClock* clock)
{
    m_clock = clock;
}

void HistoryLogPage::addEntry(const QString& msg)
{
    int r = ui->listHistory->rowCount();
    ui->listHistory->insertRow(r);

    // compute HH:MM from simulated minutes elapsed
    int total = m_clock ? m_clock->elapsedMinutes() : 0;
    int hh = total / 60;
    int mm = total % 60;
    QString ts = QString("%1:%2")
                   .arg(hh, 2, 10, QChar('0'))
                   .arg(mm, 2, 10, QChar('0'));

    ui->listHistory->setItem(r, 0,
        new QTableWidgetItem(ts));
    ui->listHistory->setItem(r, 1,
        new QTableWidgetItem(msg));
}

void HistoryLogPage::on_btnClear_clicked()
{
    ui->listHistory->setRowCount(0);
    // optionally: m_pump->clearHistory();
}

void HistoryLogPage::on_btnBack_clicked()
{
    emit backRequested();
}
