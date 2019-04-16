#ifndef EXPRESSIONWIDGET_H
#define EXPRESSIONWIDGET_H

#include <QWidget>

class ExpressionWidget : public QWidget
{
    Q_OBJECT

public:
    ExpressionWidget(QWidget *parent = 0);
    ~ExpressionWidget();
protected:
    void paintEvent(QPaintEvent *e) override;
};

#endif // EXPRESSIONWIDGET_H
