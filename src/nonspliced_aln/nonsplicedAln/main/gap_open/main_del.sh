#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -x
gap_open=1
gap_ext=0
gap_mm=0
ref=T
query=TA
./main.exe "$ref" "$query" "$gap_ext" "$gap_open" "$gap_mm"
