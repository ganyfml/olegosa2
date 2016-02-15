#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:
set -v

genomeFolder='../../../../test_data/chr1.fa'
tmpdir=$(mktemp -d)

./main.exe "$genomeFolder"
