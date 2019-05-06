#ifndef LITERALS_H
#define LITERALS_H
#include "mathbinaryoperands.h"
#include "mathfinaloperands.h"
#include "mathunaryoperands.h"

MathConstant &operator"" _c(long double val){
    MathConstant *newConstant = new MathConstant(static_cast<double>(val));
    return *newConstant;
}

MathConstant &operator"" _c(unsigned long long val){
    MathConstant *newConstant = new MathConstant(static_cast<double>(val));
    return *newConstant;
}

MathVariable &operator"" _v(unsigned long long id){
    MathVariable *newVariable = new MathVariable(static_cast<unsigned int>(id));
    return *newVariable;
}

MathExpOperand &operator"" _e(unsigned long long id){
    MathConstant *newConstant = new MathConstant(static_cast<unsigned int>(id));
    MathExpOperand *newExp = new MathExpOperand(newConstant);
    return *newExp;
}

MathExpOperand &operator"" _e(long double val){
    MathConstant *newConstant = new MathConstant(val);
    MathExpOperand *newExp = new MathExpOperand(newConstant);
    return *newExp;
}

MathRootrOperator &sroot(MathOperand &op){
    MathRootrOperator *newRoot = new MathRootrOperator(&2_c, &op);
    return *newRoot;
}

MathSinOperand &_sin(MathOperand &op){
    MathSinOperand *newSin = new MathSinOperand(&op);
    return *newSin;
}

MathCosOperand &_cos(MathOperand &op){
    MathCosOperand *newCos = new MathCosOperand(&op);
    return *newCos;
}

MathTgOperand &_tg(MathOperand &op){
    MathTgOperand *newTg = new MathTgOperand(&op);
    return *newTg;
}

MathLnOperand &_ln(MathOperand &op){
    MathLnOperand *newLn = new MathLnOperand(&op);
    return *newLn;
}

MathExpOperand &_exp(MathOperand &op){
    MathExpOperand *newExp = new MathExpOperand(&op);
    return  *newExp;
}

MathOperand &_Equals(MathOperand &_izq, MathOperand &_der){
    MathEquals *newEq = new MathEquals(&_izq, &_der);
    return *newEq;
}


#endif
