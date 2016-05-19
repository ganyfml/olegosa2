#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v
ref=AGT
godown_char=A
./main.exe "$ref" "$godown_char"

godown_char=C
./main.exe "$ref" "$godown_char"
