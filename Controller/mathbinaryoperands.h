#ifndef MATHBINARYOPERANDS_H
#define MATHBINARYOPERANDS_H
#include "mathoperand.h"

class MathBinaryOperand : public MathOperand
{
public:
    MathBinaryOperand(MathOperand const *arg1, MathOperand const *arg2);

    void printExpression(std::vector<double> &arguments, std::ostream &buff = std::cout) const override;

    void printExpression(std::ostream &buff = std::cout) const override;

    virtual void drawThis(ModelViewPrimitives *primitivesReference = nullptr) const = 0;

    std::tuple<int,int,int,int> drawExpression(ModelViewPrimitives *primitivesReference = nullptr) const override;

protected:
    void setStringRep(const std::string &value);

private:
    std::string stringRep;
};



class MathAddOperator : public MathBinaryOperand
{
public:
    MathAddOperator(MathOperand const *arg1, MathOperand const *arg2);

    double evaluateExpression(std::vector<double> &arguments) const override;



    void drawThis(ModelViewPrimitives *primitivesReference = nullptr) const override;
};

class MathSubsOperator : public MathBinaryOperand
{
public:
    MathSubsOperator(MathOperand const *arg1, MathOperand const *arg2);

    double evaluateExpression(std::vector<double> &arguments) const override;

    void drawThis(ModelViewPrimitives *primitivesReference = nullptr) const override;
};

class MathMultOperator : public MathBinaryOperand
{
public:
    MathMultOperator(MathOperand const *arg1, MathOperand const *arg2);

    double evaluateExpression(std::vector<double> &arguments) const override;

    void drawThis(ModelViewPrimitives *primitivesReference = nullptr) const override;
};

class MathDivOperator : public MathBinaryOperand
{
public:
    MathDivOperator(MathOperand const *arg1, MathOperand const *arg2);

    double evaluateExpression(std::vector<double> &arguments) const override;

    std::tuple<int,int,int,int> drawExpression(ModelViewPrimitives *primitivesReference = nullptr) const override;

    void drawThis(ModelViewPrimitives *primitivesReference = nullptr) const override {return;}

};



#endif // MATHBINARYOPERANDS_H
