#include "mathunaryoperands.h"
#include "mathfinaloperands.h"
#include "math.h"
#include <algorithm>
#include <iostream>
# define M_E 2.7182818284590452354

MathUnaryOperands::MathUnaryOperands(const MathOperand *arg1)
{
    arguments.clear();
    arguments.push_back(arg1);
}

void MathUnaryOperands::printExpression(std::ostream &buff) const
{
    //buff.flush();
    buff << strRep << '(' << arguments[0] << ") ";
    //buff.flush();
}

void MathUnaryOperands::printExpressionP(std::ostream &buff) const
{
    //buff.flush();
    buff << strRep << '(';
    arguments[0]->printExpressionP(buff);
    buff << ") ";
    //buff.flush();
}

std::tuple<int, int, int, int> MathUnaryOperands::drawExpression(ModelViewPrimitives *primitivesReference) const
{
    ModelViewPrimitives *__ModelView = primitivesReference;
    if(primitivesReference == nullptr) __ModelView = ModelView;
    int s0x0 = 0, s0x1 = 73, s0y0 = 15, s0y1 = 30;
    int s1x0 =0 , s1x1 = 12, s1y0 = 15, s1y1 = 30;
    int px0, px1, py0, py1;

    int px, py;
    std::tie(px, py) = __ModelView->getPointer();

    std::tie(s0x0, s0y0, s0x1, s0y1) = __ModelView->drawPointerText(strRep);

    int _px, _py;
    std::tie(_px, _py) = __ModelView->getPointer();

    std::tie(s1x0, s1y0, s1x1, s1y1) = arguments[0]->getSize(__ModelView);
    int oldTxtSize = __ModelView->getTextSize(), newTxtSize = abs(s1y1-s1y0);
    __ModelView->setPointer(_px, s1y1 - 2 - oldTxtSize/10);
    __ModelView->setTextSize(newTxtSize);
    std::tie(px0, py0, px1, py1) =__ModelView->drawPointerText("(");
    __ModelView->setTextSize(oldTxtSize);
    int __px, __py;
    std::tie(__px, __py) = __ModelView->getPointer();
    __ModelView->setPointer(__px,_py);
    std::tie(s1x0, s1y0, s1x1, s1y1) = arguments[0]->drawExpression(__ModelView);
    __ModelView->setTextSize(newTxtSize);
    int ___px, ___py;
    std::tie(___px, ___py) = __ModelView->getPointer();
    __ModelView->setPointer(___px, s1y1 - 2 - oldTxtSize/10);
    __ModelView->drawPointerText(")");
    int ____px, ____py;
    std::tie(____px, ____py) = __ModelView->getPointer();
    __ModelView->setPointer(____px, ___py);
    __ModelView->setTextSize(oldTxtSize);

    int ry0[] = {s1y0,s0y0,py0};
    int ry1[] = {s1y1,s0y1,py1};

    return std::tuple<int, int, int, int>(px, *std::min_element(ry0, ry0+3), px + abs(____px - px), *std::max_element(ry1, ry1+3));


}

std::string MathUnaryOperands::getStringOp() const
{
    std::string strRet = strRep + "(" + arguments[0]->getStringOp()+")";
    return strRet;
}

MathExpOperand::MathExpOperand(const MathOperand *arg) : MathPowerOperator (new MathConstant(M_E) ,arg)
{
    return;
}

std::tuple<int, int, int, int> MathExpOperand::drawExpression(ModelViewPrimitives *primitivesReference) const
{
    ModelViewPrimitives *__ModelView = primitivesReference;
    if(primitivesReference == nullptr) __ModelView = ModelView;

    int s0x0 = 0, s0x1 = 73, s0y0 = 15, s0y1 = 30;
    int s1x0 =0 , s1x1 = 12, s1y0 = 15, s1y1 = 30;

    std::tie(s0x0, s0y0, s0x1, s0y1) = __ModelView->drawPointerText("e");

    int _px, _py;
    std::tie(_px, _py) = __ModelView->getPointer();
    __ModelView->setPointer(_px+__ModelView->getTextSize()/70,_py - abs(s0y1 - s0y0)+3+__ModelView->getTextSize()/5);
    int oldTxtSize = __ModelView->getTextSize();
    __ModelView->setTextSizeNF(round(static_cast<float>(oldTxtSize)/1.2));
    std::tie(s1x0, s1y0, s1x1, s1y1) = arguments[1]->drawExpression(__ModelView);

    __ModelView->setPointer(s1x1, _py);
    __ModelView->setTextSize(oldTxtSize);

    return std::tuple<int, int, int, int>(s0x0, s0y0 > s1y0 ? s1y0 : s0y0, s1x1,  s0y1 > s1y1 ? s0y1 : s1y1);


}

MathSinOperand::MathSinOperand(const MathOperand *arg1) : MathUnaryOperands (arg1)
{
    strRep = "sin";
}

double MathSinOperand::evaluateExpression(std::vector<double> &arguments) const
{
    return sin(this->arguments[0]->evaluateExpression(arguments));
}

MathLnOperand::MathLnOperand(const MathOperand *arg1): MathUnaryOperands (arg1)
{
    strRep = "Ln";
}

double MathLnOperand::evaluateExpression(std::vector<double> &arguments) const
{
    return log(this->arguments[0]->evaluateExpression(arguments));
}

MathCosOperand::MathCosOperand(const MathOperand *arg1) : MathUnaryOperands (arg1)
{
    strRep = "cos";
}

double MathCosOperand::evaluateExpression(std::vector<double> &arguments) const
{
    return cos(this->arguments[0]->evaluateExpression(arguments));
}

MathTgOperand::MathTgOperand(const MathOperand *arg1) : MathUnaryOperands (arg1)
{
    strRep = "tg";
}

double MathTgOperand::evaluateExpression(std::vector<double> &arguments) const
{
    return tan(this->arguments[0]->evaluateExpression(arguments));
}
