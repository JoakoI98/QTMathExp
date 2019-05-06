#ifndef _PYTHONCONTROLLER_H
#define _PYTHONCONTROLLER_H
#include "Python.h"
#include <vector>
#include <string>
#include "mathoperand.h"
#include <map>
#include "_mathoperandfactory.h"



class op_Divider{
    public:
        unsigned int argsNumber;
        std::vector<op_Divider *> args;
        std::string _strRep;
        std::string _symbol;
        double _value;
        void printStr();
        MathOperand &convertMathOperand(std::vector<std::string> *symbolList = nullptr);
        static op_Divider *getDividerFromString(std::string str);
        op_Divider(PyObject *obj);
        op_Divider();
        op_Divider(std::string strR);
        op_Divider(std::string strR, std::string strSym);
        op_Divider(std::string strR, double value);

        ~op_Divider();


        static PyObject *PyModuleS;
        static PyObject *PyMakeExpS;
        static PyObject *PyRenderOpS;
        static PyObject *PyOpDividerS;
        static PyObject *PyOpDividerFromStrS;
};

//PyObject *op_Divider::PyModuleS = nullptr;
//PyObject *op_Divider::PyMakeExpS = nullptr;
//PyObject *op_Divider::PyRenderOpS = nullptr;
//PyObject *op_Divider::PyOpDividerS = nullptr;
namespace _pyOperations {
    void pySetUp(std::string fName);
    std::string GetCurrentWorkingDir();
    void renderLatexFormula(MathOperand &op, std::string fName);
    void deleteTmp();
}




#endif // _PYTHONCONTROLLER_H
