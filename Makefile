UNAME := $(shell uname)


ifeq ($(UNAME), Linux)
LINKFLAGS = -lSDLmain -lSDL -lglut -lGLU
BINARY = wing
else
LINKFLAGS = -lmingw32 -lSDLmain -lSDL -lOpenGL32 -lGLU32
BINARY = wing.exe
endif

CPP_SOURCES = src/main.cpp src/wing.cpp src/3d.cpp src/timer.cpp  src/importers.cpp

CPPFLAGS =  -g 
#-Wall

all: compile test

compile:
	g++ ${CPP_SOURCES} -o ${BINARY} ${CPPFLAGS} ${LINKFLAGS}

run:
	./${BINARY}
test:
	./${BINARY} --test
