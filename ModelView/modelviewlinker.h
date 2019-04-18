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
    std::tuple<int, int, int, int> sendDraw();
    std::tuple<int, int, int, int> getSize();
    void link(MathOperand *exp);
    bool isLinked();


private:
    MathOperand *linkedExp = nullptr;
    ModelViewPrimitives *primitives;
    bool readyToDraw = false;
};

#endif // MODELVIEWLINKER_H
