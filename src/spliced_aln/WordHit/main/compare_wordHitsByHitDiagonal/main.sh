#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

wordHit1_refPos=4
wordHit1_queryPos=2
wordHit2_refPos=4
wordHit2_queryPos=1

./main.exe "$wordHit1_refPos" "$wordHit1_queryPos" "$wordHit2_refPos" "$wordHit2_queryPos"
./main.exe "$wordHit2_refPos" "$wordHit2_queryPos" "$wordHit1_refPos" "$wordHit1_queryPos"

