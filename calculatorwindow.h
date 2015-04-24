#ifndef CALCULATORWINDOW_H
#define CALCULATORWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>
#include <QSize>
#include <QGraphicsTextItem>

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
    void a(void);
    void addNumberZero(void);
    void addNumberOne(void);
    void addNumberTwo(void);
    void addNumberThree(void);
    void addNumberFour(void);
    void addNumberFive(void);
    void addNumberSix(void);
    void addNumberSeven(void);
    void addNumberEight(void);
    void addNumberNine(void);
    void addDecimalPoint(void);
    void addRightBracket(void);
    void addLeftBracket(void);
    void ClearData(void);
    void addAddSymbol(void);
    void addSubtractSymbol(void);
    void addMultiplySymbol(void);
    void addDivideSymbol(void);

private:
    Ui::CalculatorWindow *ui;
    bool isInitialized;
    double fontAspectRaito;
    QString *formulaStr;
    QString *valueStr;

    void addNumber(QString num);
    void addSymbol(QString symbol);
};

#endif // CALCULATORWINDOW_H
