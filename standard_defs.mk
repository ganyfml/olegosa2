CXX = clang++
PACKAGE:=Tiancai
INCLUDES:=-I$(abspath $(find_upwards include))
SRC_DIR:=$(find_upwards src)
OS:=$(shell uname)
ifeq ($(OS), Linux)
	LDLIBS:=-lrt
endif
CXXFLAGS:=-std=c++14 -Wall -Wextra -O0 -g
PKG_LIBS:=-lstdc++ -lrt
