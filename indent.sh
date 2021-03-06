#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

while read -r f
do
  echo $f
  vim -n -X -E -c "normal gg=G" -c "x" "$f"
done < <(find src/ -name "*.cpp" -o -name "*.hpp")
