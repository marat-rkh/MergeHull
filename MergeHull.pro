TEMPLATE = app
TARGET = merge-hull

CONFIG += QtGui
QT += opengl

OBJECTS_DIR = bin

QMAKE_CXXFLAGS = -std=c++11 -Wall

macx {
    QMAKE_CXXFLAGS += -stdlib=libc++
    QMAKE_LFLAGS += -lc++
}

CONFIG += precompile_header
PRECOMPILED_HEADER = src/stdafx.h

DEPENDPATH += src \
              visualization/headers \
              visualization/headers/common \
              visualization/headers/io \
              visualization/headers/visualization \

INCLUDEPATH += src \
               visualization/headers \


SOURCES += src/tests.cpp \
    src/merge.cpp \
    src/main.cpp \
    src/utils.cpp \
    src/merge_hull.cpp

HEADERS += src/tests.h \
    src/merge.h \
    src/utils.h \
    src/merge_hull.h \
    src/viewer.h \
    src/stdafx.h \
    src/poly_iter.h

LIBS += -Lvisualization -lvisualization

CONFIG += c++11
