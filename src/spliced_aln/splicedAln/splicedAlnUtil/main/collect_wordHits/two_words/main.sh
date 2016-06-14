#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v

ref=ATCT
rev_comp=0

word0_seq=AT
word1_seq=GG
./main.exe "$ref" "$word0_seq" "$word1_seq" "$rev_comp"

word0_seq=GG
word1_seq=AT
./main.exe "$ref" "$word0_seq" "$word1_seq" "$rev_comp"

word0_seq=AT
word1_seq=CT
./main.exe "$ref" "$word0_seq" "$word1_seq" "$rev_comp"
