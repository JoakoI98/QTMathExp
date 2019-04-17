#include "qpainterviewobject.h"
#include <QString>

QPainterViewObject::QPainterViewObject(): defaultPen(Qt::PenStyle::SolidLine), defaulBrush(Qt::BrushStyle::SolidPattern)
{
    int r,g,b;
    std::tie(r, g, b) = getTextColor();
    defaultPen.setColor(QColor(r,g,b));
    std::tie(r, g, b) = getBkgColor();
    defaulBrush.setColor(QColor(r, g, b));
}

void QPainterViewObject::drawLine(int x1, int y1, int x2, int y2)
{

    int r,g,b;
    std::tie(r, g, b) = getLineColor();
    defaultPen.setColor(QColor(r,g,b));
    defaultPen.setWidth(getLineSize());

    painter->drawLine(x1, y1, x2, y2);
}

void QPainterViewObject::drawCircle(int x, int y, int radius)
{
    int r,g,b;
    std::tie(r, g, b) = getLineColor();
    defaultPen.setColor(QColor(r,g,b));
    defaultPen.setWidth(getLineSize());
    std::tie(r, g, b) = getBkgColor();
    defaulBrush.setColor(QColor(r,g,b));

    painter->drawEllipse(x,y,radius,radius);

}

void QPainterViewObject::drawText(std::string text, int x, int y)
{
    int r, g, b;
    std::tie(r, g, b) = getTextColor();
    defaultPen.setColor(QColor(r, g, b));
    QFont currFont = painter->font();
    currFont.setPointSize(getTextSize());

    painter->drawText(x, y, QString::fromStdString(text));

    QFontMetrics metric = painter->fontMetrics();
    setPointer(x + metric.width(QString::fromStdString(text)),y);
    return;
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




