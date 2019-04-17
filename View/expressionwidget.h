#ifndef EXPRESSIONWIDGET_H
#define EXPRESSIONWIDGET_H

#include <QWidget>
#include "qpainterviewobject.h"
#include "../ModelView/modelviewlinker.h"

class ExpressionWidget : public QWidget
{
    Q_OBJECT

public:
    ExpressionWidget(QWidget *parent = nullptr);
    ~ExpressionWidget() override;
    ModelViewLinker &getLinker();

protected:
    void paintEvent(QPaintEvent *e) override;

private:
    QPainterViewObject viewModel;
    ModelViewLinker linker;
};

#endif // EXPRESSIONWIDGET_H
