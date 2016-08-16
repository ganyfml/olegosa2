#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v 

ref=AAG
ref_pos=1
./main.exe "$ref" "$ref_pos"

ref=AAC
ref_pos=1
./main.exe "$ref" "$ref_pos"
