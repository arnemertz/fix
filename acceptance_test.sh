#! /bin/bash

set -e

./conan_install.sh Debug
cd cmake-build-debug
cmake .. && cmake --build . --target fix
if [ $? -ne 0 ]; then
  exit
fi

PATH=$PATH:$(pwd)/bin
cd ..

if [ $# -eq 0 ]; then
    behave test/behave/ $@
else
    behave $@
fi


