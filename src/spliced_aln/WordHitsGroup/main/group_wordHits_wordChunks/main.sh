#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v
hit0_ref_pos=2
hit0_query_pos=1
hit1_ref_pos=3
hit1_query_pos=2
./main.exe "$hit0_ref_pos" "$hit0_query_pos" "$hit1_ref_pos" "$hit1_query_pos"


hit0_ref_pos=2
hit0_query_pos=1
hit1_ref_pos=10
hit1_query_pos=2
./main.exe "$hit0_ref_pos" "$hit0_query_pos" "$hit1_ref_pos" "$hit1_query_pos"
