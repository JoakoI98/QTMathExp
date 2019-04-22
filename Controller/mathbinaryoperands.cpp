#include "mathbinaryoperands.h"
#include "mathfinaloperands.h"
#include <math.h>

MathBinaryOperand::MathBinaryOperand(MathOperand const *arg1, MathOperand const *arg2)
{

    arguments.clear();
    arguments.push_back(arg1);
    arguments.push_back(arg2);
}

void MathBinaryOperand::setStringRep(const std::string &value)
{
    stringRep = value;
}

MathAddOperator::MathAddOperator(MathOperand const *arg1, MathOperand const *arg2): MathBinaryOperand (arg1, arg2)
{
    setOp_Type(MathOperand::op_Add);
    setStringRep("+ ");
    return;
}

double MathAddOperator::evaluateExpression(std::vector<double> &arguments) const
{
    return this->arguments[0]->evaluateExpression(arguments) + this->arguments[1]->evaluateExpression(arguments);
}

void MathAddOperator::drawThis(ModelViewPrimitives *primitivesReference) const
{

    /*int curr_x, curr_y;

    std::tie(curr_x, curr_y) = primitivesReference->getPointer();
    primitivesReference->setPointer(curr_x, curr_y - primitivesReference->getTextSize()/2);

    std::tie(curr_x, curr_y) = primitivesReference->getPointer();
    primitivesReference->drawPointerLine(curr_x + 5, curr_y);
    primitivesReference->drawLine(curr_x + 2 , curr_y + 3, curr_x + 2, curr_y - 3);

    std::tie(curr_x, curr_y) = primitivesReference->getPointer();
    primitivesReference->setPointer(curr_x + 2, curr_y + primitivesReference->getTextSize()/2);*/


    int curr_x, curr_y;

    std::tie(curr_x, curr_y) = primitivesReference->getPointer();
    primitivesReference->setPointer(curr_x, curr_y -  1);

    primitivesReference->drawPointerText("+");

    std::tie(curr_x, curr_y) = primitivesReference->getPointer();
    primitivesReference->setPointer(curr_x, curr_y + 1);
}




void MathBinaryOperand::printExpression(std::vector<double> &arguments, std::ostream &buff) const
{
    buff << this->arguments[0] << stringRep << this->arguments[1];
}

void MathBinaryOperand::printExpression(std::ostream &buff) const
{
    MathOperand::typeEnum arg0Type = this->arguments[0]->getOp_Type();
    MathOperand::typeEnum arg1Type = this->arguments[1]->getOp_Type();

    if(this->getOp_Type() == MathOperand::op_Mult){
        if(arg0Type == MathOperand::op_Const){
            const MathConstant *cons = dynamic_cast<const MathConstant *>(this->arguments[0]);
            if(cons->getValue() == -1){
                buff << "-" << this->arguments[1];
                return;
            }
        }

        if(arg1Type == MathOperand::op_Const){
            const MathConstant *cons = dynamic_cast<const MathConstant *>(this->arguments[1]);
            if(cons->getValue() == -1){
                buff << "-" << this->arguments[0];
                return;
            }
        }
    }

    std::string strFix[4];
    for (int i = 0;i != 4;i++) {
        strFix[i] = "";
    }
    if(arg0Type != MathOperand::op_Const && arg0Type != MathOperand::op_Var){
        strFix[0] = "(";
        strFix[1] = "\b) ";
    }
    if(arg1Type != MathOperand::op_Const && arg1Type != MathOperand::op_Var){
        strFix[2] = "(";
        strFix[3] = "\b) ";
    }
    buff << strFix[0] << this->arguments[0] << strFix[1] << stringRep << strFix[2] << this->arguments[1] << strFix[3];
}

std::tuple<int, int, int, int> MathBinaryOperand::drawExpression(ModelViewPrimitives *primitivesReference) const
{

    MathOperand::drawExpression(primitivesReference);

    ModelViewPrimitives *__ModelView = primitivesReference;
    if(primitivesReference == nullptr) __ModelView = ModelView;

    std::tuple<int,int,int,int> rect0 = arguments[0]->drawExpression(__ModelView);
    int x,y;
    std::tie(x,y) = __ModelView->getPointer();
    int txtSize = __ModelView->getTextSize();
    x += 1 + static_cast<int>(round(txtSize/17.));
    __ModelView->setPointer(x,y);
    drawThis(__ModelView);
    std::tie(x,y) = __ModelView->getPointer();
    x += 3 + static_cast<int>(round(txtSize/17.));;
    __ModelView->setPointer(x,y);
    std::tuple<int,int,int,int> rect1 = arguments[1]->drawExpression(__ModelView);
    int x00, x01, x10, x11, y00, y01, y10, y11;
    std::tie(x00,y00,x01,y01) = rect0;
    std::tie(x10,y10,x11,y11) = rect1;
    return std::tuple<int,int,int,int>(x00,y00 > y10 ? y10 : y00,x11, y01 > y11 ? y01 : y11);
}
MathSubsOperator::MathSubsOperator(MathOperand const *arg1, MathOperand const *arg2): MathBinaryOperand (arg1, arg2)
{
    setOp_Type(MathOperand::op_Subs);
    setStringRep("- ");
    return;
}

