#include "mathfinaloperands.h"
#define BUFF_SIZE 30

MathVariable::MathVariable(unsigned int id): id(id)
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
    buff << "x" << id << " ";
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
    for(char &c : buff){
        if(c == '.'){
            c = primitivesReference->getCommaRepresentation();
            finded = true;
            rec = 0;
            if(primitivesReference->getFloatRepresentation() == 0) {
                c = 0;
                break;
            }

        }
        if (finded){
            if(rec > primitivesReference->getFloatRepresentation()){
                c = 0;
            }
            rec++;
        }
    }
    if(primitivesReference->getFloatRepresentation() > 0 && finded == true){
        std::cout << "Corriendo" << std::endl;
        for (int i = BUFF_SIZE; i > 0; i--) {
            if(buff[i] == '0' || buff[i] == 0) buff[i] = 0;
            else if(buff[i] == primitivesReference->getCommaRepresentation()){
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




