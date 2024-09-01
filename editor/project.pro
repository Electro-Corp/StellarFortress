HEADERS = src/*.h
SOURCES = src/*.cpp
CONFIG += qt warn_on release
TARGET  = build/MEDIT
INCLUDEPATH += /usr/include/jsoncpp
LIBS += -ljsoncpp
CONFIG += qt warn_on debug