#ifndef CALCULATORWINDOW_H
#define CALCULATORWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>
#include <QSize>

namespace Ui {
class CalculatorWindow;
}

class CalculatorWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CalculatorWindow(QWidget *parent = 0);
    ~CalculatorWindow();

    void resizeFont(void);

    bool event(QEvent *event);
    void windowStateChangeEvent(QWindowStateChangeEvent* event);
    void resizeEvent(QResizeEvent* event);
    void showEvent(QShowEvent *event);

public slots:
    void a();

private:
    Ui::CalculatorWindow *ui;
    bool isInitialized;
};

#endif // CALCULATORWINDOW_H
