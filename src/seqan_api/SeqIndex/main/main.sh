#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

tmpdir=$(mktemp -d)
./main.exe "$tmpdir/Index"
