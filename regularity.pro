QT += core gui widgets
CONFIG += c++11
TARGET = regularity

SOURCES += main.cpp \
    client.cpp \
    order.cpp \
    worker.cpp \
    factory.cpp \
    storage.cpp \
    mainwindow.cpp


HEADERS +=\
    client.h \
    order.h \
    worker.h \
    factory.h \
    storage.h \
    mainwindow.h

FORMS    += mainwindow.ui
