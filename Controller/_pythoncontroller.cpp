#include "_pythoncontroller.h"
#include <iostream>
#include <sstream>
#include "mathfinaloperands.h"
#include "mathunaryoperands.h"
#include "mathbinaryoperands.h"
#include <stdio.h>
#include <unistd.h>



#include <algorithm>
void op_Divider::printStr()
{
    using namespace std;
    cout.flush();
    cout << this->_strRep << '(';
    if(_strRep == "Constant")
        cout << this->_value;
    else if(_strRep == "Symbol")
        cout << this->_symbol;
    else
        for(op_Divider *element : args)
            element->printStr();


    cout << ")  ";
    cout.flush();

}

MathOperand &op_Divider::convertMathOperand(std::vector<std::string> *symbolList)
{
    std::vector<std::string> *toPassList = symbolList;
    if(toPassList == nullptr){
        toPassList = new std::vector<std::string>();
    }
    for (auto xx : *toPassList){
        std::cout << xx << std::endl;
    }
    _MathArg_ *thisArgs = nullptr;
    if(_strRep != "Constant" && _strRep != "Symbol"){
        std::vector<MathOperand *> c_Args(args.size());
        for (unsigned int i = 0; i != args.size(); i++) {
            c_Args[i] = &(args[i]->convertMathOperand(toPassList));
        }
        thisArgs = (_MathArg_::getArgs(c_Args));
    } else if (_strRep == "Constant"){
        thisArgs = (_MathArg_::getArgs(_value));
    } else if (_strRep == "Symbol"){
        bool isIn = false;
        unsigned int i;
        for (i = 0; i != toPassList->size(); i++) {
            if((*toPassList)[i] == _symbol){
                isIn = true;
                break;
            }
        }
        if(!isIn){
            i = toPassList->size();
            toPassList->push_back(_symbol);
        }
        thisArgs = (_MathArg_::getArgs(static_cast<int>(i), _symbol));
    }
    if(toPassList != symbolList) delete toPassList;
    typedef MathOperand &(*fType)(_MathArg_ *);
    _MathOperandFactory<std::string, fType> *fact = _MathOperandFactory<std::string, fType>::getInstance();


    MathOperand &thisOp = fact->createOperand(_strRep, thisArgs);
    return thisOp;
}



op_Divider::op_Divider(PyObject *obj)
{
    std::cout.flush();
    using namespace std;
    args.clear();

    PyObject *_pyArgsNumber, *_pyArgs, *_pyStrRep, *_pySymbol, *_pyConstant;

    _pyArgsNumber = PyObject_GetAttrString(obj, "nargs");
    if(_pyArgsNumber == NULL) throw "Error converting nargs to pyobject";

    _pyArgs = PyObject_GetAttrString(obj, "args");
    if(_pyArgs == NULL) throw "Error converting args to pyobject";

    _pyStrRep = PyObject_GetAttrString(obj, "_strRep");
    if(_pyStrRep == NULL) throw "Error converting _strRep to pyobject";

    if(!PyLong_Check(_pyArgsNumber)) throw "nargs's pyobject is not long";
    this->argsNumber = static_cast<unsigned int>(PyLong_AsLong(_pyArgsNumber));

    if(!PyUnicode_Check(_pyStrRep)) throw "strRep's pyobject is not unicode";
    const char *_strR = PyUnicode_AsUTF8(_pyStrRep);
    this->_strRep = _strR;

    if(_strRep == "Symbol"){
        _pySymbol = PyObject_GetAttrString(obj, "_symbol");
        if(_pySymbol == NULL) throw "Error converting _symbol to pyobject";

        if(!PyUnicode_Check(_pySymbol)) throw "_symbol's pyobject is not unicode";
        const char *_strS = PyUnicode_AsUTF8(_pySymbol);
        this->_symbol = _strS;

        if(_pyArgs != NULL) Py_DecRef(_pyArgs);
        if(_pyArgsNumber != NULL) Py_DecRef(_pyArgsNumber);
        if(_pyStrRep != NULL) Py_DecRef(_pyStrRep);
        if(_pySymbol != NULL) Py_DecRef(_pySymbol);
        return;
    }

    if(_strRep == "Constant"){

        _pyConstant = PyObject_GetAttrString(obj, "_constant");
        if(_pyConstant == NULL) throw "Error converting _constant to pyobject";

        if(!PyFloat_Check(_pyConstant)){
            PyTypeObject *pyType = _pyConstant->ob_type;
            cout << pyType->tp_name << endl;
            throw "_constant's pyobject is not unicode";
        }
        double _doubleC = PyFloat_AsDouble(_pyConstant);
        this->_value = _doubleC;
        if(_pyArgs != NULL) Py_DecRef(_pyArgs);
        if(_pyArgsNumber != NULL) Py_DecRef(_pyArgsNumber);
        if(_pyStrRep != NULL) Py_DecRef(_pyStrRep);
        if(_pyConstant != NULL) Py_DecRef(_pyConstant);
        return;
    }

    if(!PyList_Check(_pyArgs)) throw "args's pyobject is not list";
    for (unsigned int i = 0; i != argsNumber; i++){
        PyObject *currentPyObject = PyList_GetItem(_pyArgs, i);
        op_Divider *currentDivider = new op_Divider(currentPyObject);
        args.push_back(currentDivider);
    }


    if(_pyArgs != NULL) Py_DecRef(_pyArgs);
    if(_pyArgsNumber != NULL) Py_DecRef(_pyArgsNumber);
    if(_pyStrRep != NULL) Py_DecRef(_pyStrRep);

}

