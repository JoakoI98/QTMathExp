#-------------------------------------------------
#
# Project created by QtCreator 2019-04-12T00:37:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtMathExpressions
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
    Controller/mathbinaryoperands.cpp \
    Controller/mathfinaloperands.cpp \
    Controller/mathoperand.cpp \
    ModelView/modelviewprimitives.cpp \
    View/qpainterviewobject.cpp \
    View/expressionwidget.cpp \
    ModelView/modelviewlinker.cpp \
    Controller/mathunaryoperands.cpp \
    Controller/_pythoncontroller.cpp \
    View/qlatexviwer.cpp \
    View/qexplatexwidget.cpp

HEADERS += \
    Controller/mathbinaryoperands.h \
    Controller/mathfinaloperands.h \
    Controller/mathoperand.h \
    ModelView/modelviewprimitives.h \
    View/qpainterviewobject.h \
    View/expressionwidget.h \
    ModelView/modelviewlinker.h \
    Controller/mathunaryoperands.h \
    Controller/literalsdefinitions.h \
    Controller/_pythoncontroller.h \
    Controller/_mathoperandfactory.h \
    Controller/_factoryfunctions.h \
    View/qlatexviwer.h \
    View/qexplatexwidget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32: LIBS += -L'C:/Python 3.7/libs/' -lpython37

INCLUDEPATH += 'C:/Python 3.7/include'
DEPENDPATH += 'C:/Python 3.7/include'

win32:!win32-g++: PRE_TARGETDEPS += 'C:/Python 3.7/libs/python37.lib'
else:win32-g++: PRE_TARGETDEPS += 'C:/Python 3.7/libs/libpython37.a'
