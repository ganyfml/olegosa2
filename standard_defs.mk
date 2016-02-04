PACKAGE:=Tiancai
INCLUDES:=-I$(abspath $(find_upwards include))
SRC_DIR:=$(find_upwards src)
OS:=$(shell uname)
ifeq ($(OS), Linux)
	LDLIBS:=-lrt
endif
CXXFLAGS:=-std=c++11
#CXXFLAGS:=-std=gnu++1z
PKG_LIBS:=-lstdc++ -lrt
