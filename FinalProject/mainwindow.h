#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <iostream>
#include <QVector>

#include "Battery.h"
#include "HeartWave.h"
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

    HeartWave *heartWave;

    bool powerStatus;

    Ui::MainWindow *ui;
    QListWidget *activeQListWidget;
    QWidget *activeWidget;

    void togglePower(void);
    void initializeMainMenu(Menu* m);
    void updateView(const QString, const QStringList); //QWidget *active_widget);
    void startSession();

private slots:

    void goToMainMenu(void);
    void goBack(void);
    void goUp(void);
    void goDown(void);
    void selectMenuOption(void);
    void turnOnOff(void);
    void rechargeBattery(void);
    void changeBatteryLevel(double newLevel);
    void updateSensorConnectedLabel(int index);
    void changeBPSetting(int newSetting);
    void resetSettings(void);

};
#endif // MAINWINDOW_H
