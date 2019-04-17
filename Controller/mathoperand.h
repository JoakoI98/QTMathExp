#ifndef MATHOPERAND_H
#define MATHOPERAND_H

#include <vector>

#include <iostream>

#include "../ModelView/modelviewprimitives.h"


class MathOperand
{
public:
    MathOperand();
    enum typeEnum {op_Add, op_Subs, op_Mult, op_Div, op_Const, op_Var};
    typeEnum getType();

    typeEnum getOp_Type() const;
    virtual double evaluateExpression(std::vector<double> &arguments) const = 0;


    virtual void printExpression(std::vector<double> &arguments, std::ostream &buff = std::cout) const = 0;

    virtual void printExpression(std::ostream &buff = std::cout) const = 0;

    virtual void drawExpression() const = 0;

    friend std::ostream& operator<<(std::ostream& os, const MathOperand& operand);

    friend std::ostream& operator<<(std::ostream& os, const MathOperand* operand);

    friend MathOperand &operator+(MathOperand &operand0, const MathOperand &operand1);

    friend MathOperand &operator-(MathOperand &operand0, const MathOperand &operand1);

    friend MathOperand &operator/(MathOperand &operand0, const MathOperand &operand1);

    friend MathOperand &operator*(MathOperand &operand0, const MathOperand &operand1);

    friend MathOperand &operator-(const MathOperand &operand0);

    virtual ~MathOperand();
protected:
    void setOp_Type(const typeEnum &value);

    std::vector<const MathOperand *> arguments;

    ModelViewPrimitives *ModelView;

private:
    typeEnum op_Type;
};


#endif // MATHOPERAND_H
