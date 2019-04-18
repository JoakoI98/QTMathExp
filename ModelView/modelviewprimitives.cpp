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

std::tuple<int,int,int,int> ModelViewPrimitives::drawPointerLine(int x2, int y2)
{
    int x,y;
    std::tie(x,y) = pointer;
    std::tuple<int,int,int,int> rect = drawLine(x,y,x2,y2);
    pointer = {x2,y2};
    return rect;
}

std::tuple<int,int,int,int> ModelViewPrimitives::drawPointerCircle(int radius)
{
    int x,y;
    std::tie(x,y) = pointer;
    std::tuple<int,int,int,int> rect = drawCircle(x+radius, y, radius);
    pointer = {x + 2*radius, y};
    return rect;
}

std::tuple<int,int,int,int> ModelViewPrimitives::drawPointerText(std::string text)
{
    int x,y;
    std::tie(x,y) = pointer;
    return drawText(text,x ,y);
}

std::tuple<int,int,int,int> ModelViewPrimitives::drawPointer32UnicodeChar(uint32_t ch)
{
    int x,y;
    std::tie(x,y) = pointer;
    return draw32UnicodeChar(ch, x, y);
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
    int tz = value;
    if(value > 15) tz = 15;
    else if(value < 12) tz = 12;
    textSize = tz;
}

void ModelViewPrimitives::setTextSizeNF(int value)
{
    int tz = value;
    if(value > 15) tz = 15;
    textSize = tz;
}

int ModelViewPrimitives::getLineSize() const
{
    return lineSize;
}

void ModelViewPrimitives::setLineSize(int value)
{
    lineSize = value;
}

ModelViewPrimitives::~ModelViewPrimitives()
{
    return;
}

unsigned int ModelViewPrimitives::getFloatRepresentation() const
{
    return floatRepresentation;
}

void ModelViewPrimitives::setFloatRepresentation(unsigned int value)
{
    floatRepresentation = value;
}

char ModelViewPrimitives::getCommaRepresentation() const
{
    return commaRepresentation;
}

void ModelViewPrimitives::setCommaRepresentation(char value)
{
    commaRepresentation = value;
}

bool ModelViewPrimitives::getSeeing() const
{
    return _seeing;
}

void ModelViewPrimitives::setSeeing(bool seeing)
{
    _seeing = seeing;
}
