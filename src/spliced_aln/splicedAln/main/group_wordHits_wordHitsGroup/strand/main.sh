#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v
hit1_strand=1
hit2_strand=1
hit3_strand=1
./main.exe "$hit1_strand" "$hit2_strand" "$hit3_strand"

hit1_strand=0
hit2_strand=1
hit3_strand=1
./main.exe "$hit1_strand" "$hit2_strand" "$hit3_strand"

hit1_strand=1
hit2_strand=0
hit3_strand=1
./main.exe "$hit1_strand" "$hit2_strand" "$hit3_strand"

hit1_strand=1
hit2_strand=1
hit3_strand=0
./main.exe "$hit1_strand" "$hit2_strand" "$hit3_strand"
