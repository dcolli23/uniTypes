# uniTypes

# Table of Contents

- [uniTypes](#unitypes)
- [Table of Contents](#table-of-contents)
- [Overview](#overview)
- [Usage](#usage)
- [Building](#building)
  - [Building The App From Scratch](#building-the-app-from-scratch)
  - [Building The App Without Rebuilding The Testing Framework](#building-the-app-without-rebuilding-the-testing-framework)
- [Testing](#testing)
  - [Running Tests](#running-tests)
  - [Writing Tests](#writing-tests)

# Overview

A header only implementation of units that I use for other projects. This was initially based  on [this writeup](https://benjaminjurke.com/content/articles/2015/compile-time-numerical-unit-dimension-checking/) but has since grown in complexity to address problems/features I needed as they arose.

# Usage

uniTypes is a header-only library so using it is as simple as copying the file into your existing project and `#include`-ing it.

Everything in uniTypes is encapsulated in the `uniTypes` namespace. To make use of the custom-defined literals, include the following line in your project files that utilize the literals:

```cpp
using namespace uniTypes::string_literals;
```

# Building

This project is built using CMake. I've included several bash scripts to aid in building this project.

Note that this project requires C++ 17.

## Building The App From Scratch

To rebuild everything from scratch, use the `rebuild_everything.sh` bash script by entering the following into the command line:

```
./rebuild_everything.sh
```

This will scrap everything that has been built previously and will build the application, test suites, and testing framework from scratch. The script will then run the test suites to ensure that everything is working properly.

## Building The App Without Rebuilding The Testing Framework

To build the app on top of any existing builds that you've ran (for example when making changes to the source code) without rebuilding the testing framework, enter the following into the command line:

```
./rebuild_app_only.sh
```

This just encorporates any changes that you've made to the application and test suites since your last build without rebuilding the testing framework. The script then executes the tests that you have written.

# Testing

This repo uses [GoogleTest](https://github.com/google/googletest) for it's testing framework.

## Running Tests

As mentioned in the [Building](#building) sections, whenever the application is built or rebuilt, the test suites are ran after the build has completed. However, if you would like to run the test suite manually, do the following after the application, test suites, and testing framework have been built:


+ From the root of the repository, execute the following command:
    ```
    ./build/test_main
    ```

## Writing Tests

This project uses the `googletest` framework for testing functionality. This is the process for writing a new test suite.

Note: Test suite is used to refer to a new group of tests indepenedent from other tests. In this repository, we're making a new header file for each test suite and writing a new test suite for each class.

1. Make a new `.h` file in the `/tests/include` directory of the repository. 
    + The name of the new header file should be the name of the class under test concatenated with `Test.h`. Example:
        If you're testing `MyClass`, the name of the header file would be `MyClassTest.h`.
2. In the new `<test_suite>.h` file, write the following as boilerplate:
    ```cpp
    #include "<name_of_class_under_test>"
    #include "gtest/gtest.h"

    // insert any test fixtures here.

    TEST(<test_suite_name>, <test_name>) {
      // insert code for test here using:
      //    ASSERT_*(x, y) when you want the test to halt on failure.
      //    EXPECT_*(x, y) when you want the test to continue upon failure.
      //                   The EXPECT is best practice.
    }
    ```
    You can read more about test fixtures in the google test documentation.
3. Write the first test that you would like.
4. In `tests/main.cpp`, `#include` your new test suite header file.
