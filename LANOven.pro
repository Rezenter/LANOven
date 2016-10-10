QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LANOven
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp\
    logger.cpp \
    lanchatter.cpp


HEADERS  += mainwindow.h \
    logger.h \
    lanchatter.h

FORMS    += mainwindow.ui
