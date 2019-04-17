#ifndef MODELVIEWPRIMITIVES_H
#define MODELVIEWPRIMITIVES_H
#include <QColor>
#include <iostream>
#include <tuple>
#include <utility>

class ModelViewPrimitives
{
public:
    ModelViewPrimitives();

    virtual void drawLine(int x1, int y1, int x2, int y2)   = 0;
    void drawPointerLine(int x2, int y2){
        int x,y;
        std::tie(x,y) = pointer;
        drawLine(x,y,x2,y2);
        pointer = {x2,y2};
    }

    virtual void drawCircle(int x1, int y1, int radius)  = 0;
    void drawPointerCircle(int radius){
        int x,y;
        std::tie(x,y) = pointer;
        drawCircle(x+radius, y, radius);
        pointer = {x + 2*radius, y};
    }

    virtual void drawText(std::string text, int x, int y)  = 0;
    virtual void drawPointerText(std::string text){
        int x,y;
        std::tie(x,y) = pointer;
        drawText(text,x ,y);
    }


    std::pair<int, int> getPointer() const;
    void setPointer(const std::pair<int, int> &value);
    void setPointer(int x, int y);

    std::tuple<int, int, int> getLineColor() const;
    void setLineColor(const std::tuple<int, int, int> &value);
    std::tuple<int, int, int> getTextColor() const;
    void setTextColor(const std::tuple<int, int, int> &value);
    std::tuple<int, int, int> getBkgColor() const;
    void setBkgColor(const std::tuple<int, int, int> &value);
    int getTextSize() const;
    void setTextSize(int value);
    int getLineSize() const;
    void setLineSize(int value);

    virtual ~ModelViewPrimitives();


private:
    std::pair<int,int> pointer;
    std::tuple<int,int,int> lineColor;
    std::tuple<int,int,int> textColor;
    std::tuple<int,int,int> bkgColor;
    bool autoAvancePointer = true;
    int textSize;
    int lineSize;
};

#endif // MODELVIEWPRIMITIVES_H
