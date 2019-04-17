#ifndef MODELVIEWLINKER_H
#define MODELVIEWLINKER_H
#include "../Controller/mathoperand.h"
#include "modelviewprimitives.h"

class ModelViewLinker
{
public:
    ModelViewLinker(ModelViewPrimitives *primitives);

    bool getReadyToDraw() const;
    void setReadyToDraw(bool value);
    void sendDraw();
    void link(MathOperand *exp);
    bool isLinked();

private:
    MathOperand *linkedExp = nullptr;
    ModelViewPrimitives *primitives;
    bool readyToDraw = false;
};

#endif // MODELVIEWLINKER_H
