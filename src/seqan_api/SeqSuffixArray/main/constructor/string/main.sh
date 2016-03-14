#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

tmpdir=$(mktemp -d)
./save.exe "$tmpdir/index"
./main.exe "$tmpdir/index"
