#include "expressionwidget.h"
#include <QApplication>
#include <windows.h>
#include <iostream>
#include "mathbinaryoperands.h"
#include "mathfinaloperands.h"
#include "literalsdefinitions.cpp"




int main(int argc, char *argv[])
{
    if (AttachConsole(ATTACH_PARENT_PROCESS) || AllocConsole()) {
        freopen("CONOUT$", "w", stdout);
        freopen("CONOUT$", "w", stderr);
    }

    MathOperand &res2 = (0_v+1_v)/(0_v - 3._c);

    std::vector<double> args;
    args.clear();
    args.push_back(5);
    args.push_back(5);
    std::cout << res2 << std::endl << res2.evaluateExpression(args) << std::endl;


    system("pause");


    /*QApplication a(argc, argv);
    ExpressionWidget w;
    w.show();
    //FirstChange
    return a.exec();*/
    return 0;
}
