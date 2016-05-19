#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -x
query_pos1=2
query_pos2=4

./main.exe "$query_pos1" "$query_pos2" 
./main.exe "$query_pos2" "$query_pos1" 
