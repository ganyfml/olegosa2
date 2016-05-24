#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v
wordHit1_refPos=1
wordHit2_refPos=1
word3_refPos=2
word4_refPos=3
./main.exe "$wordHit1_refPos" "$wordHit2_refPos" "$word3_refPos" "$word4_refPos"

wordHit1_refPos=1
wordHit2_refPos=3
word3_refPos=2
word4_refPos=3
./main.exe "$wordHit1_refPos" "$wordHit2_refPos" "$word3_refPos" "$word4_refPos"

wordHit1_refPos=1
wordHit2_refPos=2
word3_refPos=3
word4_refPos=4
./main.exe "$wordHit1_refPos" "$wordHit2_refPos" "$word3_refPos" "$word4_refPos"
