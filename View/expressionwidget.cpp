#include "expressionwidget.h"
#include <QPainter>
#include <QPaintEvent>
#include <QMessageBox>
#include <exception>


ExpressionWidget::ExpressionWidget(QWidget *parent): QWidget (parent), linker(&viewModel)
{
    //setMaximumHeight(15);
    viewModel.setTextSize(12);
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
        viewModel.setPointer(0,this->geometry().height()/2);

        std::tuple<int, int, int, int> rect = linker.getSize();
        int x0,y0,x1,y1;
        std::tie(x0,y0,x1,y1) = rect;

        if(abs(y1-y0) > geometry().height()) setGeometry(geometry().x(),geometry().y(),geometry().width(),abs(y1-y0));
        //if(abs(x1-x0) > geometry().width()) setMinimumWidth(abs(x1-x0));





        int _px, _py;
        std::tie(_px, _py) = viewModel.getPointer();
        viewModel.setPointer(0,this->geometry().height()/2-(y1-_py)+abs(y1-y0)/2);


        QBrush oldBR = painter.brush();
        QPen oldPN = painter.pen();
        QBrush br(QColor(100,255,100));
        QPen pn(QColor(100,255,100));
        pn.setColor(QColor(100,255,100));
        painter.setBrush(br);
        painter.setPen(pn);
        std::tuple<int, int, int, int> rectD = linker.getSize();
        int x0D,y0D,x1D,y1D;
        std::tie(x0D,y0D,x1D,y1D) = rectD;
        painter.drawRect(x0D,y0D,abs(x1D-x0D),abs(y1D-y0D));
        painter.setBrush(oldBR);
        painter.setPen(oldPN);


        linker.sendDraw();
        viewModel.setPainter(nullptr);
    } catch (const char *e) {
        painter.end();
        return;
    }
    painter.end();
}

void ExpressionWidget::resizeEvent(QResizeEvent *e)
{
    int newHeight = e->size().height();
    viewModel.setTextSize(newHeight/4);

    //getLinker().txtSizeFromHeight(newHeight);
    QWidget::resizeEvent(e);
}

ModelViewLinker &ExpressionWidget::getLinker()
{
    return linker;
}

int ExpressionWidget::setThisAtMinimumHeigth()
{
    if(!linker.isLinked()) throw "Not linked yet";
    int x0, y0, x1, y1;
    std::tie(x0, y0, x1, y1) = linker.getSize();
    setMinimumHeight(abs(y1-y0));
    return abs(y1-y0);
}
