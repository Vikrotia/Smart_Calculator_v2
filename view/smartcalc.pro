QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    calculator.cc \
    ../controller/controller.cc \
    credit.cc \
    ../main.cc \
    mainwindow.cc \
    ../model/creditmodel.cc \
    ../model/mathmodel.cc \
    qcustomplot.cc

HEADERS += \
    calculator.h \
    ../controller/controller.h \
    credit.h \
    mainwindow.h \
    ../model/creditmodel.h \
    ../model/mathmodel.h \
    qcustomplot.h

FORMS += \
    calculator.ui \
    credit.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES +=
