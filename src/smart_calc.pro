QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    credit.cpp \
    deposit.cpp \
    graph_calc.cpp \
    main.cpp \
    menu.cpp \
    qcustomplot.cpp \
    s21_smart_calc.c \
    smart_calc.cpp

HEADERS += \
    credit.h \
    deposit.h \
    menu.h \
    qcustomplot.h \
    s21_smart_calc.h \
    smart_calc.h

FORMS += \
    credit.ui \
    deposit.ui \
    menu.ui \
    smart_calc.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
