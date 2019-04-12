#include "expressionwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ExpressionWidget w;
    w.show();

    return a.exec();
}
