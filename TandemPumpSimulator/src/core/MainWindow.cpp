#include "MainWindow.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QMessageBox>

/* --------------------------------------------------------------------- */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_pump(new InsulinPump(this))
{
    buildUI();

    /* connect pump -> log window */
    connect(m_pump, &InsulinPump::pumpLog,
            this, &MainWindow::handlePumpLog);

    /* 1‑second simulation timer (1 s = 5 sim‑min) */
    m_timer = new QTimer(this);
    m_timer->setInterval(1000);
    connect(m_timer, &QTimer::timeout,
            this, &MainWindow::onTimerTick);

    refresh();
}

/* ----------------------- UI composition ------------------------------ */
void MainWindow::buildUI()
{
    auto *central = new QWidget(this);
    setCentralWidget(central);

    /* left side -------------------------------------------------------- */
    auto *left = new QVBoxLayout;

    /* (a) pump info panel */
    auto *infoBox = new QGroupBox("Pump Info");
    auto *infoLay = new QVBoxLayout(infoBox);
    m_lblBattery = new QLabel;
    m_lblInsulin = new QLabel;
    m_lblState = new QLabel;
    m_lblBG = new QLabel("BG: --");
    lblSimTime = new QLabel("Time: 00:00");
    infoLay->addWidget(m_lblBattery);
    infoLay->addWidget(m_lblInsulin);
    infoLay->addWidget(m_lblState);
    infoLay->addWidget(m_lblBG);
    infoLay->addWidget(lblSimTime);

    /* (b) run controls */
    auto *ctrlBox = new QGroupBox("Simulation Controls");
    auto *ctrlLay = new QHBoxLayout(ctrlBox);
    m_btnStart = new QPushButton("Start");
    m_btnPause = new QPushButton("Pause");
    m_btnResume = new QPushButton("Resume");
    m_btnStop = new QPushButton("Stop");
    ctrlLay->addWidget(m_btnStart);
    ctrlLay->addWidget(m_btnPause);
    ctrlLay->addWidget(m_btnResume);
    ctrlLay->addWidget(m_btnStop);

    connect(m_btnStart, &QPushButton::clicked, this, &MainWindow::onStartClicked);
    connect(m_btnPause, &QPushButton::clicked, this, &MainWindow::onPauseClicked);
    connect(m_btnResume, &QPushButton::clicked, this, &MainWindow::onResumeClicked);
    connect(m_btnStop, &QPushButton::clicked, this, &MainWindow::onStopClicked);

    /* (c) profiles */
    auto *profBox = new QGroupBox("Profiles");
    auto *profLay = new QVBoxLayout(profBox);
    m_listProfiles = new QListWidget;
    auto *btnAdd = new QPushButton("Add profile");
    auto *btnChoose = new QPushButton("Select profile");
    profLay->addWidget(m_listProfiles);
    profLay->addWidget(btnAdd);
    profLay->addWidget(btnChoose);
    connect(btnAdd, &QPushButton::clicked, this, &MainWindow::onAddProfileClicked);
    connect(btnChoose, &QPushButton::clicked, this, &MainWindow::onSelectProfileClicked);

    /* (d) manual bolus */
    auto *bolusBox = new QGroupBox("Manual Bolus");
    auto *bolusLay = new QVBoxLayout(bolusBox);
    m_editBG = new QLineEdit;
    m_editBG->setPlaceholderText("BG (mg/dL)");
    m_editCarb = new QLineEdit;
    m_editCarb->setPlaceholderText("Carbs (g)");
    auto *btnBolus = new QPushButton("Deliver bolus");
    bolusLay->addWidget(m_editBG);
    bolusLay->addWidget(m_editCarb);
    bolusLay->addWidget(btnBolus);
    connect(btnBolus, &QPushButton::clicked, this, &MainWindow::onBolusClicked);

    /* (e) console */
    auto *logBox = new QGroupBox("Console");
    auto *logLay = new QVBoxLayout(logBox);
    m_txtLog = new QPlainTextEdit;
    m_txtLog->setReadOnly(true);
    logLay->addWidget(m_txtLog);

    /* assemble left stack */
    left->addWidget(infoBox);
    left->addWidget(ctrlBox);
    left->addWidget(profBox);
    left->addWidget(bolusBox);
    left->addWidget(logBox);
    left->addStretch();

    auto *leftWidget = new QWidget;
    leftWidget->setLayout(left);

    /* right placeholder (CGM chart etc.) ------------------------------ */
    auto *right = new QVBoxLayout;
    right->addWidget(new QLabel("CGM / charts placeholder"));
    right->addStretch();
    auto *rightWidget = new QWidget;
    rightWidget->setLayout(right);

    /* overall layout --------------------------------------------------- */
    auto *root = new QHBoxLayout(central);
    root->addWidget(leftWidget, 3);
    root->addWidget(rightWidget, 2);

    setWindowTitle("Insulin Pump Simulation");
    resize(1000, 600);
}

/* ----------------------- helpers ------------------------------------- */
void MainWindow::refresh()
{
    m_lblBattery->setText(QString("Battery: %1 %").arg(m_pump->battery()));
    m_lblInsulin->setText(QString("Insulin: %1 u").arg(m_pump->insulin()));
    m_lblState->setText(QString("State: %1").arg(static_cast<int>(m_pump->state())));
}

/* ----------------------- slots --------------------------------------- */
void MainWindow::handlePumpLog(const QString &msg)
{
    m_txtLog->appendPlainText(msg);
}

void MainWindow::onTimerTick()
{
    if (!m_running)
        return;
    m_simTime += 5; // +5 sim‑min
    int simMinutes = m_simTime * 5;
    int hrs = simMinutes / 60;
    int mins = simMinutes % 60;
    lblSimTime->setText(
        QString("Time: %1:%2").arg(hrs, 2, 10, QChar('0')).arg(mins, 2, 10, QChar('0')));
    m_pump->tick(); // advance CGM + Control‑IQ etc.
    refresh();
}

/* ---- control buttons ---- */
void MainWindow::onStartClicked()
{
    m_running = true;
    m_timer->start();
    m_pump->startBasal();
    refresh();
}
void MainWindow::onPauseClicked()
{
    m_running = false;
    m_pump->pause();
    refresh();
}
void MainWindow::onResumeClicked()
{
    m_running = true;
    m_pump->resume();
    refresh();
}
void MainWindow::onStopClicked()
{
    m_running = false;
    m_timer->stop();
    m_simTime = 0;
    lblSimTime->setText("Time: 00:00");
    m_pump->stopAll();
    refresh();
}

/* profiles */
void MainWindow::onAddProfileClicked()
{
    static int id = 1;
    QString name = QString("Profile %1").arg(id++);
    m_pump->addProfile(Profile{name, /*ICR*/ 10, /*CF*/ 40, /*target*/ 110});
    m_listProfiles->addItem(name);
}

void MainWindow::onSelectProfileClicked()
{
    if (auto *item = m_listProfiles->currentItem())
        m_pump->selectProfile(item->text());
}

/* bolus */
void MainWindow::onBolusClicked()
{
    bool ok1, ok2;
    int bg = m_editBG->text().toInt(&ok1);
    int carb = m_editCarb->text().toInt(&ok2);
    if (ok1 && ok2)
        m_pump->manualBolus(bg, carb);
}

/* --------------------------------------------------------------------- */
