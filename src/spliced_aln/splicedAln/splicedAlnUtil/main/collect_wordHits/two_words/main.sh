#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v

#Test Group 1, rev_comp = 0 with one word hit
ref=ATCT
rev_comp=0

word1_seq=AT
word2_seq=GG
./main.exe "$ref" "$word1_seq" "$word2_seq" "$rev_comp"

word1_seq=GG
word2_seq=AT
./main.exe "$ref" "$word1_seq" "$word2_seq" "$rev_comp"

#Test group 2, rev_comp = 1 with one word hit
ref=ATCT
rev_comp=1

word1_seq=AT
word2_seq=GG
./main.exe "$ref" "$word1_seq" "$word2_seq" "$rev_comp"

word1_seq=GG
word2_seq=AT
./main.exe "$ref" "$word1_seq" "$word2_seq" "$rev_comp"

#Test group 3, rev_comp = 0 with two word hit
ref=ATGG
rev_comp=0

word1_seq=AT
word2_seq=GG
./main.exe "$ref" "$word1_seq" "$word2_seq" "$rev_comp"

word1_seq=GG
word2_seq=AT
./main.exe "$ref" "$word1_seq" "$word2_seq" "$rev_comp"

#Test group4, nothing hit
ref=ATGC
rev_comp=0

word1_seq=AA
word2_seq=GG
./main.exe "$ref" "$word1_seq" "$word2_seq" "$rev_comp"
