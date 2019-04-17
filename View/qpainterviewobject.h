#ifndef QPAINTERVIEWOBJECT_H
#define QPAINTERVIEWOBJECT_H

#include "../ModelView/modelviewprimitives.h"
#include <QPainter>



class QPainterViewObject : public ModelViewPrimitives
{
public:
    QPainterViewObject();

    void drawLine(int x1, int y1, int x2, int y2)  override;
    void drawCircle(int x, int y, int radius)  override;
    void drawText(std::string text, int x, int y) override;

    void setPainter(QPainter *value);

private:
    QPainter *painter = nullptr;
    QPen defaultPen;
    QBrush defaulBrush;
};

#endif // QPAINTERVIEWOBJECT_H
