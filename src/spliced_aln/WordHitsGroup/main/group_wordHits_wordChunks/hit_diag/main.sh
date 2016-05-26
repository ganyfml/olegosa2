#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v
hit1_ref_pos=2
hit1_query_pos=1
hit2_ref_pos=3
hit2_query_pos=2
./main.exe "$hit1_ref_pos" "$hit1_query_pos" "$hit2_ref_pos" "$hit2_query_pos"


hit1_ref_pos=2
hit1_query_pos=1
hit2_ref_pos=10
hit2_query_pos=2
./main.exe "$hit1_ref_pos" "$hit1_query_pos" "$hit2_ref_pos" "$hit2_query_pos"
