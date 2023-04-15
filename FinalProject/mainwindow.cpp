#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    Battery* battery = new Battery();
    heartWave = new HeartWave();
    ui->BatteryLevel->setValue(battery->getPercentage());

    connect(ui->BatteryRechargeAdminButton, SIGNAL(pressed()), this, SLOT(rechargeBattery()));

    //set up a session

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


