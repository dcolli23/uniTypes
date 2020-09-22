#!/bin/bash

if [ -d build ]
then
  cd build
else
  mkdir build
  cd build
fi

if [ -f test_main ]
then
  rm test_main
fi

cmake -DRUN_TESTS=ON ..
make

# Run the test suites.
if [ -f test_main ]
then
  ./test_main
else
  echo "Build failed!"
fi