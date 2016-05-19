#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -x
word1_refPos=1
word2_refPos=1
word3_refPos=2
word4_refPos=3
./main.exe "$word1_refPos" "$word2_refPos" "$word3_refPos" "$word4_refPos"

word1_refPos=1
word2_refPos=3
word3_refPos=2
word4_refPos=3
./main.exe "$word1_refPos" "$word2_refPos" "$word3_refPos" "$word4_refPos"

word1_refPos=1
word2_refPos=2
word3_refPos=3
word4_refPos=4
./main.exe "$word1_refPos" "$word2_refPos" "$word3_refPos" "$word4_refPos"
