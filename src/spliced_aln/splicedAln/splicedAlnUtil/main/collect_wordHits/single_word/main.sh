#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v

ref=ATCT

word_seq=AT
rev_comp=0
./main.exe "$ref" "$word_seq" "$rev_comp"

word_seq=CT
./main.exe "$ref" "$word_seq" "$rev_comp"

ref=ATCT
word_seq=AT
rev_comp=1
./main.exe "$ref" "$word_seq" "$rev_comp"

word_seq=GG
rev_comp=0
./main.exe "$ref" "$word_seq" "$rev_comp"
