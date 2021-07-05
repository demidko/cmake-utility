# conan-utility

A cross-platform `C++20` command line tool template with dependency manager, powered by integration
of [`cmake`](https://cmake.org/)
with [`conan`](https://github.com/conan-io/cmake-conan).

## Usage

Make sure you are signed in to your GitHub account, then just
click [`here`](https://github.com/demidko/conan-utility/generate) to use template.

## Motivation and goals

In the С++ world, now...

* When an idea comes up, you have to create manually `CMakeLists.txt`,` README.md`, a directories structure, or finish
  the project created by the IDE to a portable state.
* There is no dependency management without difficulties.
* There is no cross-platform build without Qt.
* These problems overlap, causing troubles for developers.

Therefore, `conan-utility` is a template for creating and building cross-platform C++ projects with external
dependencies. `conant-utility` is a tool like `start.your-technology.io` sites for Java, .NET and Rust.

## Features and benefits

* Full compatibility with existing technologies. No build configuration files are added except for the
  traditional `CMakeLists.txt`.
* Created projects are supported in `CLion`,` Visual Studio`, `VS Code` IDEs.
* Adding dependencies is done with one command through integration with [`conan`](https://conan.io).
* A project with all dependencies can be built on different OS without configuration changes.

### Build

We need [`cmake`](https://cmake.org/download) build system and [`conan`](https://conan.io) manager libraries. It's easy
to install with system package manager, `brew` for example.

1. Prepare the directory for building using the dependencies:
   ```shell
   cmake -DCMAKE_BUILD_TYPE=Release -G "Unix Makefiles" -B cmake-build-release
   ```
1. Putting together the directory and tests:
   ```shell
   cmake --build cmake-build-release --target all
   ```  
   After that, the main self-executable utility will appear in the `cmake-build-release` directory under the
   name `conan-utility`. The tests can be run by launching the `test` file located nearby.

### This repository source code conventions

* The entry point must be located in the `Main.cpp` file for correct build script work.
* To initialize resources, we using [modern parameter passing by value](https://habr.com/ru/post/460955/), rather than a
  constant link.
* Only the result of the compilation of `* .cpp` files in the` src` folder is included in the release assembly.
* The `src` folder contains the` *.cpp` and `*.h` project files together.
* The `test` folder contains the` *.cpp` and `*.h` project test files together.
* Each `*.h` file must define only one entity in the global namespace, whose name must match the file name.
* The contents of `*.cpp` files not declared in` *.h` file must be protected from `external linkage` from others
  compilation units by adding them to the anonymous namespace or adding the keyword `static`.
