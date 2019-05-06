#ifndef MATHUNARYOPERANDS_H
#define MATHUNARYOPERANDS_H
#include "mathoperand.h"
#include "mathbinaryoperands.h"

class MathUnaryOperands : public MathOperand
{
public:
    MathUnaryOperands(MathOperand const *arg1);

    // MathOperand interface
public:
    void printExpression(std::vector<double> &arguments, std::ostream &buff) const{return;}
    void printExpression(std::ostream &buff = std::cout) const;
    void printExpressionP(std::ostream &buff) const;
    std::tuple<int, int, int, int> drawExpression(ModelViewPrimitives *primitivesReference) const;
    std::string getStringOp() const override;
protected:
    std::string strRep;
};

class MathExpOperand : public MathPowerOperator
{
public:
    MathExpOperand(MathOperand const *arg);

    std::tuple<int,int,int,int> drawExpression(ModelViewPrimitives *primitivesReference = nullptr) const override;




    // MathOperand interface
public:
    std::string getStringOp() const override
    {
        std::string str = "exp(" + arguments[1]->getStringOp() + ")";
        return str;
    }
};

class MathSinOperand : public MathUnaryOperands
{
public:
    MathSinOperand(MathOperand const *arg1);

    // MathOperand interface
public:
    double evaluateExpression(std::vector<double> &arguments) const;
};

class MathCosOperand : public MathUnaryOperands
{
public:
    MathCosOperand(MathOperand const *arg1);

    // MathOperand interface
public:
    double evaluateExpression(std::vector<double> &arguments) const;
};

class MathTgOperand : public MathUnaryOperands
{
public:
    MathTgOperand(MathOperand const *arg1);

    // MathOperand interface
public:
    double evaluateExpression(std::vector<double> &arguments) const;
};

class MathLnOperand : public MathUnaryOperands
{
public:
    MathLnOperand(MathOperand const *arg1);

    // MathOperand interface
public:
    double evaluateExpression(std::vector<double> &arguments) const;
};

#endif // MATHUNARYOPERANDS_H
