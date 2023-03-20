#ifndef DIALOG_H
#define DIALOG_H

#include "polynom.h"
#include <QDialog>
class QLabel;
class QLineEdit;
class QPushButton;


class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog() = default;

private:
    QLineEdit *inputLine;
    QLineEdit *setValsLine;

    QLineEdit *setValX;
    QLineEdit *setValY;
    QLineEdit *setValZ;

    QLineEdit *setLineA;
    QLineEdit *setLineB;
    QLineEdit *setLineC;

    QPushButton *calculateButton;
    QPushButton *calculateInPointButton;

    QLabel *resultLable;
    QLabel *answerLabel;
    QLabel *valInPoint;
    QLabel *signX;
    QLabel *signY;
    QLabel *signZ;
    QLabel *signA;
    QLabel *signB;
    QLabel *signC;
    QLabel *blank;
    QLabel *inputStart;

    polynom A;
    polynom B;
    polynom C;
    polynom inputPolynom;

    double x;
    double y;
    double z;

private slots:
    void setPolynomA(const std::string& str){
        A.set_data(str);
    }


};

#endif // DIALOG_H
