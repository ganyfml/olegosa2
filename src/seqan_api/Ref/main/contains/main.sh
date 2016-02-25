#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v

ref=AGTGTCAGTAGCATG
query=ATTCGTCA
./main.exe "$ref" "$query"

query=AGT
./main.exe "$ref" "$query"
