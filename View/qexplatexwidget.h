#ifndef QEXPLATEXWIDGET_H
#define QEXPLATEXWIDGET_H
#include "Controller/_pythoncontroller.h"
#include <QImage>
#include "../Controller/mathoperand.h"
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <fstream>
#include <QWidget>
#include <QPaintEvent>


class QExpLatexWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QExpLatexWidget(QWidget *parent = nullptr);

    void setLOp(MathOperand *op);

signals:


public slots:
protected:
    void paintEvent(QPaintEvent *e) override;
    int heightForWidth(int w) const override;
    bool hasHeightForWidth() const override;
private:
    double aspectRatio;
    QImage *lTexImage;
    MathOperand *lOp;
    std::string lFileName;
};

inline bool fExist (const std::string& name) {
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0);
}



#endif // QEXPLATEXWIDGET_H
