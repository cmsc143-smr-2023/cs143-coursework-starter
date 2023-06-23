#!/usr/bin/env bash
# this script is used to create the reference files for task 1
# Usage: ./create-refs.sh

function do_directory {
  dir=$1 # get the first argument
  for file in $1/*.txt; do
    name=`basename $file .txt` # remove dir and .txt

    python3 encrypt.py < $file > $dir/$name.enc
    python3 freq.py < $file > $dir/$name.freq
  done
}

do_directory tests
do_directory big-tests

