#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //create instance of device
    heartWave = new HeartWave();

    //initialize menu structure
    currentMenu = new Menu("MAIN MENU", {"Enter Session Mode", "View Logs/History", "Settings"}, nullptr);
    mainMenu = currentMenu;
    previousMenu = nullptr;
    initializeMainMenu(currentMenu);

    //Set active widget to main menu
    activeQListWidget = ui->MainMenuListView;
    activeQListWidget->addItems(currentMenu->getMenuItems());
    activeQListWidget->setCurrentRow(0);
    ui->MainMenuLabel->setText(currentMenu->getName());

    //set power status and toggle power
    powerStatus = false;
    togglePower();
    connect(ui->OnOffButton, &QPushButton::pressed, this, &MainWindow::turnOnOff);

    //battery ui interface
    ui->BatteryLevel->setValue(heartWave->getBattery()->getPercentage());
    ui->BatteryPercentageAdminBox->setValue(heartWave->getBattery()->getPercentage());
    connect(ui->BatteryPercentageAdminBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::changeBatteryLevel);
    connect(ui->BatteryRechargeAdminButton, &QPushButton::pressed, this, &MainWindow::rechargeBattery);

    //device buttons ui interface
    connect(ui->HomeButton, &QPushButton::pressed, this, &MainWindow::goToMainMenu);
    connect(ui->ReturnButton, &QPushButton::pressed, this, &MainWindow::goBack);
    connect(ui->UpButton, &QPushButton::pressed, this, &MainWindow::goUp);
    connect(ui->DownButton, &QPushButton::pressed, this, &MainWindow::goDown);

    //block signals to right and left button (never used)
    ui->RightButton->blockSignals(true);
    ui->LeftButton->blockSignals(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initializeMainMenu(Menu* m) {

    Menu* sessionMode = new Menu("Session Mode", {}, m);
    Menu* history = new Menu("History", {}, m);
    Menu* settings = new Menu("Settings", {}, m);

    m->addChildMenu(sessionMode);
    m->addChildMenu(history);
    m->addChildMenu(settings);
}


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

void MainWindow::goBack(void) {
   currentMenu = previousMenu;
}

void MainWindow::goUp(void) {

    int nextIndex = activeQListWidget->currentRow() - 1;

    if (nextIndex < 0) {
        nextIndex = activeQListWidget->count() - 1; //wrap around?
    }

    activeQListWidget->setCurrentRow(nextIndex);

}

void MainWindow::goDown(void) {

}

/* function that changes powerStatus to the opposite of what it is and calls togglePower
 */
void MainWindow::turnOnOff(void) {
    //power on (powerStatus = true) -> turn off (powerStatus = false)
    if(heartWave->getBattery()->getPercentage() > 0.0) {
        powerStatus = !powerStatus;
        togglePower();
    }
}

/* function that simulates turning the device on/off by toggling widget visibility
/  based on the power status.
*/
void MainWindow::togglePower(void) {

    //set visibility of widgets
    activeQListWidget->setVisible(powerStatus);
    ui->PowerOffView->setVisible(!powerStatus); //always set opposite to power status
    //ui->MainMenuListView->setVisible(powerStatus);
    ui->MainMenuLabel->setVisible(powerStatus);
    ui->Statusbar->setVisible(powerStatus);
    ui->HistoryView->setVisible(powerStatus);
    ui->SessionView->setVisible(powerStatus);
    ui->SettingsView->setVisible(powerStatus);
    ui->SessionSummaryView->setVisible(powerStatus);


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
    //ui->BatteryRechargeAdminButton->setEnabled(powerStatus);
    ui->SensorAttachedAdminBox->setEnabled(powerStatus);
}


void MainWindow::changeBatteryLevel(double newPercentage) {

    if ((newPercentage >= 0.0) && (newPercentage <= 100.0)) {

        if ((newPercentage == 0.0) && (powerStatus == true)) {
            turnOnOff();
            heartWave->getBattery()->setPercentage(0.0);
        }else{
            heartWave->getBattery()->setPercentage(newPercentage);
        }

        ui->BatteryPercentageAdminBox->setValue(newPercentage);
        ui->BatteryLevel->setValue(int(newPercentage));


        if (int(newPercentage) >= 50) {
            ui->BatteryLevel->setStyleSheet("QProgressBar { selection-background-color: rgb(78, 154, 6); background-color: rgb(136, 138, 133); color: rgb(255, 255, 255); }");
        }
        else if (int(newPercentage) >= 20) {
            ui->BatteryLevel->setStyleSheet("QProgressBar { selection-background-color: rgb(196, 160, 0); background-color: rgb(136, 138, 133); color: rgb(255, 255, 255); }");
        }
        else {
            ui->BatteryLevel->setStyleSheet("QProgressBar { selection-background-color: rgb(164, 0, 0); background-color: rgb(136, 138, 133); color: rgb(255, 255, 255); }");
        }
    }

}

/* function that recharges the device's battery
 */
void MainWindow::rechargeBattery(){
    heartWave->getBattery()->recharge();
    ui->BatteryLevel->setValue(heartWave->getBattery()->getPercentage());
    ui->BatteryPercentageAdminBox->setValue(heartWave->getBattery()->getPercentage());
}

