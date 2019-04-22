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
    int setThisAtMinimumHeigth();

protected:
    void paintEvent(QPaintEvent *e) override;
    void resizeEvent(QResizeEvent *e) override;

private:
    QPainterViewObject viewModel;
    ModelViewLinker linker;
    bool p = true;
};

#endif // EXPRESSIONWIDGET_H
