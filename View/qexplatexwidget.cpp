#include "qexplatexwidget.h"
#include <QPainter>
#include <cmath>

QExpLatexWidget::QExpLatexWidget(QWidget *parent) : QWidget(parent)
{
    setMinimumSize(30,30);
    lTexImage = nullptr;
    aspectRatio = 1;
}



void QExpLatexWidget::setLOp(MathOperand *op)
{
    lOp = op;
    std::string strFName = op->getStringOp();
    for(char &c: strFName){
        if(c == ' ') c = '_';
        if(c == '/') c = '\'';
        if(c == '*') c = ',';
    }
    if(fExist("tmp\\" + strFName + ".png")){
        std::string strNewName = strFName;
        int i = 0;
        while (fExist("tmp\\" + strNewName + ".png")) {
            strNewName = strFName;
            strNewName += std::to_string(i++);
        }
        strFName = strNewName;
    }
    _pyOperations::renderLatexFormula(*lOp,strFName);

    if(lTexImage != nullptr) delete lTexImage;
    lTexImage = new QImage();
    QString fName = QString::fromStdString("tmp\\" + strFName + ".png");
    if (!lTexImage->load(fName)){
        std::cout << "Error al cargar la imagen" << std::endl;
    }

    std::cout << "Alto: " << lTexImage->height() << "   Ancho: " << lTexImage->width() << std::endl;
    aspectRatio = static_cast<double>((static_cast<double>(lTexImage->height()))/(static_cast<double>(lTexImage->width())));
    setMinimumWidth(lTexImage->width());
}

void QExpLatexWidget::paintEvent(QPaintEvent *e)
{
    if(lTexImage == nullptr) return;
    QPainter painter;
    painter.begin(this);
    painter.drawImage(e->rect(),*lTexImage);
    painter.end();
}

int QExpLatexWidget::heightForWidth(int w) const
{
    return static_cast<int>(round(w*aspectRatio));
}

bool QExpLatexWidget::hasHeightForWidth() const
{
    return true;
}

