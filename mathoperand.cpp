#include "mathoperand.h"

MathOperand::MathOperand()
{

}

MathOperand::typeEnum MathOperand::getOp_Type() const
{
    return op_Type;
}

std::ostream &operator<<(std::ostream &os, const MathOperand &operand)
{
    operand.printExpression(os);
    return os;
}

std::ostream &operator<<(std::ostream &os, const MathOperand *operand)
{
    operand->printExpression();
    return os;
}




MathOperand::~MathOperand()
{
    for (auto x : arguments) {
        delete x;
    }
}

void MathOperand::setOp_Type(const MathOperand::typeEnum &value)
{
    op_Type = value;
}
