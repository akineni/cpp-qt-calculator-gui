#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFontDatabase>

extern bool newInp, equals;
extern QString op;
extern double res;

void resetVars();

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    void compute();

public slots:
    void digitPressed();
    void on_pushButton_dec_released();
    void unary_operator_button_released();
    void binary_operator_button_released();
    void on_pushButton_clr_released();
    void on_pushButton_equals_released();

signals:

};

#endif // MAINWINDOW_H
