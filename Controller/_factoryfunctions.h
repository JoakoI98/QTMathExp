#ifndef _FACTORYFUNCTIONS_H
#define _FACTORYFUNCTIONS_H
#include "mathoperand.h"
#include "_mathoperandfactory.h"

namespace _functionFactory {

template<class T>
MathOperand &_bynaryCreator(_MathArg_ *arg){
    MathOperand *newOp = new T(arg->arg0, arg->arg1);
    return *newOp;
}

template<class T>
MathOperand &_unaryCreator(_MathArg_ *arg){
    MathOperand *newOp = new T(arg->arg);
    return *newOp;
}

MathOperand &_constCreator(_MathArg_ *arg){
    MathOperand *newConst = new MathConstant(arg->value);
    return *newConst;
}

MathOperand &_varCreator(_MathArg_ *arg){
    MathOperand *newVar = new MathVariable(arg->id, arg->_sym);
    return  *newVar;
}


}
#endif // _FACTORYFUNCTIONS_H
