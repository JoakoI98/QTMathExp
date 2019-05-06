#define PY_SSIZE_T_CLEAN
#include "Controller/_pythoncontroller.h"
#include "View/expressionwidget.h"
#include <QApplication>
#include <windows.h>
#include <iostream>
#include <QMainWindow>
#include "Controller/mathbinaryoperands.h"
#include "Controller/mathfinaloperands.h"
#include "Controller/mathunaryoperands.h"
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QScrollArea>
#include "Controller/literalsdefinitions.h"
#include "Controller/_mathoperandfactory.h"
#include "Controller/_factoryfunctions.h"
#include <sstream>
#include <QImage>
#include "View/qexplatexwidget.h"


/*MathOperand &cCreator(vector<MathOperand&> argq){
    MathOperand *cnew = new MathConstant(5);
    return *cnew;
}*/


PyObject *op_Divider::PyModuleS = nullptr;
PyObject *op_Divider::PyMakeExpS = nullptr;
PyObject *op_Divider::PyRenderOpS = nullptr;
PyObject *op_Divider::PyOpDividerS = nullptr;
PyObject *op_Divider::PyOpDividerFromStrS = nullptr;


void registerOperations(){
    typedef MathOperand &(*fType)(_MathArg_ *);
    _MathOperandFactory<std::string, fType> *fact = _MathOperandFactory<std::string, fType>::getInstance();
    if (fact == nullptr){
        std::cout << "Nulo" << std::endl;
        return;
    }
    fact->registerElement("Add", _functionFactory::_bynaryCreator<MathAddOperator>);
    fact->registerElement("Subs", _functionFactory::_bynaryCreator<MathSubsOperator>);
    fact->registerElement("Mul", _functionFactory::_bynaryCreator<MathMultOperator>);
    fact->registerElement("Div", _functionFactory::_bynaryCreator<MathDivOperator>);
    fact->registerElement("Pow", _functionFactory::_bynaryCreator<MathPowerOperator>);
    fact->registerElement("sin", _functionFactory::_unaryCreator<MathSinOperand>);
    fact->registerElement("cos", _functionFactory::_unaryCreator<MathCosOperand>);
    fact->registerElement("tan", _functionFactory::_unaryCreator<MathTgOperand>);
    fact->registerElement("exp", _functionFactory::_unaryCreator<MathExpOperand>);
    fact->registerElement("log", _functionFactory::_unaryCreator<MathLnOperand>);
    fact->registerElement("Symbol", _functionFactory::_varCreator);
    fact->registerElement("Constant", _functionFactory::_constCreator);
}



int main(int argc, char *argv[])
{


    using namespace std;
    QApplication a(argc, argv);

    string pName = "_pyParser";
    wchar_t *pNameW = new wchar_t[pName.size()+1];
    mbstowcs(pNameW,pName.c_str(),pName.size()+1);


    Py_SetProgramName(pNameW);

    _pyOperations::pySetUp("_pyParser");
    registerOperations();

    op_Divider *p = op_Divider::getDividerFromString("x");
    op_Divider *p3 = op_Divider::getDividerFromString("sin(x)/x");
    cout << "Creados" << endl;
    cout << p->convertMathOperand().getStringOp() << endl;
    cout << p3->convertMathOperand().getStringOp() << endl;

    int er = 0;
    _pyOperations::deleteTmp();
    return er;


}
