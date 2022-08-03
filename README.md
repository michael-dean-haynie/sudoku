# Sudoku

## Build
([cmake](https://cmake.org/install/) must be installed.)
``` sh
# generate the buildsystem (make)
cmake -S . -B build
# invoke the buildsystem (make)
cmake --build build
```

## Test
(First, the steps in [Build](#build) must be completed.)
``` sh
cd /build
# run the test target
ctest
```

## Reference Materials
- https://google.github.io/googletest/quickstart-cmake.html
- https://www.sudokuwiki.org/Strategy_Families
- https://google.github.io/styleguide/cppguide.html#Function_Names
- https://google.github.io/googletest/reference/assertions.html
- https://cliutils.gitlab.io/modern-cmake/chapters/basics/example.html

## Stretch Goals
- make this run in docker to eliminate platform issues