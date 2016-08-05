#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v 
#                       16
#        1**  **89**  **|
# Ref   TTGTGGAGAAGTGGAGTT
# Query TT......AA......TT
#        1      23      4

query=TTAATT
ref=TTGTGGAGAAGTGGAGTT
head_chunk_end_pos_in_ref_and_query=(1 1)
tail_chunk_start_pos_in_ref_and_query=(16 4)
num_backsearch=1
./main.exe "$query" "$ref" "${head_chunk_end_pos_in_ref_and_query[@]}" "${tail_chunk_start_pos_in_ref_and_query[@]}" "$num_backsearch"

#                       16
#        1**  **89**  **|
# Ref   TTGTGGAGAAGTGGAGTT
# Query TA......AA......TT
#        1      23      4

query=TTAATT
ref=TTGTGGAGAAGTGGAGTT
head_chunk_end_pos_in_ref_and_query=(1 1)
tail_chunk_start_pos_in_ref_and_query=(16 4)
num_backsearch=1
./main.exe "$query" "$ref" "${head_chunk_end_pos_in_ref_and_query[@]}" "${tail_chunk_start_pos_in_ref_and_query[@]}" "$num_backsearch"