double MathSubsOperator::evaluateExpression(std::vector<double> &arguments) const
{
    return this->arguments[0]->evaluateExpression(arguments) - this->arguments[1]->evaluateExpression(arguments);
}

void MathSubsOperator::drawThis(ModelViewPrimitives *primitivesReference) const
{
    /*int curr_x, curr_y;
    std::tie(curr_x, curr_y) = primitivesReference->getPointer();
    primitivesReference->setPointer(curr_x + 2, curr_y + primitivesReference->getTextSize()/2);
    std::tie(curr_x, curr_y) = primitivesReference->getPointer();
    primitivesReference->drawPointerLine(curr_x + 5, curr_y);
    std::tie(curr_x, curr_y) = primitivesReference->getPointer();
    primitivesReference->setPointer(curr_x + 2, curr_y - primitivesReference->getTextSize()/2);*/

    int curr_x, curr_y;

    std::tie(curr_x, curr_y) = primitivesReference->getPointer();
    primitivesReference->setPointer(curr_x, curr_y -  1);

    primitivesReference->drawPointerText("-");

    std::tie(curr_x, curr_y) = primitivesReference->getPointer();
    primitivesReference->setPointer(curr_x, curr_y + 1);
}






MathMultOperator::MathMultOperator(MathOperand const *arg1, MathOperand const *arg2): MathBinaryOperand (arg1, arg2)
{
    setOp_Type(MathOperand::op_Mult);
    setStringRep("* ");
    return;
}

double MathMultOperator::evaluateExpression(std::vector<double> &arguments) const
{
    return this->arguments[0]->evaluateExpression(arguments) * this->arguments[1]->evaluateExpression(arguments);
}

void MathMultOperator::drawThis(ModelViewPrimitives *primitivesReference) const
{
    /*int curr_x, curr_y;
    std::tie(curr_x, curr_y) = primitivesReference->getPointer();
    primitivesReference->setPointer(curr_x + 2, curr_y - primitivesReference->getTextSize()/2);
    std::tie(curr_x, curr_y) = primitivesReference->getPointer();
    primitivesReference->drawPointerCircle(2);
    std::tie(curr_x, curr_y) = primitivesReference->getPointer();
    primitivesReference->setPointer(curr_x + 2, curr_y + primitivesReference->getTextSize()/2);*/

    //primitivesReference->setTextSize(primitivesReference->getTextSize()+5);
    primitivesReference->drawPointer32UnicodeChar(0x25CF);
    //primitivesReference->setTextSize(primitivesReference->getTextSize()-5);
}




MathDivOperator::MathDivOperator(MathOperand const *arg1, MathOperand const *arg2): MathBinaryOperand (arg1, arg2)
{
    setOp_Type(MathOperand::op_Div);
    setStringRep("/ ");
    return;
}

double MathDivOperator::evaluateExpression(std::vector<double> &arguments) const
{
    double val2 = this->arguments[1]->evaluateExpression(arguments);
    if (val2 == 0)
        throw "Division by 0";
    return this->arguments[0]->evaluateExpression(arguments) / val2;
}