op_Divider::op_Divider(): args(0)
{
    _symbol = "";
    _strRep = "";
    _value = 0;
    argsNumber = 0;
}

op_Divider::op_Divider(std::string strR): args(0)
{
    _symbol = "";
    _strRep = strR;
    _value = 0;
    argsNumber = 0;
}

op_Divider::op_Divider(std::string strR, double value): args(0)
{
    _symbol = "";
    _strRep = strR;
    _value = value;
    argsNumber = 0;
}

op_Divider::op_Divider(std::string strR, std::string strSym): args(0)
{
    _symbol = strSym;
    _strRep = strR;
    _value = 0;
    argsNumber = 0;
}
op_Divider::~op_Divider()
{
    for(op_Divider *element : args) delete element;
}







op_Divider *op_Divider::getDividerFromString(std::string str)
{
    using namespace std;
    const char file_Name[] = "_pyParser";

    using namespace std;

    PyObject *pyStrOp = PyUnicode_FromString(str.c_str());
    if(pyStrOp == NULL ){
        cout << "Error al crear strings unicodes" << endl;
        return nullptr;
    }

    PyObject *pyTupleArgs = PyTuple_New(1);
    if(pyTupleArgs == NULL){
        cout << "Error al crear Tupla de argumentos" << endl;
        return nullptr;
    }

    int rA0 = PyTuple_SetItem(pyTupleArgs, 0, pyStrOp);
    if(rA0 != 0){
        cout << "Error al llenar argumentos" << endl;
        return nullptr;
    }

    PyObject *returnDivider = PyObject_CallObject(op_Divider::PyOpDividerFromStrS, pyTupleArgs);
    if(returnDivider == NULL){
        cout << "Error al llamar a la funcion de renderizado" << endl;
        return nullptr;
    }

    op_Divider *toRet = new op_Divider(returnDivider);
    return toRet;
    while(Py_REFCNT(returnDivider) > 0) Py_DecRef(returnDivider);
    while(Py_REFCNT(pyTupleArgs) > 0) Py_DecRef(pyTupleArgs);
    while(Py_REFCNT(pyStrOp) > 0) Py_DecRef(pyStrOp);

    return nullptr;
}



