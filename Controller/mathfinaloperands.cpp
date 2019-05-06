#include "mathfinaloperands.h"
#define BUFF_SIZE 30

MathVariable::MathVariable(unsigned int id, std::string _s): id(id), _symbol(_s)
{
    setOp_Type(MathOperand::op_Var);
    return;
}

double MathVariable::evaluateExpression(std::vector<double> &arguments) const
{
    if(id >= arguments.size())
        throw "Variable not set";
    return arguments[id];
}

void MathVariable::printExpression(std::vector<double> &arguments, std::ostream &buff) const
{
    if(id >= arguments.size())
        throw "Variable not set";
    buff << arguments[id] << " ";
    return;
}

void MathVariable::printExpression(std::ostream &buff) const
{
    //buff.flush();
    buff << "x" << id << " ";
    //buff.flush();
    return;
}

void MathVariable::printExpressionP(std::ostream &buff) const
{
    //buff.flush();
    if (_symbol == "")
        buff << "x" << id << " ";
    else
        buff << _symbol << " ";
    //buff.flush();
    return;
}

std::tuple<int, int, int, int> MathVariable::drawExpression(ModelViewPrimitives *primitivesReference) const
{
    MathOperand::drawExpression(primitivesReference);

    ModelViewPrimitives *__ModelView = primitivesReference;
    if(primitivesReference == nullptr) __ModelView = ModelView;
    std::tuple<int,int,int,int> rect = __ModelView->drawPointerText("x" + std::to_string(id));

    return rect;
}



unsigned int MathVariable::getId() const
{
    return id;
}

std::string MathVariable::getStringOp() const
{
    std::string strRet;
    if(_symbol == "")
         strRet = " x" + std::to_string(id) + " ";
    else
        strRet = _symbol + " ";
    return strRet;
}

MathConstant::MathConstant(double value): value(value)
{
    setOp_Type(MathOperand::op_Const);
    return;
}

std::tuple<int, int, int, int> MathConstant::drawExpression(ModelViewPrimitives *primitivesReference) const
{
    MathOperand::drawExpression(primitivesReference);

    ModelViewPrimitives *__ModelView = primitivesReference;
    if(primitivesReference == nullptr) __ModelView = ModelView;

    char buff[BUFF_SIZE];
    std::sprintf(buff,"%.5f",value);
    bool finded = false;
    unsigned int rec = 0;
    unsigned int i = 0;
    for(char &c : buff){
        if(c == '.' && i <= __ModelView->getFloatRepresentation()){
            c = __ModelView->getCommaRepresentation();
            finded = true;
            rec = 0;
            if(__ModelView->getFloatRepresentation() == 0) {
                c = 0;
                break;
            }

        }
        if (finded){
            if(rec > __ModelView->getFloatRepresentation()){
                c = 0;
            }
            rec++;
        }
        i++;
    }
    if(__ModelView->getFloatRepresentation() > 0 && finded == true){
        for (int i = BUFF_SIZE; i > 0; i--) {
            if(buff[i] == '0' || buff[i] == 0) buff[i] = 0;
            else if(buff[i] == __ModelView->getCommaRepresentation()){
                buff[i] = 0;
                break;
            }
            else break;
        }
    }
    std::tuple<int,int,int,int> rect = __ModelView->drawPointerText(std::string(buff));

    return rect;
}

double MathConstant::getValue() const
{
    return value;
}

std::string MathConstant::getStringOp() const
{
    char buff[BUFF_SIZE];
    std::sprintf(buff,"%.5f",value);
    bool finded = false;
    unsigned int rec = 0;
    unsigned int i = 0;
    for(char &c : buff){
        if(c == '.' && i <= 2){
            c = '.';
            finded = true;
            rec = 0;

        }
        if (finded){
            if(rec > 2){
                c = 0;
            }
            rec++;
        }
        i++;
    }
    if(2 > 0 && finded == true){
        for (int i = BUFF_SIZE; i > 0; i--) {
            if(buff[i] == '0' || buff[i] == 0) buff[i] = 0;
            else if(buff[i] == '.'){
                buff[i] = 0;
                break;
            }
            else break;
        }
    }




    std::string strRet(buff);

    return strRet;
}




