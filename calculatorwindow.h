#ifndef CALCULATORWINDOW_H
#define CALCULATORWINDOW_H

#include <QMainWindow>

namespace Ui {
class CalculatorWindow;
}

class CalculatorWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CalculatorWindow(QWidget *parent = 0);
    ~CalculatorWindow();

private:
    Ui::CalculatorWindow *ui;
};

#endif // CALCULATORWINDOW_H
