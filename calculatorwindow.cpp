#include "calculatorwindow.h"
#include "ui_calculatorwindow.h"
#include <iostream>

CalculatorWindow::CalculatorWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CalculatorWindow)
{
    this->isInitialized = false;
    this->fontAspectRaito = 0;

    ui->setupUi(this);

    QObject::connect(ui->EqualButton, SIGNAL(clicked()), this, SLOT(a()));
    QObject::connect(ui->NumButton_0, SIGNAL(clicked()), this, SLOT(addNumberZero()));
    QObject::connect(ui->NumButton_1, SIGNAL(clicked()), this, SLOT(addNumberOne()));
    QObject::connect(ui->NumButton_2, SIGNAL(clicked()), this, SLOT(addNumberTwo()));
    QObject::connect(ui->NumButton_3, SIGNAL(clicked()), this, SLOT(addNumberThree()));
    QObject::connect(ui->NumButton_4, SIGNAL(clicked()), this, SLOT(addNumberFour()));
    QObject::connect(ui->NumButton_5, SIGNAL(clicked()), this, SLOT(addNumberFive()));
    QObject::connect(ui->NumButton_6, SIGNAL(clicked()), this, SLOT(addNumberSix()));
    QObject::connect(ui->NumButton_7, SIGNAL(clicked()), this, SLOT(addNumberSeven()));
    QObject::connect(ui->NumButton_8, SIGNAL(clicked()), this, SLOT(addNumberEight()));
    QObject::connect(ui->NumButton_9, SIGNAL(clicked()), this, SLOT(addNumberNine()));
    QObject::connect(ui->PointButton, SIGNAL(clicked()), this, SLOT(addDecimalPoint()));
    QObject::connect(ui->RBracketButton, SIGNAL(clicked()), this, SLOT(addRightBracket()));
    QObject::connect(ui->LBracketButton, SIGNAL(clicked()), this, SLOT(addLeftBracket()));
    QObject::connect(ui->ClearButton, SIGNAL(clicked()), this, SLOT(ClearData()));
    QObject::connect(ui->AddButton, SIGNAL(clicked()), this, SLOT(addAddSymbol()));
    QObject::connect(ui->SubtractButton, SIGNAL(clicked()), this, SLOT(addSubtractSymbol()));
    QObject::connect(ui->MultiplyButton, SIGNAL(clicked()), this, SLOT(addMultiplySymbol()));
    QObject::connect(ui->DivideButton, SIGNAL(clicked()), this, SLOT(addDivideSymbol()));

}

CalculatorWindow::~CalculatorWindow()
{

    delete ui;
}

void CalculatorWindow::addNumber(QString num){
    QString value = ui->valueDisplay->text();
    if (value.remove(".").length() >= 20) return;
    value = ui->valueDisplay->text();
    if (value == "0")
        ui->valueDisplay->setText(num);
    else
        ui->valueDisplay->setText(value+num);
    this->resizeFont();
}

void CalculatorWindow::addDecimalPoint(void){
    QString value = ui->valueDisplay->text();
    if (value.indexOf(".") < 0)
        ui->valueDisplay->setText(value+".");
}

void CalculatorWindow::addLeftBracket(void){
    ui->valueDisplay->setText(ui->valueDisplay->text()+"(");
}
void CalculatorWindow::addRightBracket(void){
    ui->valueDisplay->setText(ui->valueDisplay->text()+")");
}

void CalculatorWindow::ClearData(void){
    ui->valueDisplay->setText("0");
}

void CalculatorWindow::addAddSymbol(void){ this->addSymbol("＋"); }
void CalculatorWindow::addSubtractSymbol(void){ this->addSymbol("−"); }
void CalculatorWindow::addMultiplySymbol(void){ this->addSymbol("×"); }
void CalculatorWindow::addDivideSymbol(void){ this->addSymbol("÷"); }

void CalculatorWindow::addSymbol(QString symbol){
    QString value = ui->valueDisplay->text();
    ui->formulaDisplay->setText(ui->formulaDisplay->text() + value + symbol);
    ui->valueDisplay->setText("0");
}

void CalculatorWindow::addNumberZero(void){ this->addNumber("0"); }
void CalculatorWindow::addNumberOne(void){ this->addNumber("1"); }
void CalculatorWindow::addNumberTwo(void){ this->addNumber("2"); }
void CalculatorWindow::addNumberThree(void){ this->addNumber("3"); }
void CalculatorWindow::addNumberFour(void){ this->addNumber("4"); }
void CalculatorWindow::addNumberFive(void){ this->addNumber("5"); }
void CalculatorWindow::addNumberSix(void){ this->addNumber("6"); }
void CalculatorWindow::addNumberSeven(void){ this->addNumber("7"); }
void CalculatorWindow::addNumberEight(void){ this->addNumber("8"); }
void CalculatorWindow::addNumberNine(void){ this->addNumber("9"); }




bool CalculatorWindow::event(QEvent *event){

    bool returnValue = QMainWindow::event(event);

    if(event->type() == QEvent::WindowStateChange){
        this->windowStateChangeEvent((QWindowStateChangeEvent*)event);
        returnValue = true;
    }

    return returnValue;
}


void CalculatorWindow::windowStateChangeEvent(QWindowStateChangeEvent* event){
    std::cout << "window" << std::endl;
    this->resizeFont();
}

void CalculatorWindow::resizeEvent(QResizeEvent* event){
    std::cout << "resize" << std::endl;
    this->resizeFont();
}


void CalculatorWindow::showEvent(QShowEvent *event){
    std::cout << "show" << std::endl;
    this->resizeFont();

    if(this->isInitialized)
        return;
    QLabel *vd = ui->valueDisplay;
    this->fontAspectRaito = vd->font().pixelSize()/(vd->width()/(double)vd->text().length());
    this->isInitialized = true;
}

void CalculatorWindow::resizeFont(void){
    double allstretch=0, raito=0;
    int px=0, real_width=0;
    QBoxLayout* layout = (QBoxLayout*)ui->centralWidget->layout();
    for(int i=0; i < layout->count(); i++){
        allstretch += layout->stretch(i);
    }

    //ValueDisplay
    raito = layout->stretch(layout->indexOf(ui->valueWidget))/allstretch;
    px = ui->centralWidget->height()*raito*3/4.0;
    real_width = px/this->fontAspectRaito*ui->valueDisplay->text().length();
    if(real_width > ui->centralWidget->width())
        px = ui->centralWidget->width()/(double)ui->valueDisplay->text().length()*this->fontAspectRaito;
    QFont font = ui->valueDisplay->font();
    font.setPixelSize(px);
    ui->valueDisplay->setFont(font);

    //FormulaDisplay
    raito = layout->stretch(layout->indexOf(ui->formulaWidget))/allstretch;
    px = ui->centralWidget->height()*raito*3/4.0;
    font = ui->formulaDisplay->font();
    font.setPixelSize(px);
    ui->formulaDisplay->setFont(font);
}

void CalculatorWindow::a(){

}
