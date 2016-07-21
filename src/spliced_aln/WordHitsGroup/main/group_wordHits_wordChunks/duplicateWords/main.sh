#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v

hits_wordIDs=(1 2 3)
./main.exe "${hits_wordIDs[@]}"

hits_wordIDs=(1 2 2 3)
./main.exe "${hits_wordIDs[@]}"
