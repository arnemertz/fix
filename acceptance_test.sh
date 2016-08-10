#! /bin/bash

./conan_install.sh Debug
cd build
cmake .. && cmake --build . --target fix

PATH=$PATH:$(pwd)/bin

behave ../test/behave/


