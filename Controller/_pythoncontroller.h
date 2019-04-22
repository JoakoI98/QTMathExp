#ifndef _PYTHONCONTROLLER_H
#define _PYTHONCONTROLLER_H
#include "Python.h"
#include <vector>
#include <string>
#include "mathoperand.h"

using namespace std;





class _pythonController
{
public:
    _pythonController();

    static void prtNewStr(string _strParse);

    ~_pythonController();

private:
    class op_Divider{
    public:
        unsigned int argsNumber;
        vector<op_Divider *> args;
        string _strRep;
        string _symbol;
        double _value;
        void printStr();
        MathOperand &convertMathOperand();
        op_Divider(PyObject *obj);
        ~op_Divider();
    };



    static op_Divider &_pyObjectToDivider(PyObject *_pyObject);

    vector<string> symbolTable;

    MathOperand &_classConverterAdd(_pythonController::op_Divider divider);
    MathOperand &_classConverterSubs(_pythonController::op_Divider divider);
    MathOperand &_classConverterMult(_pythonController::op_Divider divider);
    MathOperand &_classConverterDiv(_pythonController::op_Divider divider);
    MathOperand &_classConverterSin(_pythonController::op_Divider divider);
    MathOperand &_classConverterLn(_pythonController::op_Divider divider);
    MathOperand &_classConverterPow(_pythonController::op_Divider divider);
    MathOperand &_classConverterExp(_pythonController::op_Divider divider);
    MathOperand &_classConverterSymbol(_pythonController::op_Divider divider);
    MathOperand &_classConverterConstant(_pythonController::op_Divider divider);

};



#endif // _PYTHONCONTROLLER_H
