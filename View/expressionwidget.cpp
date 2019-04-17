#include "expressionwidget.h"
#include <QPainter>
#include <QPaintEvent>
#include <QMessageBox>
#include <exception>


ExpressionWidget::ExpressionWidget(QWidget *parent): QWidget (parent), linker(&viewModel)
{
    return;
}

ExpressionWidget::~ExpressionWidget()
{
    return;
}

void ExpressionWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter;
    painter.begin(this);
    painter.fillRect(e->rect(),QColor(100,100,100));
    if(linker.isLinked() == false){
        painter.end();
        return;
    }
    try {
        viewModel.setPainter(&painter);
        viewModel.setPointer(30,10);
        linker.sendDraw();
        viewModel.setPainter(nullptr);
    } catch (const char *e) {
        std::cout << e << std::endl;
        assert(false);
    }
    painter.end();
}

ModelViewLinker &ExpressionWidget::getLinker()
{
    return linker;
}