void _pyOperations::pySetUp(std::string fName)
{
    using namespace std;

    Py_Initialize();
    wchar_t *pyArgv[1];
    string filename = fName;
    string currentWDir = GetCurrentWorkingDir();

    string argv1 = GetCurrentWorkingDir() + "\\" + filename + ".py";
    pyArgv[0] = new wchar_t[argv1.size()+1];
    mbstowcs(pyArgv[0],argv1.c_str(),argv1.size()+1);
    PyObject *pyPathObj = PySys_GetObject("path");

    if(pyPathObj == NULL || !PyList_Check(pyPathObj)){
        std::cout << "Fallo\n";
        if (PyErr_Occurred()) PyErr_Print();
    }

    PyObject *pNewPath = PyUnicode_DecodeFSDefault(currentWDir.c_str());
    int retAdd = PyList_Append(pyPathObj, pNewPath);
    if (retAdd != 0){
        std::cout << "Fallo\n";
        if (PyErr_Occurred()) PyErr_Print();
    }
    int retSysPathSet = PySys_SetObject("path", pyPathObj);
    if (retSysPathSet != 0){
        std::cout << "Fallo\n";
        if (PyErr_Occurred()) PyErr_Print();
    }

    PySys_SetArgv(1,pyArgv);

    Py_DecRef(pNewPath);
    PyObject *strModName = PyUnicode_FromString(fName.c_str());
    op_Divider::PyModuleS = PyImport_Import(strModName);
    while (Py_REFCNT(strModName) > 0) Py_DecRef(strModName);
    if (op_Divider::PyModuleS == nullptr){
        cout << "Error al importar Modulo" << endl;
    }

    op_Divider::PyRenderOpS = PyObject_GetAttrString(op_Divider::PyModuleS, "render_fstr");
    if(op_Divider::PyRenderOpS == nullptr || !PyCallable_Check(op_Divider::PyRenderOpS)){
        cout << "Error al importar PyRenderLater" << endl;
    }

    op_Divider::PyOpDividerS = PyObject_GetAttrString(op_Divider::PyModuleS, "op_Divider");
    if(op_Divider::PyOpDividerS == nullptr || !PyCallable_Check(op_Divider::PyOpDividerS)){
        cout << "Error al importar PyOpDivider" << endl;
    }

    op_Divider::PyMakeExpS = PyObject_GetAttrString(op_Divider::PyModuleS, "makeExpresion");
    if(op_Divider::PyMakeExpS == nullptr || !PyCallable_Check(op_Divider::PyMakeExpS)){
        cout << "Error al importar PyMakeExpression" << endl;
    }

    op_Divider::PyOpDividerFromStrS = PyObject_GetAttrString(op_Divider::PyModuleS, "opFromStr");
    if(op_Divider::PyOpDividerFromStrS == nullptr || !PyCallable_Check(op_Divider::PyOpDividerFromStrS)){
        cout << "Error al importar PyMakeExpression" << endl;
    }


}

std::string _pyOperations::GetCurrentWorkingDir()
{
    std::string cwd("\0",FILENAME_MAX+1);
    return getcwd(&cwd[0],cwd.capacity());
}



void _pyOperations::renderLatexFormula(MathOperand &op, std::string fName){
    using namespace std;
    string strOp = op.getStringOp();

    PyObject *pyStrOp = PyUnicode_FromString(strOp.c_str());
    PyObject *pyStrFName = PyUnicode_FromString(fName.c_str());
    if(pyStrOp == NULL || pyStrFName == NULL){
        cout << "Error al crear strings unicodes" << endl;
        return;
    }

    PyObject *pyTupleArgs = PyTuple_New(2);
    if(pyTupleArgs == NULL){
        cout << "Error al crear Tupla de argumentos" << endl;
        return;
    }

    int rA0 = PyTuple_SetItem(pyTupleArgs, 0, pyStrOp);
    int rA1 =PyTuple_SetItem(pyTupleArgs, 1, pyStrFName);
    if(rA0 != 0 || rA1 != 0){
        cout << "Error al llenar argumentos" << endl;
        return;
    }

    PyObject *returnRender = PyObject_CallObject(op_Divider::PyRenderOpS, pyTupleArgs);
    if(returnRender == NULL){
        cout << "Error al llamar a la funcion de renderizado" << endl;
        return;
    }


    return;
}

void _pyOperations::deleteTmp()
{
    PyRun_SimpleString("import shutil\nshutil.rmtree(\"tmp\")");
}
