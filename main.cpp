#include "View/expressionwidget.h"
#include <QApplication>
#include <windows.h>
#include <iostream>
#include <QMainWindow>
#include "Controller/mathbinaryoperands.h"
#include "Controller/mathfinaloperands.h"
#include "Controller/literalsdefinitions.cpp"
#include <QVBoxLayout>
#include <QSpacerItem>




int main(int argc, char *argv[])
{
    if (AttachConsole(ATTACH_PARENT_PROCESS) || AllocConsole()) {
        freopen("CONOUT$", "w", stdout);
        freopen("CONOUT$", "w", stderr);
    }
    QApplication a(argc, argv);
    QVBoxLayout *lw = new QVBoxLayout();
    ExpressionWidget w0;
    w0.setMinimumHeight(50);
    MathOperand &op = 10_c;
    w0.getLinker().link(&op);
    op.getModelView()->setPointer(15,15);
    if(op.getModelView() == nullptr) std::cout << "Not linked" << std::endl;
    else std::cout << "Linked" << std::endl;
    w0.update();
    lw->addWidget(&w0);


    auto mw = new QWidget;
    mw->setLayout(lw);
    mw->show();
    //FirstChange
    return a.exec();

}
