This document describes the process for running this application on your local computer.

## Dependencies

Make sure you have the following dependencies installed:

- [git](https://git-scm.com/)
- [LLVM w/ clang-tools](https://github.com/llvm/llvm-project/releases/)
- a C++23 compliant compiler ([LLVM](https://github.com/llvm/llvm-project/releases)/ [MSVC w/ Visual Studio](https://visualstudio.microsoft.com))
- [CMake](https://cmake.org)

## Getting the source code

Once you have `Git` installed, run:
```commandline
git clone https://github.com/es3n1n/portal2-internal
```

Once you've done that, the whole updated source should be available in the portal2-internal.

## Building

### On Windows

#### With Visual Studio

Using Visual Studio GUI
- Open the `msvc/portal2-internal.sln` file. Compile.
Using CMake
- Open the `msvc/` directory in command line and run:
```commandline
cd portal2-internal/msvc
msbuild portal2-internal.sln /p:Configuration=Debug
```

#### With CMake
Run from the command line:
```commandline
cd portal2-internal/
cmake -B build -A Win32
cmake --build build --config Debug
```
