#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:
set -v

genomeFolder='../../../../test_data/chr1.fa'
tmpdir=$(mktemp -d)
seqIndex=1

./main.exe "$genomeFolder" "$tmpdir" "$seqIndex"
