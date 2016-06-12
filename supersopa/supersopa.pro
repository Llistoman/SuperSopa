TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    dictionary.cpp \
    board.cpp \
    naive.cpp

HEADERS += \
    dictionary.h \
    board.h

