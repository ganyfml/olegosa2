#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v

ref=ATCGTAGAGG
existing_part=G
char_insert=T
./main.exe "$ref" "$existing_part" "$char_insert"

ref=ATC
char_insert=G
existing_part=A
./main.exe "$ref" "existing_part" "$char_insert"

ref=ATCG
char_insert=T
existing_part=''
./main.exe "$ref" "$existing_part" "$char_insert"
