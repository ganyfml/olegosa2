#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v 

#         **  **89
# Ref   TTGTGGAGAA
# Query TT......AA
#               23
#
#       01**  **89
# Ref   TTGTGGAGAA
# Query TT......AA
#       01      23

query=TTAA
ref=TTGTGGAGAA
tail_chunk_start_pos_in_ref_and_query=(8, 2)
num_backsearch=1
./main.exe "$query" "$ref" "${tail_chunk_start_pos_in_ref_and_query[@]}" "$num_backsearch"

#              7
#         **  **
# Ref   TGGTGGAGAA
# Query T......GAA
#              1
#
#       01**  **89
# Ref   TGGTGGAGAA
# Query TG......AA
#       01      23

query=TGAA
ref=TGGTGGAGAA
tail_chunk_start_pos_in_ref_and_query=(7, 1)
num_backsearch=2
./main.exe "$query" "$ref" "${tail_chunk_start_pos_in_ref_and_query[@]}" "$num_backsearch"

#              7
#         **  **
# Ref   TTGTGGAGAA
# Query T......TAA
#              1
#
#       01**  **89
# Ref   TTGTGGAGAA
# Query TT......AA
#       01      23

query=TTAA
ref=TTGTGGAGAA
tail_chunk_start_pos_in_ref_and_query=(7, 1)
num_backsearch=2
./main.exe "$query" "$ref" "${tail_chunk_start_pos_in_ref_and_query[@]}" "$num_backsearch"
