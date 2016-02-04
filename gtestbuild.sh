#!/usr/bin/env bash

mkdir -p gtestbuild
cd gtestbuild
#CXX=g++-4.9 CC=gcc-4.9 cmake -G"Unix Makefiles" ../gtest-1.7.0
cmake -G"Unix Makefiles" ../gtest-1.7.0
make -j
