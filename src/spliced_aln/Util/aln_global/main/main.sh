#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v
ref=TG
query=TCG
./main.exe "$ref" "$query"

ref=ATG
query=AG
./main.exe "$ref" "$query"

ref=ATCACTAG
query=AG
./main.exe "$ref" "$query"
