#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v
seq=TCG
godown_seq=A
./main.exe "$seq" "$godown_seq" 

seq=TCG
godown_seq=TA
./main.exe "$seq" "$godown_seq" 

seq=ATCG
godown_seq=TC
./main.exe "$seq" "$godown_seq" 

