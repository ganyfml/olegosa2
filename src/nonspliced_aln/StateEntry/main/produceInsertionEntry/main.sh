#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v
ref=ATCG
char_insert=A
./main.exe "$ref" "$char_insert"

ref=ATC
char_insert=G
./main.exe "$ref" "$char_insert"
