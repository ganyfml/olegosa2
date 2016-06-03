#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v
hit1_ref_pos=1
hit2_ref_pos=2
hit3_ref_pos=3
./main.exe "$hit1_ref_pos" "$hit2_ref_pos" "$hit3_ref_pos"

hit1_ref_pos=1
hit2_ref_pos=202
hit3_ref_pos=203
./main.exe "$hit1_ref_pos" "$hit2_ref_pos" "$hit3_ref_pos"

hit1_ref_pos=1
hit2_ref_pos=2
hit3_ref_pos=203
./main.exe "$hit1_ref_pos" "$hit2_ref_pos" "$hit3_ref_pos"

hit1_ref_pos=1
hit2_ref_pos=202
hit3_ref_pos=403
./main.exe "$hit1_ref_pos" "$hit2_ref_pos" "$hit3_ref_pos"
