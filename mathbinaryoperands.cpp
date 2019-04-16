#include "mathbinaryoperands.h"
#include "mathfinaloperands.h"

MathBinaryOperand::MathBinaryOperand(MathOperand const *arg1, MathOperand const *arg2)
{

    arguments.clear();
    arguments.push_back(arg1);
    arguments.push_back(arg2);
}

void MathBinaryOperand::setStringRep(const std::string &value)
{
    stringRep = value;
}

MathAddOperator::MathAddOperator(MathOperand const *arg1, MathOperand const *arg2): MathBinaryOperand (arg1, arg2)
{
    setOp_Type(MathOperand::op_Add);
    setStringRep("+ ");
    return;
}

double MathAddOperator::evaluateExpression(std::vector<double> &arguments) const
{
    return this->arguments[0]->evaluateExpression(arguments) + this->arguments[1]->evaluateExpression(arguments);
}

void MathBinaryOperand::printExpression(std::vector<double> &arguments, std::ostream &buff) const
{
    buff << this->arguments[0] << stringRep << this->arguments[1];
}

void MathBinaryOperand::printExpression(std::ostream &buff) const
{
    MathOperand::typeEnum arg0Type = this->arguments[0]->getOp_Type();
    MathOperand::typeEnum arg1Type = this->arguments[1]->getOp_Type();

    if(this->getOp_Type() == MathOperand::op_Mult){
        if(arg0Type == MathOperand::op_Const){
            const MathConstant *cons = dynamic_cast<const MathConstant *>(this->arguments[0]);
            if(cons->getValue() == -1){
                buff << "-" << this->arguments[1];
                return;
            }
        }

        if(arg1Type == MathOperand::op_Const){
            const MathConstant *cons = dynamic_cast<const MathConstant *>(this->arguments[1]);
            if(cons->getValue() == -1){
                buff << "-" << this->arguments[0];
                return;
            }
        }
    }

    std::string strFix[4];
    for (int i = 0;i != 4;i++) {
        strFix[i] = "";
    }
    if(arg0Type != MathOperand::op_Const && arg0Type != MathOperand::op_Var){
        strFix[0] = "(";
        strFix[1] = "\b) ";
    }
    if(arg1Type != MathOperand::op_Const && arg1Type != MathOperand::op_Var){
        strFix[2] = "(";
        strFix[3] = "\b) ";
    }
        buff << strFix[0] << this->arguments[0] << strFix[1] << stringRep << strFix[2] << this->arguments[1] << strFix[3];
}
MathSubsOperator::MathSubsOperator(MathOperand const *arg1, MathOperand const *arg2): MathBinaryOperand (arg1, arg2)
{
    setOp_Type(MathOperand::op_Subs);
    setStringRep("- ");
    return;
}

double MathSubsOperator::evaluateExpression(std::vector<double> &arguments) const
{
    return this->arguments[0]->evaluateExpression(arguments) - this->arguments[1]->evaluateExpression(arguments);
}

MathMultOperator::MathMultOperator(MathOperand const *arg1, MathOperand const *arg2): MathBinaryOperand (arg1, arg2)
{
    setOp_Type(MathOperand::op_Mult);
    setStringRep("* ");
    return;
}

double MathMultOperator::evaluateExpression(std::vector<double> &arguments) const
{
    return this->arguments[0]->evaluateExpression(arguments) * this->arguments[1]->evaluateExpression(arguments);
}

MathDivOperator::MathDivOperator(MathOperand const *arg1, MathOperand const *arg2): MathBinaryOperand (arg1, arg2)
{
    setOp_Type(MathOperand::op_Div);
    setStringRep("/ ");
    return;
}

double MathDivOperator::evaluateExpression(std::vector<double> &arguments) const
{
    double val2 = this->arguments[1]->evaluateExpression(arguments);
    if (val2 == 0)
        throw "Division by 0";
    return this->arguments[0]->evaluateExpression(arguments) / val2;
}

MathOperand &operator+(MathOperand &operand0, const MathOperand &operand1)
{
    MathAddOperator *ne = new MathAddOperator(&operand0, &operand1);
    return *ne;
}

MathOperand &operator-(MathOperand &operand0, const MathOperand &operand1)
{
    MathSubsOperator *ne = new MathSubsOperator(&operand0, &operand1);
    return *ne;
}

MathOperand &operator/(MathOperand &operand0, const MathOperand &operand1)
{
    MathDivOperator *ne = new MathDivOperator(&operand0, &operand1);
    return *ne;
}

MathOperand &operator*(MathOperand &operand0, const MathOperand &operand1)
{
    MathMultOperator *ne = new MathMultOperator(&operand0, &operand1);
    return *ne;
}

MathOperand &operator-(const MathOperand &operand0){
    MathConstant *minus = new MathConstant(-1);
    MathMultOperator *negative = new MathMultOperator(minus,&operand0);
    return *negative;
}
