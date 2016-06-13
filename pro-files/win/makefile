#hier ein neuer kommentar
TARGET = exp-model-2.exe

HEADERS = \
	../../src/gn-fit.h \
	../../src/lm-fit.h \
	../../src/sa-fit.h \
	../../src/io-data.h \
	../../src/model.h \
	../../src/math-utils.h

SOURCES = \
	../../src/gn-fit.cpp \
	../../src/lm-fit.cpp \
	../../src/sa-fit.cpp \
	../../src/io-data.cpp \
	../../src/main.cpp

first: $(HEADERS) $(SOURCES)
	i586-mingw32msvc-g++  -o $(TARGET) -D__WIN__ $(SOURCES)
	# g++ -std=gnu++11 -o $(TARGET) -D__WIN__ $(SOURCES)