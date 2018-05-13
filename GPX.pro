TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

HEADERS += \
    headers/earth.h \
    headers/geometry.h \
    headers/logs.h \
    headers/position.h \
    headers/route.h \
    headers/track.h \
    headers/types.h \
    headers/xmlparser.h \
    headers/gridworld.h \
    headers/gridworld_route.h \
    headers/gridworld_track.h \
    headers/xmlgenerator.h

SOURCES += \
    src/earth.cpp \
    src/geometry.cpp \
    src/logs.cpp \
    src/main.cpp \
    src/position.cpp \
    src/route.cpp \
    src/track.cpp \
    src/xmlparser.cpp \
    src/gridworld.cpp \
    src/gridworld_route.cpp \
    src/gridworld_track.cpp \
    src/xmlgenerator.cpp

INCLUDEPATH += headers/

TARGET = $$_PRO_FILE_PWD_/execs/gpx

LIBS += -lboost_unit_test_framework
