#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v

head_word_refEnd_pos=0
tail_word_refStart_pos=0
./main.exe "$head_word_refEnd_pos" "$tail_word_refStart_pos"

head_word_refEnd_pos=1
tail_word_refStart_pos=0
./main.exe "$head_word_refEnd_pos" "$tail_word_refStart_pos"

head_word_refEnd_pos=1
tail_word_refStart_pos=1
./main.exe "$head_word_refEnd_pos" "$tail_word_refStart_pos"

head_word_refEnd_pos=0
tail_word_refStart_pos=1
./main.exe "$head_word_refEnd_pos" "$tail_word_refStart_pos"
