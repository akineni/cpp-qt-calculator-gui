#include "mainwindow.h"
#include "ui_mainwindow.h"

/*
 * new input: clears the display to prevent appending new digits
*/
bool newInp, equals;
double res;     //result
QString op;     //operation

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("akineni");

    connect(ui->pushButton_0, SIGNAL(released()), this, SLOT(digitPressed()));
    connect(ui->pushButton_1, SIGNAL(released()), this, SLOT(digitPressed()));
    connect(ui->pushButton_2, SIGNAL(released()), this, SLOT(digitPressed()));
    connect(ui->pushButton_3, SIGNAL(released()), this, SLOT(digitPressed()));
    connect(ui->pushButton_4, SIGNAL(released()), this, SLOT(digitPressed()));
    connect(ui->pushButton_5, SIGNAL(released()), this, SLOT(digitPressed()));
    connect(ui->pushButton_6, SIGNAL(released()), this, SLOT(digitPressed()));
    connect(ui->pushButton_7, SIGNAL(released()), this, SLOT(digitPressed()));
    connect(ui->pushButton_8, SIGNAL(released()), this, SLOT(digitPressed()));
    connect(ui->pushButton_9, SIGNAL(released()), this, SLOT(digitPressed()));

    connect(ui->pushButton_plusMinus, SIGNAL(released()), this, SLOT(unary_operator_button_released()));
    connect(ui->pushButton_pcent, SIGNAL(released()), this, SLOT(unary_operator_button_released()));

    connect(ui->pushButton_plus, SIGNAL(released()), this, SLOT(binary_operator_button_released()));
    connect(ui->pushButton_minus, SIGNAL(released()), this, SLOT(binary_operator_button_released()));
    connect(ui->pushButton_mult, SIGNAL(released()), this, SLOT(binary_operator_button_released()));
    connect(ui->pushButton_div, SIGNAL(released()), this, SLOT(binary_operator_button_released()));

    QFontDatabase::addApplicationFont(":/font/digital-7");
    QFontDatabase::addApplicationFont(":/font/digital-7i");
    QFontDatabase::addApplicationFont(":/font/digital-7-m");
    QFontDatabase::addApplicationFont(":/font/digital-7i-m");
    ui->label->setFont(QFont("Digital-7",20, QFont::Bold));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digitPressed()
{
    QPushButton *button = (QPushButton*)sender();

    if(newInp) ui->label->clear();
    newInp = false;
    equals = false;
    QString str = ui->label->text() + button->text();

    if(ui->label->text().indexOf('.') > -1 && button->text() == "0") {
        ui->label->setText(str);
        return;
    }

    double val = str.toDouble();
    ui->label->setText(QString::number(val,'g',15));
}

void MainWindow::on_pushButton_dec_released()
{
    if(equals) ui->label->setText("0");
    newInp = false;

    if(ui->label->text().indexOf('.') == -1) ui->label->setText(ui->label->text() + ".");
}

void MainWindow::unary_operator_button_released()
{
    QPushButton *button = (QPushButton*)sender();

    if(button->text() == "+/-") {
        double val = ui->label->text().toDouble() * -1;
        ui->label->setText(QString::number(val,'g',15));
    }else if(button->text() == "%") {
        double val = ui->label->text().toDouble() * .01;
        ui->label->setText(QString::number(val,'g',15));
    }
}

void MainWindow::binary_operator_button_released()
{
    QPushButton *button = (QPushButton*)sender();
    compute();
    ui->label->setText(QString::number(res, 'g', 15));
    op = button->text();
    newInp = true;
}

void MainWindow::compute() {
    if(op == "+")
        res += ui->label->text().toDouble();
    else if(op == "-")
        res -= ui->label->text().toDouble();
    else if(op == "x")
        res *= ui->label->text().toDouble();
    else if(op == "/")
        res /= ui->label->text().toDouble();
    else
        res = ui->label->text().toDouble();
}

void MainWindow::on_pushButton_clr_released()
{
    ui->label->setText("0");
    resetVars();
}

void MainWindow::on_pushButton_equals_released()
{
    if(!equals){
        if(!newInp) compute();
        ui->label->setText(QString::number(res, 'g', 15));
        equals = true;
        resetVars();
    }
}

void resetVars() {
    res = 0;
    op.clear();
    newInp = true;
}
