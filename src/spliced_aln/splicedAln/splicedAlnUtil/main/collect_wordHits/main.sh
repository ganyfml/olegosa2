#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v
ref=ATCGATCGATCGATCAGCTA
query=ATCG
./main.exe "$ref" "$query"
