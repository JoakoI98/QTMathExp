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

int ModelViewLinker::txtSizeFromHeight(int height)
{
    int x0, x1, y0, y1;
    std::tie(x0,y0,x1,y1) = getSize();
    int fz = primitives->getTextSize();
    if(abs(y1-y0) < height){

        do {
            primitives->setTextSizeNF(fz);
            std::tie(x0,y0,x1,y1) = getSize();
            fz++;
            std::cout << "real: " << abs(y1-y0) << " buscado: " << height << std::endl;

        } while (abs(height - abs(y1-y0)) >=3);
    }
    return fz;
}
