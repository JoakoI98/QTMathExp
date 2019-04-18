#include "modelviewlinker.h"

ModelViewLinker::ModelViewLinker(ModelViewPrimitives *primitives) : primitives(primitives)
{

}

bool ModelViewLinker::getReadyToDraw() const
{
    return readyToDraw;
}

void ModelViewLinker::setReadyToDraw(bool value)
{
    readyToDraw = value;
}

std::tuple<int, int, int, int> ModelViewLinker::sendDraw()
{
    if(linkedExp == nullptr) throw "Not linked expression";
    return linkedExp->drawExpression();
}

std::tuple<int, int, int, int> ModelViewLinker::getSize()
{
    if(linkedExp == nullptr) throw "Not linked expression";
    return linkedExp->getSize();
}

void ModelViewLinker::link(MathOperand *exp)
{
    this->linkedExp = exp;
    this->linkedExp->setModelView(primitives);
}

bool ModelViewLinker::isLinked()
{
    return linkedExp == nullptr ? false: true;
}
