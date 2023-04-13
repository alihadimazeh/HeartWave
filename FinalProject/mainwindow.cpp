#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
       // ui->setupUi(this);
      //  QPixmap bkgnd("/home/student/COMP3004-GP/HeartWave/FinalProject/resources/maindisplay.svg");
       // bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
//        QPalette palette;
    //    palette.setBrush(QPalette::Background, bkgnd);
      //  this->setPalette(palette);

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

