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
    x+= 3 + static_cast<int>(round(txtSize/17.));
    __ModelView->setPointer(x,y);
    drawThis(__ModelView);
    std::tie(x,y) = __ModelView->getPointer();
    x+=3;
    __ModelView->setPointer(x,y);
    std::tuple<int,int,int,int> rect1 = arguments[1]->drawExpression(__ModelView);
    int x00, x01, x10, x11, y00, y01, y10, y11;
    std::tie(x00,y00,x01,y01) = rect0;
    std::tie(x10,y10,x11,y11) = rect1;
    return std::tuple<int,int,int,int>(x00,y00 > y10 ? y00 : y10,x11, y01 > y11 ? y01 : y11);
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
    MathOperand::drawExpression();
    return std::tuple<int,int,int,int>(0,0,0,0);
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

MathOperand &operator-(const MathOperand &operand0){
    MathConstant *minus = new MathConstant(-1);
    MathMultOperator *negative = new MathMultOperator(minus,&operand0);
    return *negative;
}
