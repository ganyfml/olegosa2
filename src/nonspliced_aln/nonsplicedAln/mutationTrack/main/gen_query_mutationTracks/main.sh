#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v

ref=ACATTTCCCGGG
query=GAATAAT
./main.exe "$ref" "$query"
