#! /bin/bash

mkdir -p build
cd build
CONAN_ARGS="-s build_type=$1"
if [ $1 == Debug ]; then
    CONAN_ARGS+=" -o Poco:cxx_14=True"
fi
CONAN_ARGS+=" --build missing"
conan install .. ${CONAN_ARGS}
