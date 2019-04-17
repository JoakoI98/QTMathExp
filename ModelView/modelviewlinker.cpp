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

void ModelViewLinker::sendDraw()
{
    if(linkedExp == nullptr) throw "Not linked expression";
    linkedExp->drawExpression();
}

void ModelViewLinker::link(MathOperand *exp)
{
    this->linkedExp = exp;
    this->linkedExp->setModelView(primitives);
}

bool ModelViewLinker::isLinked()
{
    if(linkedExp == nullptr) std::cout << "Link fallido" << std::endl;
    else std::cout << "Link correcto" << std::endl;
    return linkedExp == nullptr ? false: true;
}
