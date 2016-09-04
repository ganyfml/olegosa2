#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v

ref=GCTGAATAATCACCAGAGCTTCTCATGCCGCTGAGGGAATCTAAAAGAATTAT
query=GAATAATCACCAGAGCTTCTCATGCCGCTGAGGGAATCTAAAAGAATTAT
gap_open=2
gap_ext=2
gap_mm=0
max_mutation=6
./main.exe "$ref" "$query" "$gap_ext" "$gap_open" "$gap_mm" "$max_mutation"
