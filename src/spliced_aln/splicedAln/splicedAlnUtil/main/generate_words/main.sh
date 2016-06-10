#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v

query=AGTC
word_length=2

wod_max_overlap=0
./main.exe "$word_length" "$wod_max_overlap" "$query"

wod_max_overlap=1
./main.exe "$word_length" "$wod_max_overlap" "$query"

word_length=3

wod_max_overlap=0
./main.exe "$word_length" "$wod_max_overlap" "$query"

wod_max_overlap=1
./main.exe "$word_length" "$wod_max_overlap" "$query"

wod_max_overlap=2
./main.exe "$word_length" "$wod_max_overlap" "$query"
