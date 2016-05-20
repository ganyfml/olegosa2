#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v
seq=TCGACTACGTCTACGAT
query=CT
./main.exe "$seq" "$query" 
