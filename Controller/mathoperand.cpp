#include "mathoperand.h"
#include <exception>


MathOperand::MathOperand()
{

}

MathOperand::typeEnum MathOperand::getOp_Type() const
{
    return op_Type;
}

std::tuple<int, int, int, int> MathOperand::getSize(ModelViewPrimitives *primitivesReference) const
{
    ModelViewPrimitives *__ModelView = primitivesReference;
    if(primitivesReference == nullptr) __ModelView = ModelView;

    bool oldSeeing = __ModelView->getSeeing();
    bool oldGettingSize = __ModelView->getGetingSize();
    __ModelView->setSeeing(false);
    __ModelView->setGetingSize(true);

    std::pair<int,int> pointer = __ModelView->getPointer();
    std::tuple<int, int, int> bkgColor = __ModelView->getBkgColor();
    std::tuple<int, int, int> txtColor = __ModelView->getTextColor();
    std::tuple<int, int, int> lineColor = __ModelView->getLineColor();
    int txtSize = __ModelView->getTextSize();
    int lineSize = __ModelView->getLineSize();

    std::tuple<int, int, int, int> rect = drawExpression(__ModelView);

    __ModelView->setPointer(pointer);
    __ModelView->setBkgColor(bkgColor);
    __ModelView->setTextColor(txtColor);
    __ModelView->setLineColor(lineColor);
    __ModelView->setTextSizeNF(txtSize);
    __ModelView->setLineSize(lineSize);

    __ModelView->setSeeing(oldSeeing);
    __ModelView->setGetingSize(oldGettingSize);

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
