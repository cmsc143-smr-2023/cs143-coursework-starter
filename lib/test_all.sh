#!/usr/bin/env bash

set -e

for file in ./bin/*-test; do
  echo "$file:"
  ./$file
  echo
done
