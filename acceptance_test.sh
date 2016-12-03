#! /bin/bash

./conan_install.sh Debug
cd build
cmake .. && cmake --build . --target fix

PATH=$PATH:$(pwd)/bin
cd ..

if [ $# -eq 0 ]; then
    behave test/behave/ $@
else
    behave $@
fi


