#include "mathfinaloperands.h"

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
