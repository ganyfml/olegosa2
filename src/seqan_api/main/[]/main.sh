#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:
set -v

genomeFolder='../../../../test_data/chr1.fa'
tmpdir=$(mktemp -d)
<<<<<<< HEAD

./main.exe "$genomeFolder" "$tmpdir"
=======
seqIndex=1

./main.exe "$genomeFolder" "$tmpdir" "$seqIndex"
>>>>>>> 7fd46dc42701f81650945fa10d4b7f6d04ddba9d
