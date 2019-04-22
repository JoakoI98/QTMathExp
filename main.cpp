#include "Controller/_pythoncontroller.h"
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
#include <QScrollArea>




int main(int argc, char *argv[])
{
    /*if (AttachConsole(ATTACH_PARENT_PROCESS) || AllocConsole()) {
        freopen("CONOUT$", "w", stdout);
        freopen("CONOUT$", "w", stderr);
    }*/



    QApplication a(argc, argv);
    Py_Initialize();
    try {
        _pythonController::prtNewStr("2+2sin 3x");
    } catch (const char *e) {
        cout << e << endl;
    }

    cout << endl;


    /*QVBoxLayout *lw = new QVBoxLayout();
    ExpressionWidget w0;

    //MathOperand &op = ((((0_v / 1_v)+1_e)/( 0_v+5_c))/5_e + 2_c)/3_e;

    MathOperand &op = sroot(_sin(2_c + (2_c^0_v)))/(0_v+2_v);

    lw->addWidget(&w0);

    w0.getLinker().link(&op);
    try {
        int k = w0.setThisAtMinimumHeigth();
    } catch (const char *c) {
        std::cout << "Exception: " << c << "\n";
    }

    auto mw = new QWidget;
    mw->setLayout(lw);


    mw->show();

    //FirstChange*/
    return a.exec();

}
