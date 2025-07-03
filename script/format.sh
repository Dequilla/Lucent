#!/bin/bash

path=$1

if [ ! -d "$path" ]; then
  echo "$path does not exist, cannot format."
fi

echo "Formatting with clang-format $path..."
find $path -iname '*.h' -o -iname '*.cpp' -o -iname '*.hpp' | xargs clang-format -i
