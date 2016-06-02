#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v
wordHit1_refPos=1
wordHit2_refPos=1
wordHit3_refPos=2
wordHit4_refPos=3
./main.exe "$wordHit1_refPos" "$wordHit2_refPos" "$wordHit3_refPos" "$wordHit4_refPos"

wordHit1_refPos=1
wordHit2_refPos=3
wordHit3_refPos=2
wordHit4_refPos=3
./main.exe "$wordHit1_refPos" "$wordHit2_refPos" "$wordHit3_refPos" "$wordHit4_refPos"

wordHit1_refPos=1
wordHit2_refPos=2
wordHit3_refPos=3
wordHit4_refPos=4
./main.exe "$wordHit1_refPos" "$wordHit2_refPos" "$wordHit3_refPos" "$wordHit4_refPos"
