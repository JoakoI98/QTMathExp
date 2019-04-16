#include "expressionwidget.h"
#include <QPainter>
#include <QPaintEvent>
#include <QMessageBox>

ExpressionWidget::ExpressionWidget(QWidget *parent)
    : QWidget(parent)
{
    update();
}

ExpressionWidget::~ExpressionWidget()
{

}

void ExpressionWidget::paintEvent(QPaintEvent *e)
{
    QPainter p;
    p.fillRect(e->rect(), QColor(0, 32, 200));
}
