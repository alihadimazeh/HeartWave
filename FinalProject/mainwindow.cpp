#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    heartWave = new HeartWave();

    /*currentMenu = new Menu("MAIN MENU", {"ENTER SESSION MODE", "VIEW LOGS/HISTORY", "SETTINGS"}, nullptr);
    mainMenu = currentMenu;
    previousMenu = nullptr;
    //initializeMainMenu(currentMenu);

    activeQListWidget = ui->MainMenuListView;
    //activeQListWidget->addItems(currentMenu->getMenuItems());
   // activeQListWidget->setCurrentRow(0);
    ui->MainMenuLabel->setText(currentMenu->getName());*/

    powerStatus = false;
    togglePower();
    connect(ui->OnOffButton, &QPushButton::pressed, this, &MainWindow::turnOnOff);


     ui->BatteryLevel->setValue(heartWave->getBattery()->getPercentage());
     connect(ui->BatteryPercentageAdminBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::changeBatteryLevel);
     connect(ui->BatteryRechargeAdminButton, &QPushButton::pressed, this, &MainWindow::rechargeBattery);

    connect(ui->HomeButton, &QPushButton::pressed, this, &MainWindow::goToMainMenu);
    connect(ui->ReturnButton, &QPushButton::pressed, this, &MainWindow::navigateBack);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
void MainWindow::initializeMainMenu(Menu* m) {

    Menu* sessionMode = new Menu("SESSION MODE", {}, m);
    Menu* history = new Menu("HISTORY", {}, m);
    Menu* settings = new Menu("SETTINGS", {}, m);

    m->addChildMenu(sessionMode);
    m->addChildMenu(history);
    m->addChildMenu(settings);
}*/


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
    currentMenu = previousMenu;
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

void MainWindow::changeBatteryLevel(double newPercentage) {

    if ((newPercentage >= 0) && (newPercentage <= 100)) {

        if ((newPercentage == 0) && (powerStatus == true)) {
            togglePower();
            heartWave->getBattery()->setPercentage(0);
        }else{
            heartWave->getBattery()->setPercentage(newPercentage);
        }

        ui->BatteryPercentageAdminBox->setValue(newPercentage);
        ui->BatteryLevel->setValue(int(newPercentage));


        if (int(newPercentage) >= 50) {
            ui->BatteryLevel->setStyleSheet("QProgressBar { selection-background-color: rgb(78, 154, 6); background-color: rgb(0, 0, 0); }");
        }
        else if (int(newPercentage) >= 20) {
            ui->BatteryLevel->setStyleSheet("QProgressBar { selection-background-color: rgb(196, 160, 0); background-color: rgb(0, 0, 0); }");
        }
        else {
            ui->BatteryLevel->setStyleSheet("QProgressBar { selection-background-color: rgb(164, 0, 0); background-color: rgb(0, 0, 0); }");
        }
    }

}

/* function that recharges the device's battery
 */
void MainWindow::rechargeBattery(){
    heartWave->getBattery()->recharge();
    ui->BatteryLevel->setValue(heartWave->getBattery()->getPercentage());
}

