#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v 

#        1 ** ** 9
# Ref   AATGTGAGATTT
# Query AAGG.....TTT
#        1       4
#
#        1 ** ** 9
# Ref   AATGTGAGATTT
# Query AAG.....GTTT
#        1       4

query=AAGGTTT
ref=AATGTGAGATTT
head_chunk_end_pos_in_ref_and_query=(1 1)
tail_chunk_start_pos_in_ref_and_query=(9 4)
num_backsearch=1

./main.exe "$query" "$ref" "${head_chunk_end_pos_in_ref_and_query[@]}" "${tail_chunk_start_pos_in_ref_and_query[@]}" "$num_backsearch"

#        1 ** ** 9
# Ref   AATGTGAGATTT
# Query AATG.....TTT
#        1       4
#
#        1 ** ** 9
# Ref   AATGTGAGATTT
# Query AAT.....GTTT
#        1       4

query=AATGTTT
ref=AATGTGAGATTT
head_chunk_end_pos_in_ref_and_query=(1 1)
tail_chunk_start_pos_in_ref_and_query=(9 4)
num_backsearch=1

./main.exe "$query" "$ref" "${head_chunk_end_pos_in_ref_and_query[@]}" "${tail_chunk_start_pos_in_ref_and_query[@]}" "$num_backsearch"
