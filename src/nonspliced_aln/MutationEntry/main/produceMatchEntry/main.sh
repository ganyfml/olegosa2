#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v
ref=ATCG
query=A
./main.exe "$ref" "$query"

ref=ATC
query=G
./main.exe "$ref" "$query"
