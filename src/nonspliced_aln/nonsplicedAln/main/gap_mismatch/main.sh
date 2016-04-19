#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v
gap_open=0
gap_ext=0
gap_mm=0
ref=AG
query=AG
./main.exe "$ref" "$query" "$gap_ext" "$gap_open" "$gap_mm"

query=AT
gap_mm=1
./main.exe "$ref" "$query" "$gap_ext" "$gap_open" "$gap_mm"
