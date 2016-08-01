#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v 

ref=AAG
ref_pos=1
revcomp=0
./main.exe "$ref" "$ref_pos" "$revcomp"

ref=AAG
ref_pos=1
revcomp=1
./main.exe "$ref" "$ref_pos" "$revcomp"

ref=AAC
ref_pos=1
revcomp=1
./main.exe "$ref" "$ref_pos" "$revcomp"

ref=AAC
ref_pos=1
revcomp=0
./main.exe "$ref" "$ref_pos" "$revcomp"
