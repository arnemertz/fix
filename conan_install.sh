#! /bin/bash

CONFIGURATION=$1

if [ "${CONFIGURATION}" == "Debug" ]; then
    BUILD_DIR=cmake-build-debug
elif [ "$CONFIGURATION" == "Release" ]; then
    BUILD_DIR=cmake-build-release
else
    echo "Configuration missing (Debug|Release)"
    exit 1
fi
mkdir -p ${BUILD_DIR}
cd ${BUILD_DIR}

CONAN_ARGS="-s build_type=${CONFIGURATION} --build missing"
conan install .. ${CONAN_ARGS}
