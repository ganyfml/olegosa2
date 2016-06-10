#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v

ref=AGCT
query=AGAA
./main.exe "$ref" "$query"

ref=AGCT
query=AAAG
./main.exe "$ref" "$query"
