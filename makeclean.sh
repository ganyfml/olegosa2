#!/usr/bin/env bash
# vim: set noexpandtab tabstop=2:

find -name "*.o" -delete
find -name "*.exe" -delete
rm -rf $(find -name ".makepp")
