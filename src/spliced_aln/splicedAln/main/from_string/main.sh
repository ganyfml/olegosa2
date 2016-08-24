#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v

ref=AAAAATTTTTGTAAAAAAAAAAAAAAAAAAAGCCCCCAAAAAAAAAAAAAA
query=TTTTTCCCCC
./main.exe "$ref" "$query"
