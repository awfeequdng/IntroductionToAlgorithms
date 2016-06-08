TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    redblacktree.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    redblacktree.h

