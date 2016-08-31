#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v

worst_score=14
./main.exe "$worst_score"

worst_score=13
./main.exe "$worst_score"
