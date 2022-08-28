# Sudoku

Solves sudoke puzzles

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

## CLion

It's not required, but this project was developed using the CLion IDE.
CLion-specific instructions were based on CLion 2022.2.1.

### CLion Project Setup

#### Clone the project locally

```shell
git clone https://github.com/michael-dean-haynie/sudoku.git
```

#### Open the porject in CLion

Start CLion and use the `Open` option to open a project from disk. DO NOT simply open the folder of the git repo. Instead, open the root level `CMakeLists.txt` file and, when prompted, select the `Open as Project` option.

#### Load the CMake project

We'll use the shared CMake profile in `.idea/cmake.xml`. CLion will (sometimes?) automatically load the CMake project. If you see a red x on the run configuration dropdown (or it says "Nothing to run on"), that means the CMake project was not loaded, and we'll have to it manually:

- Open the `CMakeLists.txt` file from the `Project` tool window.
- At the top of the editor window you should see a message: "CMake project is not loaded". If you do not see this message, we'll need to invalidate CLion's caches:
  - Double tap `SHIFT` to open the `Search Everywhere` window.
  - Type in "Invalidate Caches" and hit `Enter` to select the first result.
  - Check all 3 boxes and click the `Invalidate and Restart` button.

Click the `Load CMake Project` text at the top of the `CMakeLists.txt` editor window.

#### Auto-Reload CMake Project

- Open Preferences with `Cmd`+`,`
- Select `Build, Execution, Deployment` > `CMake`
- Check the "Reload Cmake project ..." option
- Click `Apply`, then `OK` to close preferences

### CLion Development

#### Run Configurations

Some helpful run configurations have been saved under the `.run/` directory. For these to work, the CMake project needs to have been loaded (see [Load the CMake project](#load-the-cmake-project)).

- The `Custom` > `Debug App ...` RCs are useful for general debugging with example sudoku puzzles as input.
- The `Run App Slow ...` RCs are useful for watching the slowed-down execution using example sudoku puzzles as input.
  - One of the `Custom` > `Debug App ...` RCs need to be executed before these can run. This is because these are shell scripts that don't build the project first.
- The `tests` RC executes all the unit tests.

## Reference Materials

- https://google.github.io/googletest/quickstart-cmake.html
- https://www.sudokuwiki.org/Strategy_Families
- https://google.github.io/styleguide/cppguide.html#Function_Names
- https://google.github.io/googletest/reference/assertions.html
- https://cliutils.gitlab.io/modern-cmake/chapters/basics/example.html

## Stretch Goals

- make this run in docker to eliminate platform issues
- update the slow flag to re-write console history instead of blowing it up.

