#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v

word1_strand=1
word2_strand=2
word1_ref_pos=2
word2_ref_pos=2
./main.exe "$word1_strand" "$word1_ref_pos" "$word2_strand" "$word2_ref_pos"

word1_strand=2
word2_strand=1
word1_ref_pos=2
word2_ref_pos=2
./main.exe "$word1_strand" "$word1_ref_pos" "$word2_strand" "$word2_ref_pos"

word1_strand=1
word2_strand=1
word1_ref_pos=1
word2_ref_pos=2
./main.exe "$word1_strand" "$word1_ref_pos" "$word2_strand" "$word2_ref_pos"

word1_strand=1
word2_strand=1
word1_ref_pos=2
word2_ref_pos=1
./main.exe "$word1_strand" "$word1_ref_pos" "$word2_strand" "$word2_ref_pos"

word1_strand=1
word2_strand=1
word1_ref_pos=1
word2_ref_pos=1
./main.exe "$word1_strand" "$word1_ref_pos" "$word2_strand" "$word2_ref_pos"
