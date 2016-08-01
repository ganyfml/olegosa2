#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v 

ref_seq=AATTAATTAA
anchor_seq=AA
hit_left_bound=4
hit_right_bound=5
./main.exe "$ref_seq" "$anchor_seq" "$hit_left_bound" "$hit_right_bound"

ref_seq=AATTAATTAA
anchor_seq=AA
hit_left_bound=0
hit_right_bound=5
./main.exe "$ref_seq" "$anchor_seq" "$hit_left_bound" "$hit_right_bound"
