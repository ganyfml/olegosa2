#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -x
ref=AAATACAG
exist_part=A
next_char=C
max_gapOpen=1
max_gapExt=1
./main.exe "$ref" "$exist_part" "$next_char" "$max_gapOpen" "$max_gapExt"

max_gapOpen=0
max_gapExt=0
./main.exe "$ref" "$exist_part" "$next_char" "$max_gapOpen" "$max_gapExt"

max_gapOpen=1
max_gapExt=0
./main.exe "$ref" "$exist_part" "$next_char" "$max_gapOpen" "$max_gapExt"

max_gapOpen=0
max_gapExt=1
./main.exe "$ref" "$exist_part" "$next_char" "$max_gapOpen" "$max_gapExt"
