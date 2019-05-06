#ifndef MATHOPERAND_H
#define MATHOPERAND_H

#include <vector>

#include <iostream>

#include "../ModelView/modelviewprimitives.h"



class MathOperand
{
public:
    MathOperand();
    enum typeEnum {op_Add, op_Subs, op_Mult, op_Div, op_Power, op_Root, op_Const, op_Var, op_Equ, op_Other};
    typeEnum getType();

    typeEnum getOp_Type() const;
    virtual double evaluateExpression(std::vector<double> &arguments) const = 0;


    virtual void printExpression(std::vector<double> &arguments, std::ostream &buff = std::cout) const = 0;

    virtual void printExpression(std::ostream &buff = std::cout) const = 0;
    virtual void printExpressionP(std::ostream &buff) const = 0;

    virtual std::tuple<int,int,int,int> drawExpression(ModelViewPrimitives *primitivesReference = nullptr) const{
        if(ModelView == nullptr && primitivesReference == nullptr) throw "Not link with view";
        return std::tuple<int, int, int, int>(0,0,0,0);
    }

    std::tuple<int,int,int,int> getSize(ModelViewPrimitives *primitivesReference = nullptr) const;


    virtual std::string getStringOp() const = 0;

    friend std::ostream& operator<<(std::ostream& os, const MathOperand& operand);

    friend std::ostream& operator<<(std::ostream& os, const MathOperand* operand);

    friend MathOperand &operator+(MathOperand &operand0, const MathOperand &operand1);

    friend MathOperand &operator-(MathOperand &operand0, const MathOperand &operand1);

    friend MathOperand &operator/(MathOperand &operand0, const MathOperand &operand1);

    friend MathOperand &operator*(MathOperand &operand0, const MathOperand &operand1);

    friend MathOperand &operator^(MathOperand &operand0, const MathOperand &operand1);


    friend MathOperand &operator-(const MathOperand &operand0);

    ModelViewPrimitives *getModelView() const;
    void setModelView(ModelViewPrimitives *value);

    virtual ~MathOperand();






protected:
    void setOp_Type(const typeEnum &value);

    std::vector<const MathOperand *> arguments;

    ModelViewPrimitives *ModelView = nullptr;

private:
    typeEnum op_Type;

};


#endif // MATHOPERAND_H
