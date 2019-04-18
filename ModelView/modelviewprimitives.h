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

    virtual std::tuple<int,int,int,int> drawLine(int x1, int y1, int x2, int y2)   = 0;
    std::tuple<int,int,int,int> drawPointerLine(int x2, int y2);

    virtual std::tuple<int,int,int,int> drawCircle(int x1, int y1, int radius)  = 0;
    std::tuple<int,int,int,int> drawPointerCircle(int radius);

    virtual std::tuple<int,int,int,int> drawText(std::string text, int x, int y)  = 0;
    virtual std::tuple<int,int,int,int> drawPointerText(std::string text);

    virtual std::tuple<int,int,int,int> draw32UnicodeChar(uint32_t ch, int x, int y) = 0;
    virtual std::tuple<int,int,int,int> drawPointer32UnicodeChar(uint32_t ch);


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
    void setTextSizeNF(int value);
    bool getSeeing() const;
    void setSeeing(bool seeing);
    unsigned int getFloatRepresentation() const;
    void setFloatRepresentation(unsigned int value);
    char getCommaRepresentation() const;
    void setCommaRepresentation(char value);

    virtual ~ModelViewPrimitives();



private:
    std::pair<int,int> pointer;
    std::tuple<int,int,int> lineColor;
    std::tuple<int,int,int> textColor;
    std::tuple<int,int,int> bkgColor;
    bool autoAvancePointer = true;
    int textSize;
    int lineSize;
    bool _seeing = true;
    unsigned int floatRepresentation = 5;
    char commaRepresentation = ',';
};

#endif // MODELVIEWPRIMITIVES_H
