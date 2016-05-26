#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v
hit1_wordID=1
hit2_wordID=2
hit3_wordID=3
./main.exe "$hit1_wordID" "$hit2_wordID" "$hit3_wordID"

hit1_wordID=1
hit2_wordID=2
hit3_wordID=1
./main.exe "$hit1_wordID" "$hit2_wordID" "$hit3_wordID"
