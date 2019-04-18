#include "expressionwidget.h"
#include <QPainter>
#include <QPaintEvent>
#include <QMessageBox>
#include <exception>


ExpressionWidget::ExpressionWidget(QWidget *parent): QWidget (parent), linker(&viewModel)
{
    setMaximumHeight(15);
    setMinimumHeight(12);
    setMinimumWidth(100);
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

    try {
        viewModel.setPainter(&painter);
        viewModel.setPointer(0,this->geometry().height());
        viewModel.setTextSize(this->geometry().height());
        viewModel.setSeeing(false);
        std::tuple<int, int, int, int> rect = linker.getSize();
        int x0,y0,x1,y1;
        std::tie(x0,y0,x1,y1) = rect;
        QBrush br(QColor(100,255,100));
        QPen pn(QColor(100,255,100));
        painter.setPen(pn);
        painter.setBrush(br);
        painter.drawRect(x0,y0,abs(x1-x0),abs(y1-y0));
        viewModel.setSeeing(true);
        linker.sendDraw();
        viewModel.setPainter(nullptr);
        setMinimumWidth(300);
    } catch (const char *e) {
        painter.end();
        return;
    }
    painter.end();
}

ModelViewLinker &ExpressionWidget::getLinker()
{
    return linker;
}
