#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v
gap_open=0
gap_ext=0
gap_mm=0
ref=AGAG
query=AG
./main.exe "$ref" "$query" "$gap_ext" "$gap_open" "$gap_mm"

gap_mm=1
query=AT
./main.exe "$ref" "$query" "$gap_ext" "$gap_open" "$gap_mm"

gap_open=1
gap_ext=2
gap_mm=0

ref=CA
query=CTGA
./main.exe "$ref" "$query" "$gap_ext" "$gap_open" "$gap_mm"

ref=CTGA
query=CA
./main.exe "$ref" "$query" "$gap_ext" "$gap_open" "$gap_mm"

gap_open=0
gap_ext=0
gap_mm=1
ref=AG
query=AT
./main.exe "$ref" "$query" "$gap_ext" "$gap_open" "$gap_mm"
