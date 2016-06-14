#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v
wordHit1_refPos=1
wordHit2_refPos=1
./main.exe "$wordHit1_refPos" "$wordHit2_refPos"

wordHit1_refPos=1
wordHit2_refPos=2
./main.exe "$wordHit1_refPos" "$wordHit2_refPos"

wordHit1_refPos=2
wordHit2_refPos=1
./main.exe "$wordHit1_refPos" "$wordHit2_refPos"
