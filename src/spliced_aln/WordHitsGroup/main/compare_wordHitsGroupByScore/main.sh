#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v

group1score=1
group2score=2
./main.exe "$group1score" "$group2score"

group1score=2
group2score=2
./main.exe "$group1score" "$group2score"

group1score=2
group2score=1
./main.exe "$group1score" "$group2score"
