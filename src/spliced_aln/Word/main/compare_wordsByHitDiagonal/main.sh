#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

word1_refPos=4
word1_queryPos=2
word2_refPos=4
word2_queryPos=1

./main.exe "$word1_refPos" "$word1_queryPos" "$word2_refPos" "$word2_queryPos"
./main.exe "$word2_refPos" "$word2_queryPos" "$word1_refPos" "$word1_queryPos"

