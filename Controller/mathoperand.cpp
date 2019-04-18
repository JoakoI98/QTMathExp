#include "mathoperand.h"
#include <exception>


MathOperand::MathOperand()
{

}

MathOperand::typeEnum MathOperand::getOp_Type() const
{
    return op_Type;
}

std::tuple<int, int, int, int> MathOperand::getSize() const
{
    if(ModelView == nullptr) throw "Not linked view, or trying to get size of not mother expresion";

    ModelView->setSeeing(false);

    std::pair<int,int> pointer = ModelView->getPointer();
    std::tuple<int, int, int> bkgColor = ModelView->getBkgColor();
    std::tuple<int, int, int> txtColor = ModelView->getTextColor();
    std::tuple<int, int, int> lineColor = ModelView->getLineColor();
    int txtSize = ModelView->getTextSize();
    int lineSize = ModelView->getLineSize();

    std::tuple<int, int, int, int> rect = drawExpression();

    ModelView->setPointer(pointer);
    ModelView->setBkgColor(bkgColor);
    ModelView->setTextColor(txtColor);
    ModelView->setLineColor(lineColor);
    ModelView->setTextSizeNF(txtSize);
    ModelView->setLineSize(lineSize);

    ModelView->setSeeing(true);

    return rect;
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

ModelViewPrimitives *MathOperand::getModelView() const
{
    return ModelView;
}

void MathOperand::setModelView(ModelViewPrimitives *value)
{
    ModelView = value;
}
