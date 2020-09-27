#!/bin/bash

if [ -d build ]
then
  rm -rf build
fi

mkdir build && cd build
cmake -DBUILD_TESTS=ON ..
make

# Run the test suites.
if [ -f test_main ]
then
  ./test_main
else
  export RED_FONT_COLOR='\033[0;31m'
  echo -e "${RED_FONT_COLOR}Build failed!"
fi