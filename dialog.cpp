#include "dialog.h"
#include <QtWidgets>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{

    // Делаем кнопочки
    inputLine = new QLineEdit();
    setValsLine = new QLineEdit(tr("x =  y =   z = "));
    setLineA = new QLineEdit(tr("2x^3y - 8yz^5"));
    setLineB = new QLineEdit(tr("y^3 - x^3z"));
    setLineC = new QLineEdit(tr("xyz - 2xyz^3"));
    calculateButton = new QPushButton(tr("Calculate"));
    answerLabel = new QLabel(tr("Insert polynoms:"));
    // Новые кнопочки
    inputStart = new QLabel(tr("Input Polynom using polynoms-variables a, b, c"));
    setValX = new QLineEdit();
    setValY = new QLineEdit();
    setValZ = new QLineEdit();
    resultLable = new QLabel(tr("Resulting polynom: "));
    calculateInPointButton = new QPushButton(tr("Calculate in point"));
    valInPoint = new QLabel(tr("Result: 5"));
    signX = new QLabel(tr("x ="));
    signY = new QLabel(tr("y ="));
    signZ = new QLabel(tr("z ="));
    signA = new QLabel(tr("a ="));
    signB = new QLabel(tr("b ="));
    signC = new QLabel(tr("c ="));
    blank = new QLabel();

    calculateButton->setStyleSheet("background-color:yellow;");
    inputLine->setStyleSheet("background-color:blue;");
    //calculateInPointButton->setStyleSheet("background-color:cyan;");
    setValX->setStyleSheet("background-color:white;");
    setValY->setStyleSheet("background-color:blue;");
    setValZ->setStyleSheet("background-color:red;");


    QVBoxLayout *signsLayout = new QVBoxLayout;
    signsLayout->addWidget(signX);
    signsLayout->addWidget(signY);
    signsLayout->addWidget(signZ);

    QVBoxLayout *polNamesLayout = new QVBoxLayout;
    polNamesLayout->addWidget(signA);
    polNamesLayout->addWidget(signB);
    polNamesLayout->addWidget(signC);

    QVBoxLayout *setVals = new QVBoxLayout;
    setVals->addWidget(setValX);
    setVals->addWidget(setValY);
    setVals->addWidget(setValZ);

    QHBoxLayout *eqLayout = new QHBoxLayout;
    eqLayout->addLayout(signsLayout);
    eqLayout->addLayout(setVals);

    QVBoxLayout *setLines = new QVBoxLayout;
    setLines->addWidget(setLineA);
    setLines->addWidget(setLineB);
    setLines->addWidget(setLineC);

    QHBoxLayout *setPolLayout = new QHBoxLayout;
    setPolLayout->addLayout(polNamesLayout);
    setPolLayout->addLayout(setLines);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(inputStart);
    mainLayout->addWidget(inputLine);
    mainLayout->addWidget((calculateButton));
    mainLayout->addWidget(resultLable);
    mainLayout->addWidget(blank);
    mainLayout->addLayout(eqLayout);
    mainLayout->addWidget(calculateInPointButton);
    mainLayout->addWidget(valInPoint);
    mainLayout->addWidget(blank);
    mainLayout->addWidget(answerLabel);
    mainLayout->addLayout(setPolLayout);

    calculateButton->setDefault(true);

    setLayout(mainLayout);
    setWindowTitle("Лиза, улыбнись");
    setFixedWidth(750);


}
