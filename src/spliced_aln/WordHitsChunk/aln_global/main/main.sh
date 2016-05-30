#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v
ref=ATG
query=ATCG
./main.exe "$ref" "$query"

ref=ATCG
query=ATG
./main.exe "$ref" "$query"

ref=ATC
query=ATG
./main.exe "$ref" "$query"
