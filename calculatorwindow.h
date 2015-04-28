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
    void PercentOperate(void);
    void addAddSymbol(void);
    void addSubtractSymbol(void);
    void addMultiplySymbol(void);
    void addDivideSymbol(void);
    void ExecuteOperation(void);

private:
    Ui::CalculatorWindow *ui;
    bool isInitialized;
    bool isCleared;
    enum CalcState{Init, Number, Symbol, LeftBracket, RightBracket, Point, Result};
    CalcState pre_lastState;
    CalcState lastState;
    int bracketCount;
    double fontAspectRaito;
    QString *formulaStr;
    QString *valueStr;

    void addNumber(QString num);
    void addSymbol(QString symbol);
    void saveState(CalcState state);
};

#endif // CALCULATORWINDOW_H
