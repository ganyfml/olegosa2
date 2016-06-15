#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v
hits_word_id=(1 2 3)
./main.exe "${hits_word_id[@]}"

hits_word_id=(3 2 1)
./main.exe "${hits_word_id[@]}"

hits_word_id=(3 1 2)
./main.exe "${hits_word_id[@]}"

hits_word_id=(1 2 1)
./main.exe "${hits_word_id[@]}"
