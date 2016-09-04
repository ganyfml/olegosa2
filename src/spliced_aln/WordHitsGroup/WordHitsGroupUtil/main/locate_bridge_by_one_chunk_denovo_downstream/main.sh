#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v 

#        1**  **
# Ref   TTGTGGAGAA
# Query TT......AA
#        1
#
#        1**  **89
# Ref   TTGTGGAGAA
# Query TT......AA
#        1      23

query=TTAA
ref=TTGTGGAGAA
head_chunk_end_pos_in_ref_and_query=(1 1)
num_backsearch=1
./main.exe "$query" "$ref" "${head_chunk_end_pos_in_ref_and_query[@]}" "$num_backsearch"

#         2
#         **  **
# Ref   TTGTGGAGGAA
# Query TTG......AA
#         2
#
#        1**  **8 10
# Ref   TTGTGGAGGAA
# Query TT......GAA
#        1      2 4

query=TTGAA
ref=TTGTGGAGGAA
head_chunk_end_pos_in_ref_and_query=(2 2)
num_backsearch=2
./main.exe "$query" "$ref" "${head_chunk_end_pos_in_ref_and_query[@]}" "$num_backsearch"

#         2
#         **  **
# Ref   TTGTGGAGAAA
# Query TTA......AA
#         2
#
#        1**  **8 10
# Ref   TTGTGGAGAAA
# Query TT......AAA
#        1      2 4

query=TTAAA
ref=TTGTGGAGAAA
head_chunk_end_pos_in_ref_and_query=(2 2)
num_backsearch=2
./main.exe "$query" "$ref" "${head_chunk_end_pos_in_ref_and_query[@]}" "$num_backsearch"
