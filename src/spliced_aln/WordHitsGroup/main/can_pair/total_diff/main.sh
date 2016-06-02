#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v

max_diff=0
./main.exe "$max_diff" 

max_diff=1
./main.exe "$max_diff"

max_diff=2
./main.exe "$max_diff"

max_diff=3
./main.exe "$max_diff"
