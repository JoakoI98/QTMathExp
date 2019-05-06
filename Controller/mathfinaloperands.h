#ifndef MATHFINALOPERANDS_H
#define MATHFINALOPERANDS_H



#include "mathoperand.h"



class MathVariable : public MathOperand
{
public:
    MathVariable(unsigned int id, std::string _s = "");

    double evaluateExpression(std::vector<double> &arguments) const override;

    void printExpression(std::vector<double> &arguments, std::ostream &buff = std::cout) const override;

    void printExpression(std::ostream &buff = std::cout) const override;

    void printExpressionP(std::ostream &buff) const override;

    std::tuple<int,int,int,int> drawExpression(ModelViewPrimitives *primitivesReference = nullptr) const override;

    unsigned int getId() const;

    std::string getStringOp() const override;

private:
    unsigned int id;

    std::string _symbol;

};

class MathConstant : public MathOperand
{
public:
    MathConstant(double value);

    double evaluateExpression(std::vector<double> &arguments) const override {return value;}

    void printExpression(std::vector<double> &arguments, std::ostream &buff = std::cout) const override {buff << value << " ";}

    void printExpression(std::ostream &buff = std::cout) const override {buff << value << " ";}
    void printExpressionP(std::ostream &buff) const override {buff << value << " ";}

    std::tuple<int,int,int,int> drawExpression(ModelViewPrimitives *primitivesReference = nullptr) const override;

    MathConstant& operator=(double val){
        this->value = val;
        return *this;
    }


    double getValue() const;

    std::string getStringOp() const override;

private:
    double value;
};



#endif // MATHFINALOPERANDS_H
