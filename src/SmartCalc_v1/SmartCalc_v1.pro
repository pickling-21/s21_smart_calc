QT       += core gui printsupport 

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    graph_my.cpp \
    main.cpp \
    mainwindow.cpp \
    ../Project/s21_calc.c \
    ../Project/s21_common.c \
    ../Project/s21_polish_calc.c \
    ../Project/s21_credit_calc.c \
    ../Project/structs/s21_double.c \
    ../Project/structs/s21_list.c \
    ../Project/structs/s21_operators.c \
    ../Project/polish_format/s21_polish_format.c \
    ../Project/polish_format/s21_valid.c \
    ../Project/polish_format/s21_notation.c \
    ../Project/polish_format/s21_replace_name.c \
    qcustomplot.cpp


HEADERS += \
    graph_my.h \
    mainwindow.h \
    ../Project/s21_calc.h \
    ../Project/s21_common.h \
    ../Project/s21_polish_calc.h \
    ../Project/s21_credit_calc.h \
    ../Project/structs/s21_double.h \
    ../Project/structs/s21_list.h \
    ../Project/structs/s21_operators.h \
    ../Project/polish_format/s21_polish_format.h \
    ../Project/structs/s21_structs.h \
    qcustomplot.h


FORMS += \
    graph_my.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    SmartCalc.pro.user
