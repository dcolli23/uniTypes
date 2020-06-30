#!/bin/bash

if [ -d build ]
then
  rm -rf build
fi

mkdir build && cd build
cmake -DBUILD_TESTS=ON ..
make
./test_main