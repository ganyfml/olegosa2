#!/usr/bin/env bash

mkdir -p include
cd ./include
rm -rf *
while read -r f
do
  foldname=$(echo $f | awk '{split($1, a, "/"); print a[3]}')
  mkdir -p $foldname
  while read -r hpp
  do
    ln -f -s "../$hpp" "$foldname/"
  done < <(find $(dirname $f) -name "*hpp")
done < <(find ../src -name ".export")
cd -
