# Sudoku

## Build
([cmake](https://cmake.org/install/) must be installed.)
``` sh
cmake -S . -B build
cmake --build build
```

## Test
(First, the steps in [Build](#build) must be completed.)
``` sh
cd /build
ctest
```

## Reference Materials
- https://google.github.io/googletest/quickstart-cmake.html
- https://www.sudokuwiki.org/Strategy_Families

## Stretch Goals
- make this run in docker to eliminate platform issues