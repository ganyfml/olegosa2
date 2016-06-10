#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

ref_pos1=2
ref_pos2=4

./main.exe "$ref_pos1" "$ref_pos2" 
./main.exe "$ref_pos2" "$ref_pos1" 
