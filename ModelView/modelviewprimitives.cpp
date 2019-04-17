#include "modelviewprimitives.h"

#define DefaultBkgColor 0,0,0
#define DefaultLineColor 0,0,0
#define DefaultTextColor 0,0,0
#define DefaultTextSize 1

ModelViewPrimitives::ModelViewPrimitives()
{
    setPointer(0,0);
    setBkgColor(std::tuple<int,int,int>(DefaultBkgColor));
    setLineColor(std::tuple<int,int,int>(DefaultLineColor));
    setTextColor(std::tuple<int,int,int>(DefaultTextColor));
    setTextSize(DefaultTextSize);
}

std::pair<int, int> ModelViewPrimitives::getPointer() const
{
    return pointer;
}

void ModelViewPrimitives::setPointer(const std::pair<int, int> &value)
{
    pointer = value;
}

void ModelViewPrimitives::setPointer(int x, int y)
{
    pointer = {x,y};
}

std::tuple<int, int, int> ModelViewPrimitives::getLineColor() const
{
    return lineColor;
}

void ModelViewPrimitives::setLineColor(const std::tuple<int, int, int> &value)
{
    lineColor = value;
}

std::tuple<int, int, int> ModelViewPrimitives::getTextColor() const
{
    return textColor;
}

void ModelViewPrimitives::setTextColor(const std::tuple<int, int, int> &value)
{
    textColor = value;
}

std::tuple<int, int, int> ModelViewPrimitives::getBkgColor() const
{
    return bkgColor;
}

void ModelViewPrimitives::setBkgColor(const std::tuple<int, int, int> &value)
{
    bkgColor = value;
}

int ModelViewPrimitives::getTextSize() const
{
    return textSize;
}

void ModelViewPrimitives::setTextSize(int value)
{
    textSize = value;
}

int ModelViewPrimitives::getLineSize() const
{
    return lineSize;
}

void ModelViewPrimitives::setLineSize(int value)
{
    lineSize = value;
}
