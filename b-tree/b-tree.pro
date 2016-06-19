TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    b_tree.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    b_tree.h

