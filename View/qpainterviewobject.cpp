#include "qpainterviewobject.h"
#include <QString>
#include <math.h>

QPainterViewObject::QPainterViewObject(): defaultPen(Qt::PenStyle::SolidLine), defaulBrush(Qt::BrushStyle::SolidPattern)
{
    int r,g,b;
    std::tie(r, g, b) = getTextColor();
    defaultPen.setColor(QColor(r,g,b));
    std::tie(r, g, b) = getBkgColor();
    defaulBrush.setColor(QColor(r, g, b));
}

std::tuple<int, int, int, int> QPainterViewObject::drawLine(int x1, int y1, int x2, int y2)
{
    bool haveToDeletePainter = false;
    if(painter == nullptr) {
        if(getGetingSize()){
            painter = new QPainter();
            haveToDeletePainter = true;
        }
        else throw "Painter null reference";
    }

    int r,g,b;
    std::tie(r, g, b) = getLineColor();
    defaultPen.setColor(QColor(r,g,b));
    defaultPen.setWidth(getLineSize());

    painter->setPen(defaultPen);

    if(getSeeing()) painter->drawLine(x1, y1, x2, y2);

    if(haveToDeletePainter) {
        delete painter;
        painter = nullptr;
    }

    return std::tuple<int,int,int,int>(x1,y1,x2,y2);
}

std::tuple<int, int, int, int> QPainterViewObject::drawCircle(int x, int y, int radius)
{
    bool haveToDeletePainter = false;
    if(painter == nullptr) {
        if(getGetingSize()){
            painter = new QPainter();
            haveToDeletePainter = true;
        }
        else throw "Painter null reference";
    }

    int r,g,b;
    std::tie(r, g, b) = getLineColor();
    defaultPen.setColor(QColor(r,g,b));
    defaultPen.setWidth(getLineSize());
    std::tie(r, g, b) = getBkgColor();
    defaulBrush.setColor(QColor(r,g,b));

    painter->setPen(defaultPen);
    painter->setBrush(defaulBrush);

    if(getSeeing()) painter->drawEllipse(x,y,radius,radius);

    if(haveToDeletePainter) {
        delete painter;
        painter = nullptr;
    }

    return std::tuple<int,int,int,int>(x-radius, y-radius, x+radius, y + radius);

}

std::tuple<int, int, int, int> QPainterViewObject::drawText(std::string text, int x, int y)
{
    bool haveToDeletePainter = false;
    if(painter == nullptr) {
        if(getGetingSize()){
            painter = new QPainter();
            haveToDeletePainter = true;
        }
        else throw "Painter null reference";
    }

    int r, g, b;
    std::tie(r, g, b) = getTextColor();
    defaultPen.setColor(QColor(r, g, b));
    QFont currFont = painter->font();
    currFont.setWeight(0);
    currFont.setPixelSize(getTextSize());
    painter->setFont(currFont);
    painter->setPen(defaultPen);

    if(getSeeing()) painter->drawText(x, y, QString::fromStdString(text));

    QFontMetrics metric = painter->fontMetrics();
    setPointer(x + metric.width(QString::fromStdString(text)),y);

    if(haveToDeletePainter) {
        delete painter;
        painter = nullptr;
    }

    return std::tuple<int,int,int,int>(x,y - (metric.height() - metric.xHeight()),x+metric.width(QString::fromStdString(text)), y);
}

std::tuple<int, int, int, int> QPainterViewObject::draw32UnicodeChar(uint32_t ch, int x, int y)
{
    bool haveToDeletePainter = false;
    if(painter == nullptr) {
        if(getGetingSize()){
            painter = new QPainter();
            haveToDeletePainter = true;
        }
        else throw "Painter null reference";
    }

    int r, g, b;
    std::tie(r, g, b) = getTextColor();
    defaultPen.setColor(QColor(r, g, b));
    QFont currFont = painter->font();
    currFont.setWeight(0);
    currFont.setPixelSize(getTextSize());
    painter->setFont(currFont);

    painter->setPen(defaultPen);
    if(getSeeing()) painter->drawText(x, y - round(static_cast<float>(getTextSize())/10), QString(QChar(ch)));
    QFontMetrics metric = painter->fontMetrics();
    setPointer(x + metric.width(QString(QChar(ch))),y);

    if(haveToDeletePainter) {
        delete painter;
        painter = nullptr;
    }

    return std::tuple<int,int,int,int>(x,y - metric.xHeight(),x+metric.width(QString(QChar(ch))), y);
}

void QPainterViewObject::setPainter(QPainter *value)
{
    painter = value;
}

QPainterViewObject::~QPainterViewObject()
{
    if(painter != nullptr) delete painter;
    return;
}




