#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"bp.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Train_clicked()
{
    bp_train();
}
