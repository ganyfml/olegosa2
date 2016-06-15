#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v
hit1_word_id=1
hit2_word_id=2
hit3_word_id=3
./main.exe "$hit1_word_id" "$hit2_word_id" "$hit3_word_id"

hit1_word_id=1
hit2_word_id=2
hit3_word_id=1
./main.exe "$hit1_word_id" "$hit2_word_id" "$hit3_word_id"

hit1_word_id=3
hit2_word_id=1
hit3_word_id=2
./main.exe "$hit1_word_id" "$hit2_word_id" "$hit3_word_id"
