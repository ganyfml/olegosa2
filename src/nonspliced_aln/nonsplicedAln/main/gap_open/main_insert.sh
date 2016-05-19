#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v
ref=ATC
gap_open=1
gap_ext=1
gap_mm=0
query=AC
./main.exe "$ref" "$query" "$gap_ext" "$gap_open" "$gap_mm"

gap_open=0
gap_ext=0
gap_mm=0
query=AC
./main.exe "$ref" "$query" "$gap_ext" "$gap_open" "$gap_mm"

gap_open=0
gap_ext=1
gap_mm=0
query=AC
./main.exe "$ref" "$query" "$gap_ext" "$gap_open" "$gap_mm"

gap_open=1
gap_ext=0
gap_mm=0
query=AC
./main.exe "$ref" "$query" "$gap_ext" "$gap_open" "$gap_mm"
