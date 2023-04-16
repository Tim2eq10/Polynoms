#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <vector>

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
        QString rawInput = ui->lineEdit->text();
        QString input = "";
        QString polynomName;

        for (auto c : rawInput)
            if (c != ' ')
                input += c;

        if (input.size() > 0 && input[0] >= 'A' && input[0] <= 'Z')
            polynomName = static_cast<QString>(input[0]);
        else
            return;

        if (input[1] != '=')
            return;

        QString polynomData = "";
        for (int i = 2; i < input.size(); i++)
            polynomData += input[i];

        // Transform to Polynom
        Polynom polynom;
        try {
            polynom = Polynom(polynomData.toStdString());
        }
        catch(std::invalid_argument) {
            return;
        }



        // Add/change in tables
        if (allTables.find(polynomName.toStdString()) == false) {
            allTables.insert(polynomName.toStdString(), polynom);
            ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            QTableWidgetItem *itemName = new QTableWidgetItem(polynomName);
            QTableWidgetItem *itemPolynom = new QTableWidgetItem(polynomData);

            ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, itemName);
            ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, itemPolynom);
        }
        else {
            allTables.insert(polynomName.toStdString(), polynom);

            for (int i = 0; i < ui->tableWidget->rowCount(); i++)
                if (ui->tableWidget->item(i, 0)->text() == polynomName) {
                    QTableWidgetItem *itemName = new QTableWidgetItem(polynomName);
                    QTableWidgetItem *itemPolynom = new QTableWidgetItem(polynomData);
                    //QTableWidgetItem *itemPolynom = new QTableWidgetItem(QString::fromStdString(polynom.getPolynom()));

                    ui->tableWidget->setItem(i, 0, itemName);
                    ui->tableWidget->setItem(i, 1, itemPolynom);

                    return;
                }
        }

}


void MainWindow::on_pushButton_3_clicked()
{
    string input = ui->lineEdit_2->text().toStdString();

    try {
        ArithmeticalExpression expr(input);
        Polynom result = expr.getExpr(allTables);
        //string output = result.getPolynom() + " | value in dot: "  + std::to_string(result.PolynomValueInPoint(valueX, valueY, valueZ));
        string output = "REAL DATA";
        ui->lineEdit_3->setText(QString::fromStdString(output));
    }
    catch (...) {
        ui->lineEdit_3->setText(QString::fromStdString("FAIL"));
        return;
    }
}
