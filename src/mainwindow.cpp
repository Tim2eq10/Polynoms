#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Name" << "Polynom" << "Derivative" << "Integral");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    std::string stringX = ui->lineEdit_4->text().toStdString();
    std::string stringY = ui->lineEdit_5->text().toStdString();
    std::string stringZ = ui->lineEdit_6->text().toStdString();

    try {
        valueX = std::stod(stringX);
    } catch(...) {
        valueX = 0;
        ui->lineEdit_4->setText("0");
    }
    try {
        valueY = std::stod(stringY);
    } catch(...) {
        valueY = 0;
        ui->lineEdit_5->setText("0");
    }
    try {
        valueZ = std::stod(stringZ);
    } catch(...) {
        valueZ = 0;
        ui->lineEdit_6->setText("0");
    }
}

void MainWindow::on_pushButton_clicked()
{
    ui->tableWidget->insertRow( ui->tableWidget->rowCount() );
}
