#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    powerStatus = false;
    togglePower();


    connect(ui->HomeButton, &QPushButton::pressed, this, &MainWindow::goToMainMenu);
    connect(ui->ReturnButton, &QPushButton::pressed, this, &MainWindow::navigateBack);
    connect(ui->OnOffButton, &QPushButton::pressed, this, &MainWindow::turnOnOff);

    ui->setupUi(this);

    Battery* battery = new Battery();
    heartWave = new HeartWave();
    ui->BatteryLevel->setValue(battery->getPercentage());

    connect(ui->BatteryRechargeAdminButton, SIGNAL(pressed()), this, SLOT(rechargeBattery()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::rechargeBattery(){
    heartWave->getBattery()->recharge();
    ui->BatteryLevel->setValue(heartWave->getBattery()->getPercentage());
}
/*
void MainWindow::initializeMainMenu(Menu* m) {

    QStringList frequenciesList;
    QStringList programsList;

    for (Therapy* f : this->frequencies) {
        frequenciesList.append(f->getName());
    }
    for (Therapy* p : this->programs) {
        programsList.append(p->getName());
    }

    Menu* programs = new Menu("PROGRAMS", programsList, m);
    Menu* frequencies = new Menu("FREQUENCIES", frequenciesList, m);
    Menu* history = new Menu("HISTORY", {"VIEW","CLEAR"}, m);

    m->addChildMenu(programs);
    m->addChildMenu(frequencies);
    m->addChildMenu(history);

    for (Therapy* f : this->frequencies) {
        frequencies->addChildMenu(new Menu(f->getName(), {}, frequencies));
    }

    for (Therapy* p : this->programs) {
        programs->addChildMenu(new Menu(p->getName(), {}, programs));
    }

    Menu* viewHistory = new Menu("VIEW",{}, history);
    Menu* clearHistory = new Menu("CLEAR", {"YES","NO"}, history);
    history->addChildMenu(viewHistory);
    history->addChildMenu(clearHistory);
}
*/

/* function that navigates back to the main menu
 */
void MainWindow::goToMainMenu(void) {
    ui->MainMenuListView->setVisible(true);
    ui->MainMenuLabel->setVisible(true);

    ui->HistoryView->setVisible(false);
    ui->SessionView->setVisible(false);
    ui->PowerOffView->setVisible(false);
    ui->SettingsView->setVisible(false);
    ui->SessionSummaryView->setVisible(false);
}

void MainWindow::navigateBack(void) {
    masterMenu = previousMenu;
}

/* function that changes powerStatus to the opposite of what it is and calls togglePower
 */
void MainWindow::turnOnOff(void) {
    //power on (powerStatus = true) -> turn off (powerStatus = false)
    powerStatus = !powerStatus;
    togglePower();
}

/* function that simulates turning the device on/off by toggling widget visibility
/  based on the power status.
*/
void MainWindow::togglePower(void) {

    //set visibility of widgets
    ui->PowerOffView->setVisible(!powerStatus); //always set opposite to power status
    ui->MainMenuListView->setVisible(powerStatus);
    ui->MainMenuLabel->setVisible(powerStatus);
    ui->HistoryView->setVisible(powerStatus);
    ui->SessionView->setVisible(powerStatus);
    ui->SettingsView->setVisible(powerStatus);
    ui->SessionSummaryView->setVisible(powerStatus);
    ui->Statusbar->setVisible(powerStatus);

    //enable or disable buttons base on power status
    //powerStatus = true (ie. on) -> enable buttons
    //powerStatus = false (ie. off) -> disable buttons
    ui->ReturnButton->setEnabled(powerStatus);
    ui->HomeButton->setEnabled(powerStatus);
    ui->UpButton->setEnabled(powerStatus);
    ui->RightButton->setEnabled(powerStatus);
    ui->LeftButton->setEnabled(powerStatus);
    ui->DownButton->setEnabled(powerStatus);
    ui->SelectorButton->setEnabled(powerStatus);
    ui->BatteryPercentageAdminBox->setEnabled(powerStatus);
    ui->BatteryRechargeAdminButton->setEnabled(powerStatus);
    ui->SensorAttachedAdminBox->setEnabled(powerStatus);
}

