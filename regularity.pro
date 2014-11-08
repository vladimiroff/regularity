TEMPLATE = app
CONFIG += c++11

QT += qml quick widgets

SOURCES += main.cpp \
    client.cpp \
    order.cpp \
    worker.cpp \
    factory.cpp \
    storage.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    client.h \
    order.h \
    worker.h \
    factory.h \
    storage.h
