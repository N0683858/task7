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
    headers/xmlparser.h

SOURCES += \
    src/earth.cpp \
    src/geometry.cpp \
    src/logs.cpp \
    src/position.cpp \
    src/route.cpp \
    src/track.cpp \
    src/xmlparser.cpp \
    src/gpx-tests/name.cpp \
    src/gpx-tests/n0693955-totalheightgaintests.cpp \
    src/gpx-tests/totalLength-t0068955.cpp \
    src/gpx-tests.cpp \
    src/gpx-tests/netHeightGain_n0689061.cpp \
    src/gpx-tests/name.cpp \
    src/gpx-tests/travellingTime-N0696066.cpp \
    src/gpx-tests/maxlattestsn0690641.cpp \
    src/gpx-tests/maxLongTests_N0669298.cpp \
    #src/gpx-tests/minLongitude_N0671080.cpp \
    src/gpx-tests/n0650950_numPos_Tests.cpp \
    src/gpx-tests/N0680192.cpp \
    src/gpx-tests/n0671966_mingrad.cpp \
    src/gpx-tests/N0643498_Max_Latitude.cpp \
    src/gpx-tests/totalHeightGain-N0720387.cpp \
    src/gpx-tests/max_elevation_n0689529.cpp \
    src/gpx-tests/n0688119_Route_maxGradient.cpp \
    src/gpx-tests/minElevation_N0699610.cpp \
    #src/gpx-tests/N0682255_MinLAtitude.cpp \
    src/gpx-tests/TestMinElev-N0719715.cpp \
    src/gpx-tests/N0682255_MinLAtitude.cpp \
    #src/gpx-tests/TestMinElev-N0719715.cpp \
    src/gpx-tests/TotalTime-N0688008-Tests.cpp \
    src/gpx-tests/n0673230_totalheightgain.cpp \
    src/gpx-tests/minLatTests_N0720717.cpp \
    #src/gpx-tests/numPositionsTests_n0719388.cpp \
    src/gpx-tests/maxElevation-n0686300.cpp \
    #src/gpx-tests/totalTime-N0702007.cpp \
    src/gpx-tests/netLength_n0641701.cpp \
    src/gpx-tests/n0703481_maxelevationtests.cpp \
    src/gpx-tests/n0494166MaximumLongitude.cpp \
    src/gpx-tests/n0680788-minElevationTests.cpp \
    #src/gpx-tests/N0692013_minLongitude().cpp \
    #src/gpx-tests/N0630057-MaxLatitudeTest.cpp
    src/gpx-tests/n0720144_mingradient_tests.cpp \
    src/gpx-tests/N0692013_minLongitude.cpp \
    #src/gpx-tests/N0630057-MaxLatitudeTest.cpp \
    src/gpx-tests/MaxLong-N0680337.cpp \
    src/gpx-tests/array-operator.cpp \
    src/gpx-tests/netLengthT0073651.cpp \
    src/gpx-tests/n0695913.cpp \
    #src/gpx-tests/mingradient_n0719479.cpp \
    #src/gpx-tests/averageSpeed(N0695426).cpp\
    src/gpx-tests/maxGradientTests_N0686602.cpp \
    src/gpx-tests/maxGradient-N0697611.cpp \
    src/gpx-tests/N0689085_findPosition.cpp \
    src/gpx-tests/N0719058_netHeightGain.cpp

INCLUDEPATH += headers/

TARGET = $$_PRO_FILE_PWD_/execs/gpx-tests

LIBS += -lboost_unit_test_framework

macx {

QMAKE_CFLAGS += -std=c++11 -stdlib=libc++

QMAKE_CXXFLAGS += -std=c++11 -stdlib=libc++

LIBS += -L"/usr/local/Cellar/boost/1.66.0/lib" -lboost_random

INCLUDEPATH += "/usr/local/Cellar/boost/1.66.0/include"


}
