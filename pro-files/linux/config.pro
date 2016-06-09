TARGET  = prg.exe

TEMPLATE = app
CONFIG += console thread warn_on release 
CONFIF -= qt
QT -= gui core

DEFINES += 
QMAKE_CXXFLAGS  += -O2 -fPIC -restrict -fno-fnalias -fno-rtti -fno-exceptions -static -std=c++11
QMAKE_LFLAGS    +=

INCLUDEPATH += 

LIBS +=

HEADERS = \
	../../src/math-utils.h \
	../../src/gn-fit.h \
	../../src/lm-fit.h \
	../../src/sa-fit.h \
	../../src/model.h \
	../../src/io-data.h

SOURCES	= \
	../../src/gn-fit.cpp \
	../../src/lm-fit.cpp \
	../../src/sa-fit.cpp \
	../../src/io-data.cpp \
	../../src/main.cpp



unix:OBJECTS_DIR          = objs
#unix:MOC_DIR              = moc

unix:QMAKE_POST_LINK=strip $(TARGET)
