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
    initializeMainMenu(currentMenu);

    //Set active widget to main menu
    activeQListWidget = ui->MainMenuListView;
    activeQListWidget->addItems(currentMenu->getMenuItems());
    activeQListWidget->setCurrentRow(0);
    ui->MainMenuLabel->setText(currentMenu->getName());

    //activeWidget = activeQListWidget;

    //set power status and toggle power
    powerStatus = false;
    togglePower();
    connect(ui->OnOffButton, &QPushButton::pressed, this, &MainWindow::turnOnOff);

    //battery ui interface
    ui->BatteryLevel->setValue(heartWave->getBattery()->getPercentage());
    ui->BatteryPercentageAdminBox->setValue(heartWave->getBattery()->getPercentage());
    ui->BatteryWarning->setVisible(false);
    connect(ui->BatteryPercentageAdminBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::changeBatteryLevel);
    connect(ui->BatteryRechargeAdminButton, &QPushButton::pressed, this, &MainWindow::rechargeBattery);

    //device buttons ui interface
    connect(ui->HomeButton, &QPushButton::pressed, this, &MainWindow::goToMainMenu);
    connect(ui->ReturnButton, &QPushButton::pressed, this, &MainWindow::goBack);
    connect(ui->UpButton, &QPushButton::pressed, this, &MainWindow::goUp);
    connect(ui->DownButton, &QPushButton::pressed, this, &MainWindow::goDown);
    connect(ui->SelectorButton, &QPushButton::pressed, this, &MainWindow::selectMenuOption);

    //settings
    ui->BreathPacerSetting->setValue(heartWave->getBP());
    connect(ui->BreathPacerSetting, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::changeBPSetting);
    connect(ui->ResetButton, &QPushButton::pressed, this, &MainWindow::resetSettings);

    //admin tab interface
    ui->SensorAttachedAdminBox->setCurrentIndex(1);
    updateSensorConnectedLabel(ui->SensorAttachedAdminBox->currentIndex());
    connect(ui->SensorAttachedAdminBox, QOverload<int>::of(&QComboBox::currentIndexChanged),this, &MainWindow::updateSensorConnectedLabel);

    //block signals to right and left button (never used)
    ui->RightButton->blockSignals(true);
    ui->LeftButton->blockSignals(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateSensorConnectedLabel(int index)
{
    if (index == 1) { // "False" option selected
        ui->SensorConectedLabel->setText("Sensor Disconnected");
        ui->SensorConectedLabel->setStyleSheet("background-color: red");
        ui->SensorWarning->setVisible(true);
    } else { // "True" option selected
        ui->SensorConectedLabel->setText("Sensor Connected");
        ui->SensorConectedLabel->setStyleSheet("background-color: rgb(27, 212, 0)");
        ui->SensorWarning->setVisible(false);
    }
}


void MainWindow::initializeMainMenu(Menu* m) {

    Menu* sessionMode = new Menu("SESSION MODE", {}, m);
    Menu* history = new Menu("HISTORY", {}, m);
    Menu* settings = new Menu("SETTINGS", {}, m);

    m->addChildMenu(sessionMode);
    m->addChildMenu(history);
    m->addChildMenu(settings);

}


/* function that navigates back to the main menu
 */
void MainWindow::goToMainMenu(void) {
    currentMenu = mainMenu;
    activeWidget = ui->MainMenuListView;
    MainWindow::updateView(mainMenu->getName(), mainMenu->getMenuItems());

    ui->HistoryView->setVisible(false);
    ui->SessionView->setVisible(false);
    ui->PowerOffView->setVisible(false);
    ui->SettingsView->setVisible(false);
    ui->SessionSummaryView->setVisible(false);
}

void MainWindow::goBack(void) {

   if (currentMenu->getName() == "MAIN MENU") {
       activeQListWidget->setCurrentRow(0);
   }
   else {
       currentMenu = currentMenu->getParent();
       updateView(currentMenu->getName(), currentMenu->getMenuItems());
   }

   ui->HistoryView->setVisible(false);
   ui->SessionView->setVisible(false);
   ui->PowerOffView->setVisible(false);
   ui->SettingsView->setVisible(false);
   ui->SessionSummaryView->setVisible(false);
}

/* Function that navigates up the menu
 */
void MainWindow::goUp(void) {
    //if(activeWidget != activeQListWidget) { return; }

    int nextIndex = activeQListWidget->currentRow() - 1;

    if (nextIndex < 0) {
        nextIndex = activeQListWidget->count() - 1; //wrap around
    }

    activeQListWidget->setCurrentRow(nextIndex);
}

/* Function that naviagtes down the menu
 */
void MainWindow::goDown(void) {
    //if(activeWidget != activeQListWidget) { return; }

    int previousIndex = activeQListWidget->currentRow() + 1;

    if (previousIndex >= activeQListWidget->count()) {
        previousIndex = 0; //wrap around
    }

    activeQListWidget->setCurrentRow(previousIndex);
}

/* Function that selects a a menu option
 */
void MainWindow::selectMenuOption(void) {

    int index = activeQListWidget->currentRow();
    //if (index < 0) return;

    // --------- Prevent crashes - ie. when selector button has no effect

    //Prevent crash when selector button is pressed in settings screen
    if(currentMenu->getName() == "SETTINGS") { return ; }

    //Prevent crash when selector button is pressed in session summary view
    if(currentMenu->getName() == "SESSION SUMMARY") { return; }

    // ------------------------------------------------------------------

    //If the menu is a parent and clicking on it should display more menus.
    if (currentMenu->getMenuItems().length() > 0) {
        if(currentMenu->getName() == "MAIN MENU") {
            currentMenu = currentMenu->get(index);

            if(index == 0) { activeWidget = ui->SessionView; }
            else if(index == 1) { activeWidget = ui->HistoryView; }
            else if(index == 2) { activeWidget = ui->SettingsView; }

            MainWindow::updateView(currentMenu->getName(), currentMenu->getMenuItems());
        }else if(currentMenu->getName() == "HISTORY") {
            currentMenu = currentMenu->get(index);

            MainWindow::updateView(currentMenu->getName(), currentMenu->getMenuItems());
        }
    }
    else if (currentMenu->getMenuItems().length() == 0) {
        if(currentMenu->getName() == "SESSION MODE") {
            if(ui->SensorAttachedAdminBox->currentIndex() == 0) {
                if(heartWave->startSession()) { //would be nice if it returns a bool
                    return;
                }else{
                    ui->SensorWarning->setVisible(true);
                    return;
                }
            }else{
                ui->SensorWarning->setVisible(true);
                return;
            }
        }
    }

}

/* Function that updaates the device's view
 */
void MainWindow::updateView(const QString selectedItem, const QStringList menuItems) {

    activeQListWidget->clear();
    activeQListWidget->addItems(menuItems);
    activeQListWidget->setCurrentRow(0);

    ui->MainMenuLabel->setText(selectedItem);
    activeWidget->setVisible(true);
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
    //if(active)
    activeQListWidget->setVisible(powerStatus);
    ui->PowerOffView->setVisible(!powerStatus); //always set opposite to power status
    //ui->MainMenuListView->setVisible(powerStatus);
    ui->MainMenuLabel->setVisible(powerStatus);
    ui->Statusbar->setVisible(powerStatus);
    ui->HistoryView->setVisible(powerStatus);
    ui->SessionView->setVisible(powerStatus);
    ui->SettingsView->setVisible(powerStatus);
    ui->SessionSummaryView->setVisible(powerStatus);

    //reset menu position
    if (powerStatus) {
        MainWindow::goToMainMenu();
    }

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
            ui->BatteryWarning->setVisible(false);
        }
        else if (int(newPercentage) >= 20) {
            ui->BatteryLevel->setStyleSheet("QProgressBar { selection-background-color: rgb(196, 160, 0); background-color: rgb(136, 138, 133); color: rgb(255, 255, 255); }");
            ui->BatteryWarning->setVisible(false);
        }
        else {
            ui->BatteryLevel->setStyleSheet("QProgressBar { selection-background-color: rgb(164, 0, 0); background-color: rgb(136, 138, 133); color: rgb(255, 255, 255); }");
            ui->BatteryWarning->setVisible(true);
        }
    }

}

/* Function that recharges the device's battery
 */
void MainWindow::rechargeBattery(void){
    heartWave->getBattery()->recharge();
    ui->BatteryLevel->setValue(heartWave->getBattery()->getPercentage());
    ui->BatteryPercentageAdminBox->setValue(heartWave->getBattery()->getPercentage());
    ui->BatteryWarning->setVisible(false);
}

/* Function that changes the setting of the breath pacer
 */
void MainWindow::changeBPSetting(int newSetting) {
    heartWave->setBreathPacerSetting(newSetting);
}

/* Function that resets/reverts the device's settings to initial install conditions
 */
void MainWindow::resetSettings(void) {
    heartWave->reset();
    ui->BreathPacerSetting->setValue(heartWave->getBP());
}

/*
void MainWindow::startSession() {
    //create new session
    Session* session = new Session();

    //calculate HRV


    //calculate coherence


    //update led light
    //heartWave->updateLEDColor();
    //ui->CoherenceLED->setStyleSheet("background-color: red");


    //update breath pacer


    //calculate percentage of time in different coherence levels
    //calculate average coherence
    //calculate acheivement score


}*/