std::tuple<int, int, int, int> MathDivOperator::drawExpression(ModelViewPrimitives *primitivesReference) const
{
    MathOperand::drawExpression(primitivesReference);

    ModelViewPrimitives *__ModelView = primitivesReference;
    if(primitivesReference == nullptr) __ModelView = ModelView;

    int s0x0 = 0, s0x1 = 73, s0y0 = 15, s0y1 = 30;
    std::tie(s0x0,s0y0,s0x1,s0y1) = arguments[0]->getSize(__ModelView);
    int s1x0 =0 , s1x1 = 12, s1y0 = 15, s1y1 = 30;
    std::tie(s1x0,s1y0,s1x1,s1y1) = arguments[1]->getSize(__ModelView);

    const MathOperand *bigger, *smaller;
    int biggerWeith, smallerWeith;

    if(abs(s0x1-s0x0) > abs(s1x1-s1x0)){
        bigger = arguments[0];
        smaller = arguments[1];
        biggerWeith = abs(s0x1-s0x0);
        smallerWeith = abs(s1x1-s1x0);
    } else{
        bigger = arguments[1];
        smaller = arguments[0];
        smallerWeith = abs(s0x1-s0x0);
        biggerWeith = abs(s1x1-s1x0);
    }

    int _px,_py;
    std::tie(_px,_py) = __ModelView->getPointer();
    __ModelView->setPointer(_px,_py - __ModelView->getTextSize()/2 + __ModelView->getTextSize()/10);
    __ModelView->setLineSize(1+floor(__ModelView->getTextSize()/20));
    __ModelView->drawPointerLine(_px+biggerWeith, _py - __ModelView->getTextSize()/2 + __ModelView->getTextSize()/10, true);

    std::tuple<int, int, int, int> rect = {0,0,0,0};

    if(bigger == arguments[0]){
        __ModelView->setPointer(_px,_py - __ModelView->getTextSize()/2 - (5 + abs(_py - s0y1)));
        arguments[0]->drawExpression(__ModelView);
        __ModelView->setPointer(_px + biggerWeith/2 - smallerWeith/2,_py - __ModelView->getTextSize()/2 + (5 + abs(_py - s1y0)));
        arguments[1]->drawExpression(__ModelView);
        rect = {_px, _py - __ModelView->getTextSize()/2 - abs(s0y1 -s0y0) - 5, _px + biggerWeith, _py - __ModelView->getTextSize()/2 + abs(s1y1 -s1y0) + 5};
    } else {
        __ModelView->setPointer(_px + biggerWeith/2 - smallerWeith/2, _py - __ModelView->getTextSize()/2 - (5 + abs(_py - s0y1)));
        arguments[0]->drawExpression(__ModelView);
        __ModelView->setPointer(_px, _py - __ModelView->getTextSize()/2 + (5 + abs(_py - s1y0)));
        arguments[1]->drawExpression(__ModelView);
        rect = {_px, _py - __ModelView->getTextSize()/2 - abs(s0y1 -s0y0) - 5, _px + biggerWeith, _py - __ModelView->getTextSize()/2 + abs(s1y1 -s1y0) + 5};

    }

    __ModelView->setPointer(_px+biggerWeith, _py);
    return rect;
}




MathOperand &operator+(MathOperand &operand0, const MathOperand &operand1)
{
    MathAddOperator *ne = new MathAddOperator(&operand0, &operand1);
    return *ne;
}

MathOperand &operator-(MathOperand &operand0, const MathOperand &operand1)
{
    MathSubsOperator *ne = new MathSubsOperator(&operand0, &operand1);
    return *ne;
}

MathOperand &operator/(MathOperand &operand0, const MathOperand &operand1)
{
    MathDivOperator *ne = new MathDivOperator(&operand0, &operand1);
    return *ne;
}

MathOperand &operator*(MathOperand &operand0, const MathOperand &operand1)
{
    MathMultOperator *ne = new MathMultOperator(&operand0, &operand1);
    return *ne;
}

MathOperand &operator^(MathOperand &operand0, const MathOperand &operand1)
{
    MathPowerOperator *ne = new MathPowerOperator(&operand0, &operand1);
    return *ne;
}

MathOperand &operator-(const MathOperand &operand0){
    MathConstant *minus = new MathConstant(-1);
    MathMultOperator *negative = new MathMultOperator(minus,&operand0);
    return *negative;
}

MathPowerOperator::MathPowerOperator(const MathOperand *arg1, const MathOperand *arg2): MathBinaryOperand (arg1, arg2)
{
    setOp_Type(MathOperand::op_Power);
    setStringRep("^");
    return;
}

double MathPowerOperator::evaluateExpression(std::vector<double> &arguments) const
{

    return pow(this->arguments[0]->evaluateExpression(arguments),this->arguments[1]->evaluateExpression(arguments));
}

