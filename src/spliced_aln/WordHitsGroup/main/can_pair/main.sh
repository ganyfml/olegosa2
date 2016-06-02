#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v

word_chunk1_strand=1
word_chunk2_strand=0
./main.exe "$word_chunk1_strand" "$word_chunk2_strand"

word_chunk1_strand=1
word_chunk2_strand=1
./main.exe "$word_chunk1_strand" "$word_chunk2_strand"
