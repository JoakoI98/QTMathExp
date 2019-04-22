#include "_pythoncontroller.h"
#include <iostream>
#include "literalsdefinitions.cpp"
#include <algorithm>

_pythonController::_pythonController()
{
    Py_Initialize();
    return;
}

void _pythonController::prtNewStr(string _strParse)
{
    using namespace std;
    const char file_Name[] = "_pyParser";


    PyObject *pName = PyUnicode_DecodeFSDefault(file_Name);
    PyObject *pModule = PyImport_Import(pName);
    if(pModule == NULL) {
        cout << "Fallo al importar el modulo\n";
        if (PyErr_Occurred()) PyErr_Print();
        return;
    }

    PyObject *pClass = PyObject_GetAttrString(pModule, "op_Divider");
    if(pClass == NULL || !PyCallable_Check(pClass) ) {
        std::cout << "Fallo al obtener la clase, o esta no es ejecutable\n";
        if (PyErr_Occurred()) PyErr_Print();
        return;
    }

    PyObject *pParseExpF = PyObject_GetAttrString(pModule, "makeExpresion");
    if(pParseExpF == NULL || !PyCallable_Check(pParseExpF) ) {
        std::cout << "Fallo\n";
        if (PyErr_Occurred()) PyErr_Print();
    }

    PyObject *pStrParse = PyUnicode_FromString(_strParse.c_str());
    PyObject *pyTuble_Args0 = PyTuple_New(1);
    PyTuple_SetItem(pyTuble_Args0, 0, pStrParse);
    PyObject *pySympyObj = PyObject_CallObject(pParseExpF,pyTuble_Args0);
    if(pySympyObj == NULL) {
        cout << "Error al llamar a la funcion parse_exp\n";
        return;
    }

    PyObject *pyTuble_Args1 = PyTuple_New(1);
    PyTuple_SetItem(pyTuble_Args1, 0, pySympyObj);
    PyObject *pyOp_Divider = PyObject_CallObject(pClass,pyTuble_Args1);
    if(!pyOp_Divider){
        cout << "Error al cargar pyopDivider\n";
        return;
    }

    op_Divider divider = _pyObjectToDivider(pyOp_Divider);


    divider.printStr();
}

_pythonController::~_pythonController()
{
    Py_Finalize();
}

_pythonController::op_Divider &_pythonController::_pyObjectToDivider(PyObject *_pyObject)
{
    op_Divider *newDivider = new op_Divider(_pyObject);
    return *newDivider;
}

MathOperand &_pythonController::_classConverterAdd(_pythonController::op_Divider divider)
{
    MathOperand &ret = divider.args[0]->convertMathOperand() + divider.args[1]->convertMathOperand();
    return ret;
}

MathOperand &_pythonController::_classConverterSubs(_pythonController::op_Divider divider)
{
    MathOperand &ret = divider.args[0]->convertMathOperand() - divider.args[1]->convertMathOperand();
    return ret;
}

MathOperand &_pythonController::_classConverterMult(_pythonController::op_Divider divider)
{
    MathOperand &ret = divider.args[0]->convertMathOperand() * divider.args[1]->convertMathOperand();
    return ret;
}

MathOperand &_pythonController::_classConverterDiv(_pythonController::op_Divider divider)
{
    MathOperand &ret = divider.args[0]->convertMathOperand() / divider.args[1]->convertMathOperand();
    return ret;
}

MathOperand &_pythonController::_classConverterSin(_pythonController::op_Divider divider)
{
    MathOperand &ret = _sin(divider.args[0]->convertMathOperand());
    return ret;
}

MathOperand &_pythonController::_classConverterLn(_pythonController::op_Divider divider)
{
    MathOperand &ret = _ln(divider.args[0]->convertMathOperand());
    return ret;
}

MathOperand &_pythonController::_classConverterPow(_pythonController::op_Divider divider)
{
    MathOperand &ret = divider.args[0]->convertMathOperand() ^ divider.args[1]->convertMathOperand();
    return  ret;
}

MathOperand &_pythonController::_classConverterExp(_pythonController::op_Divider divider)
{
    MathOperand &ret = _exp(divider.args[0]->convertMathOperand());
    return ret;
}






void _pythonController::op_Divider::printStr()
{
    cout << _strRep << '(';
    if(_strRep == "Constant")
        cout << this->_value;
    else if(_strRep == "Symbol")
        cout << this->_symbol;
    else{
        for(op_Divider *element : args)
            element->printStr();
    }

    cout << ")  ";

}

_pythonController::op_Divider::op_Divider(PyObject *obj)
{
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
        return;
    }



    if(!PyList_Check(_pyArgs)) throw "args's pyobject is not list";
    for (unsigned int i = 0; i != argsNumber; i++){
        PyObject *currentPyObject = PyList_GetItem(_pyArgs, i);
        op_Divider *currentDivider = new op_Divider(currentPyObject);
        args.push_back(currentDivider);
    }
}

_pythonController::op_Divider::~op_Divider()
{
    for(op_Divider *element : args) delete element;
}




MathOperand &_pythonController::_classConverterConstant(_pythonController::op_Divider divider)
{
    MathConstant *c = new MathConstant(divider._value);
    return *c;
}

MathOperand &_pythonController::_classConverterSymbol(_pythonController::op_Divider divider)
{
    MathVariable *v;

    vector<string>::iterator it = find(symbolTable.begin(),symbolTable.end(), divider._symbol);
    if(it == symbolTable.end()){
        symbolTable.push_back(divider._symbol);
        unsigned int id = symbolTable.size() - 1;
        v = new MathVariable(id);
    } else{
        unsigned int id = it - symbolTable.begin();
        v = new MathVariable(id);
    }
    return *v;
}
