#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v 

#        1**  **  **  **16
# Ref   TTGTGGAGGGGTGGAGTT
# Query TT...GG...TT
#        1        4

query=TTGGTT
ref=TTGTGGAGGGGTGGAGTT
head_chunk_end_pos_in_ref_and_query=(1 1)
tail_chunk_start_pos_in_ref_and_query=(16 4)
num_backsearch=1
./main.exe "$query" "$ref" "${head_chunk_end_pos_in_ref_and_query[@]}" "${tail_chunk_start_pos_in_ref_and_query[@]}" "$num_backsearch"
