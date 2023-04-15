#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
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
    Menu* masterMenu;
    Menu* mainMenuOG;
    Menu* previousMenu;

    HeartWave *heartWave;

    bool powerStatus;

    Ui::MainWindow *ui;

    void togglePower(void);

private slots:
    void goToMainMenu(void);
    void navigateBack(void);
    void turnOnOff(void);
    void rechargeBattery(void);
};
#endif // MAINWINDOW_H
