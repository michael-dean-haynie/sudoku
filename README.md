# Sudoku

## Build / Test / Run

[cmake](https://cmake.org/install/) must be installed.

Delete any existing cmake artifacts:

``` sh
rm -rf ./build
```

Generate the build system:

``` sh
cmake -S . -B build
```

Invoke the build system:

``` sh
cmake --build build
```

Run the tests:

``` sh
ctest --test-dir build/test --output-on-failure
```

Debug the tests with gdb:

```
gdb build/test/tests
(gdb) run
```

Run the app:

``` sh
build/src/app < input/sudoku-hard.txt
```

## Reference Materials

- https://google.github.io/googletest/quickstart-cmake.html
- https://www.sudokuwiki.org/Strategy_Families
- https://google.github.io/styleguide/cppguide.html#Function_Names
- https://google.github.io/googletest/reference/assertions.html
- https://cliutils.gitlab.io/modern-cmake/chapters/basics/example.html

## Stretch Goals

- make this run in docker to eliminate platform issues
