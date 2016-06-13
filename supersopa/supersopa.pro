TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

SOURCES += main.cpp \
    board.cpp \
    dictionary.cpp \
    naive.cpp \
    trie.cpp \
    hashing.cpp \
    trie_alg.cpp

HEADERS += \
    board.h \
    dictionary.h \
    trie.h \
    hashing.h \
    naive.h \
    trie_alg.h

