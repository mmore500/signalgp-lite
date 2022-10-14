#!/bin/bash

shopt -s globstar
for f in include/**/*.hpp; do
  echo "${f}"
  printf "#include \"${f}\"\nint main(){}" | g++ -std=c++17 -x c++ - &
  printf "#include \"${f}\"\nint main(){}" | clang++ -std=c++17 -DUIT_VENDORIZE_EMP -x c++ - &

  # adapted from https://unix.stackexchange.com/a/436713
  if [[ $(jobs -r -p | wc -l) -ge 2 ]]; then
      # now there are $N jobs already running, so wait here for any job
      # to be finished so there is a place to start next one.
      wait -n
  fi
done
