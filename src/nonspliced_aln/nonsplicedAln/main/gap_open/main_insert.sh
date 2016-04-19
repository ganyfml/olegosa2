#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v
ref=A
gap_open=1
gap_ext=0
gap_mm=0

query=AA
./main.exe "$ref" "$query" "$gap_ext" "$gap_open" "$gap_mm"
query=AT
./main.exe "$ref" "$query" "$gap_ext" "$gap_open" "$gap_mm"
query=AC
./main.exe "$ref" "$query" "$gap_ext" "$gap_open" "$gap_mm"
query=AG
./main.exe "$ref" "$query" "$gap_ext" "$gap_open" "$gap_mm"
