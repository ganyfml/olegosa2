#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v

ref=GTAG
./main.exe "$ref" "0" "3"

ref=CTAC
./main.exe "$ref" "0" "3"

ref=ATGA
./main.exe "$ref" "0" "3"
