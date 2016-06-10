#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v

query=AGTC
word_length=2

word_max_overlap=0
./main.exe "$word_length" "$word_max_overlap" "$query"

word_max_overlap=1
./main.exe "$word_length" "$word_max_overlap" "$query"

word_length=3

word_max_overlap=0
./main.exe "$word_length" "$word_max_overlap" "$query"

word_max_overlap=1
./main.exe "$word_length" "$word_max_overlap" "$query"

word_max_overlap=2
./main.exe "$word_length" "$word_max_overlap" "$query"

#Uneven distribution
query=AGTAGC
word_length=3
word_max_overlap=1
./main.exe "$word_length" "$word_max_overlap" "$query"
