#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v 

ref=AGT
ref_pos=1
revcomp=0
./main.exe "$ref" "$ref_pos" "$revcomp"

ref=ACT
ref_pos=1
revcomp=1
./main.exe "$ref" "$ref_pos" "$revcomp"
