#!/bin/bash

if [ -d build ]
then
  cd build
else
  mkdir build
  cd build
fi

cmake -DRUN_TESTS=ON ..
make
./test_main