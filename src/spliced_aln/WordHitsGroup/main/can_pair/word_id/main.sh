#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v

head_word_id=1
tail_word_id=0
./main.exe "$head_word_id" "$tail_word_id"

head_word_id=0
tail_word_id=0
./main.exe "$head_word_id" "$tail_word_id"

head_word_id=0
tail_word_id=1
./main.exe "$head_word_id" "$tail_word_id"
