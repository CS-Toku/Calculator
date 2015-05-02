#include "stringarithmeticoperation.h"

QString StringArithmeticOperation(QString formula){
    int index=0;
    QRegExp r("[0-9]\\(|\\)[-0-9]+");
    //正規化(×を省略しているところに追加)
    while((index=r.indexIn(formula)) != -1)
        formula.insert(index+1, "*");

    formula.replace("＋", "p");
    formula.replace("−", "m");
    formula.replace("×", "*");
    formula.replace("÷", "/");

    QString RPN = parseMethod(formula);
    calcrateMethod(RPN);

    return RPN;
}


QString parseMethod(QString formula){
    int index=0;
    QString bracketFormula;
    QString normalizedFormula;
    QRegExp r("\\(|\\)");

    //()を外す作業。あったら中身を取り出して再帰呼び出し
    if((index=formula.indexOf("(")) != -1){
        while((index=formula.indexOf("(")) != -1){
            int start = index, end=0;
            int bracketCount = 0;
            while(end==0){
                index=formula.indexOf(r, index+1);
                switch(formula[index].toLatin1()){
                case '(':
                    bracketCount++;
                    break;
                case ')':
                    if(bracketCount == 0)
                        end = index;
                    else
                        bracketCount--;
                    break;
                default:
                    throw "internal Error!!";
                    break;
                }
            }
            bracketFormula = formula.mid(start+1, end-start-1);
            normalizedFormula = parseMethod(bracketFormula);
            formula.replace("("+bracketFormula+")", "["+normalizedFormula+"]");
        }
    }

    //逆ポーランドに置き換え
    //QStack<QString> NumStack;
    QStack<char> SymbolStack;
    QString RPN;
    bool rpnBlock = false;
    char ch;
    int top, chpriority;

    for(int i=0; i<formula.length(); i++){
        ch = formula[i].toLatin1();
        if(rpnBlock){
            if(ch == ']'){
                //RPN += ' ';
                rpnBlock = false;
            }
            else{
                RPN += ch;
                continue;
            }
        }

        switch(ch){
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '.':
        case '+':
        case '-':
        case 'e':
            RPN += ch;
            break;
        case 'p':
        case 'm':
        case '*':
        case '/':
            RPN += ' ';
            chpriority = symbolPriority(ch);
            while(true){
                if(!SymbolStack.isEmpty()){
                    top = symbolPriority(SymbolStack.top());
                    if(top < chpriority){
                        SymbolStack.push(ch);
                        break;
                    }
                    else{
                        RPN += SymbolStack.pop();
                        RPN += ' ';
                    }
                }
                else{
                    SymbolStack.push(ch);
                    break;
                }
            }
            break;
        case '[':
            rpnBlock = true;
            break;
        default:
            continue;
        }
    }

    while(!SymbolStack.isEmpty()){
        RPN += ' ';
        RPN += SymbolStack.pop();
    }

    return RPN;
}


void calcrateMethod(QString formula){
    QStringList list = formula.split(" ");
    for(int i=0; i<list.length(); i++){
        std::cout << list[i].toStdString() << std::endl;
    }
}

int symbolPriority(char ch){
    switch(ch){
    case 'p': return 1;
    case 'm': return 1;
    case '*': return 2;
    case '/': return 2;
    }
}

