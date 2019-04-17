#ifndef MATHFINALOPERANDS_H
#define MATHFINALOPERANDS_H

#include "mathoperand.h"



class MathVariable : public MathOperand
{
public:
    MathVariable(unsigned int id);

    double evaluateExpression(std::vector<double> &arguments) const override;

    void printExpression(std::vector<double> &arguments, std::ostream &buff = std::cout) const override;

    void printExpression(std::ostream &buff = std::cout) const override;

    unsigned int getId() const;

private:
    unsigned int id;

};

class MathConstant : public MathOperand
{
public:
    MathConstant(double value);

    double evaluateExpression(std::vector<double> &arguments) const override {return value;}

    void printExpression(std::vector<double> &arguments, std::ostream &buff = std::cout) const override {buff << value << " ";}

    void printExpression(std::ostream &buff = std::cout) const override {buff << value << " ";}

    MathConstant& operator=(double val){
        this->value = val;
        return *this;
    }


    double getValue() const;

private:
    double value;
};



#endif // MATHFINALOPERANDS_H
