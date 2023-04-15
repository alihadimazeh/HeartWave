#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <iostream>

#include "Battery.h"
#include "HeartWave.h"
#include "menu.h"

#include "menu.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Menu* currentMenu;
    Menu* mainMenu;
    Menu* previousMenu;

    HeartWave *heartWave;

    bool powerStatus;

    Ui::MainWindow *ui;
    QListWidget *activeQListWidget;
    QWidget *activeWidget;

    void togglePower(void);
   void initializeMainMenu(Menu* m);

private slots:
    void goToMainMenu(void);
    void goBack(void);
    void goUp(void);
    void goDown(void);
    void selectMenuOption(void);
    void turnOnOff(void);
    void rechargeBattery(void);
    void changeBatteryLevel(double newLevel);
};
#endif // MAINWINDOW_H
