#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v

ref="GTAAAG"
refStart_pos=0
refEnd_pos=5
./main.exe "$ref" "$refStart_pos" "$refEnd_pos"

ref="CTAAAC"
refStart_pos=0
refEnd_pos=5
./main.exe "$ref" "$refStart_pos" "$refEnd_pos"

ref="ATAAAC"
refStart_pos=0
refEnd_pos=5
./main.exe "$ref" "$refStart_pos" "$refEnd_pos"
