#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v
gap_open=1
gap_ext=1
gap_mm=0

ref=CA
query=CTGA
query_qual=IIII
./main.exe "$ref" "$query" "$query_qual" "$gap_ext" "$gap_open" "$gap_mm" 
