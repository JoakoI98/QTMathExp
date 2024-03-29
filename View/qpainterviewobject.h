#ifndef QPAINTERVIEWOBJECT_H
#define QPAINTERVIEWOBJECT_H

#include "../ModelView/modelviewprimitives.h"
#include <QPainter>



class QPainterViewObject : public ModelViewPrimitives
{
public:
    QPainterViewObject();

    std::tuple<int,int,int,int> drawLine(int x1, int y1, int x2, int y2)  override;
    std::tuple<int,int,int,int> drawCircle(int x, int y, int radius)  override;
    std::tuple<int,int,int,int> drawText(std::string text, int x, int y) override;
    std::tuple<int,int,int,int> draw32UnicodeChar(uint32_t ch, int x, int y) override;

    void setPainter(QPainter *value);

    ~QPainterViewObject() override;

private:
    QPainter *painter = nullptr;
    QPen defaultPen;
    QBrush defaulBrush;
};

#endif // QPAINTERVIEWOBJECT_H
