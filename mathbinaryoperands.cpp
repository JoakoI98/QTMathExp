#include "mathbinaryoperands.h"
#include "mathfinaloperands.h"

MathBinaryOperand::MathBinaryOperand(MathOperand *arg1, MathOperand *arg2)
{

    arguments.clear();
    arguments.push_back(arg1);
    arguments.push_back(arg2);
}

void MathBinaryOperand::setStringRep(const std::string &value)
{
    stringRep = value;
}

MathAddOperator::MathAddOperator(MathOperand *arg1, MathOperand *arg2): MathBinaryOperand (arg1, arg2)
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
MathSubsOperator::MathSubsOperator(MathOperand *arg1, MathOperand *arg2): MathBinaryOperand (arg1, arg2)
{
    setOp_Type(MathOperand::op_Subs);
    setStringRep("- ");
    return;
}

double MathSubsOperator::evaluateExpression(std::vector<double> &arguments) const
{
    return this->arguments[0]->evaluateExpression(arguments) - this->arguments[1]->evaluateExpression(arguments);
}

MathMultOperator::MathMultOperator(MathOperand *arg1, MathOperand *arg2): MathBinaryOperand (arg1, arg2)
{
    setOp_Type(MathOperand::op_Mult);
    setStringRep("* ");
    return;
}

double MathMultOperator::evaluateExpression(std::vector<double> &arguments) const
{
    return this->arguments[0]->evaluateExpression(arguments) * this->arguments[1]->evaluateExpression(arguments);
}

MathDivOperator::MathDivOperator(MathOperand *arg1, MathOperand *arg2): MathBinaryOperand (arg1, arg2)
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