std::tuple<int, int, int, int> MathPowerOperator::drawExpression(ModelViewPrimitives *primitivesReference) const
{
    ModelViewPrimitives *__ModelView = primitivesReference;
    if(primitivesReference == nullptr) __ModelView = ModelView;

    int s0x0 = 0, s0x1 = 73, s0y0 = 15, s0y1 = 30;
    int s1x0 =0 , s1x1 = 12, s1y0 = 15, s1y1 = 30;

    std::tie(s0x0, s0y0, s0x1, s0y1) = arguments[0]->drawExpression(__ModelView);

    int oldTxtSize = __ModelView->getTextSize();
    __ModelView->setTextSizeNF(round(static_cast<float>(oldTxtSize)/1.2));
    std::tie(s1x0, s1y0, s1x1, s1y1) = arguments[1]->getSize(__ModelView);

    int _px, _py;
    std::tie(_px, _py) = __ModelView->getPointer();
    __ModelView->setPointer(_px+__ModelView->getTextSize()/70,_py - abs(s0y1 - s0y0) - abs(s1y1 - _py) + abs(s1y1-s1y0)/10 +3+__ModelView->getTextSize()/5);

    std::tie(s1x0, s1y0, s1x1, s1y1) = arguments[1]->drawExpression(__ModelView);

    __ModelView->setPointer(s1x1, _py);
    __ModelView->setTextSize(oldTxtSize);

    return std::tuple<int, int, int, int>(s0x0, s0y0 > s1y0 ? s1y0 : s0y0, s1x1,  s0y1 > s1y1 ? s0y1 : s1y1);


}

MathRootrOperator::MathRootrOperator(const MathOperand *arg1, const MathOperand *arg2) : MathBinaryOperand (arg1, arg2)
{
    setOp_Type(MathOperand::op_Root);
    setStringRep("root");
    return;
}

double MathRootrOperator::evaluateExpression(std::vector<double> &arguments) const
{
    return pow(this->arguments[1]->evaluateExpression(arguments),1.0/(this->arguments[0]->evaluateExpression(arguments)));
}

std::tuple<int, int, int, int> MathRootrOperator::drawExpression(ModelViewPrimitives *primitivesReference) const
{
    ModelViewPrimitives *__ModelView = primitivesReference;
    if(primitivesReference == nullptr) __ModelView = ModelView;
    int s0x0 = 0, s0x1 = 73, s0y0 = 15, s0y1 = 30;
    int s1x0 =0 , s1x1 = 12, s1y0 = 15, s1y1 = 30;

    std::tie(s0x0, s0y0, s0x1, s0y1) = arguments[1]->getSize(__ModelView);

    int oldTxtSize = __ModelView->getTextSize();
    __ModelView->setTextSizeNF(round(static_cast<float>(oldTxtSize)/1.2));
    std::tie(s1x0, s1y0, s1x1, s1y1) = arguments[0]->getSize(__ModelView);
    if(abs(s1y1-s0y0) > abs(s0y1-s0y0)){
        __ModelView->setTextSizeNF(round(static_cast<float>(oldTxtSize)/2.2));
        std::tie(s1x0, s1y0, s1x1, s1y1) = arguments[0]->getSize(__ModelView);
    }
    int _px, _py;
    std::tie(_px, _py) = __ModelView->getPointer();
    __ModelView->setPointer(_px, _py - __ModelView->getTextSize()/2 + _py - s1y1 - 3 - oldTxtSize/20);
    std::tie(s1x0, s1y0, s1x1, s1y1) = arguments[0]->drawExpression(__ModelView);
    __ModelView->setTextSizeNF(oldTxtSize);

    int oldLineSize = __ModelView->getLineSize();
    __ModelView->setLineSize(oldTxtSize/10);
    int middleWidth = abs(s1x1-s1x0)/2;
    __ModelView->setPointer(_px + middleWidth, s1y1 + 3 + oldTxtSize/20);
    if(middleWidth < 2 + __ModelView->getTextSize()/15) middleWidth = 2 + __ModelView->getTextSize()/15;
    __ModelView->drawPointerLine(_px + middleWidth + abs(s1x1-s1x0)/2, s0y1);
    int __px = _px + middleWidth + abs(s1x1-s1x0)/2 + 5 + oldTxtSize/10;
    __ModelView->drawPointerLine(__px, s0y0 - 2 - oldTxtSize/15);
    __ModelView->drawPointerLine(__px + abs(s0x1-s0x0) + 3 + oldTxtSize/8 ,s0y0 - 2 - oldTxtSize/15);
    __ModelView->setLineSize(oldLineSize);

    __ModelView->setPointer(__px + 2 + oldTxtSize/10, _py);
    arguments[1]->drawExpression(__ModelView);



    return std::tuple<int, int, int, int>(s1x0, s1y0 >  s0y0 - 2 - oldTxtSize/15 ?  s0y0 - 2 - oldTxtSize/15 : s1y0, __px + abs(s0x1-s0x0) + 3 + oldTxtSize/8 , s0y1);

}
