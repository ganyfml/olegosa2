#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -x
gap_open=1
gap_ext=1
gap_mm=0

ref=CA
query=CTTA
./main.exe "$ref" "$query" "$gap_ext" "$gap_open" "$gap_mm"
