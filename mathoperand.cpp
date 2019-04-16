#include "mathoperand.h"

MathOperand::MathOperand()
{

}

MathOperand::typeEnum MathOperand::getOp_Type() const
{
    return op_Type;
}

void MathOperand::setOp_Type(const MathOperand::typeEnum &value)
{
    op_Type = value;
}
