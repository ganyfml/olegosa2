#!/usr/bin/env bash

cd ./include
rm -rf *
while read -r f
do
  ln -f -s "$f" .
done < <(find ../src -name "*hpp")
cd -
