#include "mathfinaloperands.h"


MathVariable::MathVariable(unsigned int id): id(id)
{
    setOp_Type(MathOperand::op_Var);
    return;
}

double MathVariable::evaluateExpression(std::vector<double> &arguments) const
{
    if(id >= arguments.size())
        throw "Variable not set";
    return arguments[id];
}

void MathVariable::printExpression(std::vector<double> &arguments, std::ostream &buff) const
{
    if(id >= arguments.size())
        throw "Variable not set";
    buff << arguments[id] << " ";
    return;
}

void MathVariable::printExpression(std::ostream &buff) const
{
    buff << "x" << id << " ";
    return;
}

void MathVariable::drawExpression() const
{
    MathOperand::drawExpression();
    ModelView->drawPointerText("x" + std::to_string(id) + " ");
}

unsigned int MathVariable::getId() const
{
    return id;
}

MathConstant::MathConstant(double value): value(value)
{
    setOp_Type(MathOperand::op_Const);
    return;
}

void MathConstant::drawExpression() const
{
    MathOperand::drawExpression();
    ModelView->drawPointerText(std::to_string(value) + " ");
}

double MathConstant::getValue() const
{
    return value;
}




