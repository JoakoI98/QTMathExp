#include "expressionwidget.h"
#include <QApplication>
#include <windows.h>
#include <iostream>
#include "mathbinaryoperands.h"
#include "mathfinaloperands.h"


int main(int argc, char *argv[])
{
    if (AttachConsole(ATTACH_PARENT_PROCESS) || AllocConsole()) {
        freopen("CONOUT$", "w", stdout);
        freopen("CONOUT$", "w", stderr);
    }
    MathConstant c1(12);
    MathConstant c2(4);
    MathConstant c3(2);
    MathConstant c4(2);
    MathVariable v0(0);

    MathSubsOperator sumExp(&c1, &c2);
    MathMultOperator multExp(&c3, &c4);

    MathDivOperator divExp(&sumExp, &multExp);
    MathAddOperator addExp(&v0, &divExp);

    std::vector<double> args;
    args.push_back(5);
    std::cout << addExp << std::endl << addExp.evaluateExpression(args) << std::endl;


    system("pause");


    /*QApplication a(argc, argv);
    ExpressionWidget w;
    w.show();
    //FirstChange
    return a.exec();*/
    return 0;
}
