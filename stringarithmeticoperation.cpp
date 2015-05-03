#include "stringarithmeticoperation.h"

const int N = 15;

QString StringArithmeticOperation(QString formula){
    int index=0;
    int prec = (1000000)*3.32;//100万桁
    mpf_set_default_prec(prec);
    QRegExp r("[0-9]\\(|\\)[-0-9]+|\\)\\(");
    //正規化(×を省略しているところに追加)
    while((index=r.indexIn(formula)) != -1)
        formula.insert(index+1, "*");

    formula.replace("＋", "p");
    formula.replace("−", "m");
    formula.replace("×", "*");
    formula.replace("÷", "/");


    QString RPN = parseMethod(formula);
    QString result = calcrateMethod(RPN);

    return result;
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
    QStack<char> SymbolStack;
    QString RPN;
    bool rpnBlock = false;
    char ch;
    int top, chpriority;

    for(int i=0; i<formula.length(); i++){
        ch = formula[i].toLatin1();
        if(rpnBlock){
            if(ch == ']'){
                RPN += ' ';
                rpnBlock = false;
            }
            else{
                RPN += ch;
                continue;
            }
        }

        switch(ch){
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


QString calcrateMethod(QString formula){
    QRegExp r(" +");
    QStringList list = formula.split(r);
    QStack<mpf_class> numBuffer;
    QString buf;
    mpf_class op1, op2, tmp;
    std::ostringstream ostream;
    mp_exp_t e;
    int i=0;

    throw "Yahooooo";

    for(int i=0; i<list.length(); i++){
        buf = list[i];
        if(buf.isEmpty())continue;
        switch (buf[0].toLatin1()) {
        case 'p':
            op2 = numBuffer.pop();
            op1 = numBuffer.pop();
            numBuffer.push(op1 + op2);
            break;
        case 'm':
            op2 = numBuffer.pop();
            op1 = numBuffer.pop();
            numBuffer.push(op1 - op2);
            break;
        case '*':
            op2 = numBuffer.pop();
            op1 = numBuffer.pop();
            numBuffer.push(op1 * op2);
            break;
        case '/':
            op2 = numBuffer.pop();
            op1 = numBuffer.pop();
            numBuffer.push(op1 / op2);
            break;
        default:
            tmp.set_str(buf.toStdString(), 10);
            numBuffer.push(tmp);
            break;
        }
    }

    tmp = numBuffer.pop();
    ostream << tmp;
    std::string f = tmp.get_str(e, 10, N);
    QString result;
    buf = "";
    if(0 < e && e <= N){
        result += f.c_str();
        if((ulong)e >= f.length()){
            for(i=0; i<(int)(e-f.length()); i++)
                result += "0";
        }
        else{
            if(f[0]!='-'){
                result.insert(e, "."); //ここ！！
            }
            else{
                result.insert(e+1, "."); //ここ！！
            }
        }
    }
    else if(0 < f.length()-e && f.length()-e <= N+1){ //符号分の+1
        e=std::abs(e);
        for(i=0; i<e; i++)
            buf += "0";
        if(f[0]!='-'){
            result += "0."; //ここ！！
            result += buf+f.c_str();
        }
        else{
            result += "-0."; //ここ！！
            result += buf+f.substr(1).c_str();
        }
    }
    else{
        buf = "%1%2%3";
        e--;
        if(0 < e)
            result = buf.arg(f.c_str()).arg("e+").arg(e);
        else
            result = buf.arg(f.c_str()).arg("e-").arg(-e);
        if(f.length() > 1){
            if(f[0]!='-'){
                result.insert(1, "."); //ここ！！
            }
            else{
                result.insert(2, "."); //ここ！！
            }
        }
    }
    return result;

}

int symbolPriority(char ch){
    switch(ch){
    case 'p': return 1;
    case 'm': return 1;
    case '*': return 2;
    case '/': return 2;
    }
    return 0;
}

