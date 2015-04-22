#include "calculatorwindow.h"
#include "ui_calculatorwindow.h"
#include <iostream>

CalculatorWindow::CalculatorWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CalculatorWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->pushButton_20, SIGNAL(clicked()), this, SLOT(a()));


}

CalculatorWindow::~CalculatorWindow()
{

    delete ui;
}

bool CalculatorWindow::event(QEvent *event){

    bool returnValue = QMainWindow::event(event);

    if(event->type() == QEvent::WindowStateChange){
        this->windowStateChangeEvent((QWindowStateChangeEvent*)event);
        returnValue = true;
    }

    return returnValue;
}


void CalculatorWindow::windowStateChangeEvent(QWindowStateChangeEvent* event){
    std::cout<<"Hey!!"<<std::endl;
    this->resizeFont();
}

void CalculatorWindow::resizeEvent(QResizeEvent* event){
    this->resizeFont();
}


void CalculatorWindow::showEvent(QShowEvent *event){
    if(this->isInitialized)
        return;
    this->resizeFont();
    this->isInitialized = true;
}

void CalculatorWindow::resizeFont(void){
    double allstretch=0;
    QBoxLayout* layout = (QBoxLayout*)ui->centralWidget->layout();
    for(int i=0; i < layout->count(); i++){
        allstretch += layout->stretch(i);
    }

    double raito = layout->stretch(layout->indexOf(ui->valueWidget))/allstretch;
    int px = ui->centralWidget->height()*raito*3/4.0;
    QFont font = ui->valueDisplay->font();
    font.setPixelSize(px);
    ui->valueDisplay->setFont(font);
    raito = layout->stretch(layout->indexOf(ui->formulaWidget))/allstretch;
    px = ui->centralWidget->height()*raito*3/4.0;
    font = ui->formulaDisplay->font();
    font.setPixelSize(px);
    ui->formulaDisplay->setFont(font);
}

void CalculatorWindow::a(){

    std::cout <<  ui->valueDisplay->width() << std::endl;
    std::cout <<  ui->centralWidget->width() << std::endl;
}
