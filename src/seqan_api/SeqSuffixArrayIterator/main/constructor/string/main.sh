#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

tmpdir=$(mktemp -d)
./save.exe "$tmpdir/SA"
./main.exe "$tmpdir/SA"
