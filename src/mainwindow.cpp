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
    // TODO
        // 1. Parse lineEdit.text()
        // 2. Check if we have this name in tables
        //   3.a Update val in tables and QTableWidget
        //   3.b Set new <key, value> in tables and add new row in QTableWidget

        QString data = ui->lineEdit->text();

        QString polynomName = static_cast<QString>(data[0]);
        QString polynomData = "";

        for (size_t i = 2; i < static_cast<size_t>(data.size()); i++)
            if (data[i] != ' ' && data[i] != '=')
                polynomData += data[i];

        Polynom polynom(polynomData.toStdString());

        if (allTables.find(polynomName.toStdString()) == false) {
            allTables.insert(polynomName.toStdString(), polynom);

            ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            QTableWidgetItem *itemName = new QTableWidgetItem(polynomName);
            QTableWidgetItem *itemPolynom = new QTableWidgetItem(polynomData);

            ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, itemName);
            ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, itemPolynom);
        }
        else {

        }
}
