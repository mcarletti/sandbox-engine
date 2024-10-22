# Sandbox Engine

<img src="assets/public/shovel.png" alt="sandbox-logo" width="128"/>

**Sandbox** is a open source game engine for X11 systems.

## Features
* All code is written in C++ and OpenGL/GLEW.
* Create multiple windows with OpenGL context.
* Keyboard and mouse inputs.
* Assets loader and filesystem utilities to read and write data from/to disk.
* High resolution timer, thread safe logger and other debugging tools.
* Math library for vector and matrix algebra.
* Support both 2D and 3D rendering through GLSL shaders.

**Sandbox Engine** is in constant development.  
Checkout the release notes to view the latest features.

## Getting started
**Sandbox** is a pure C++ library you can include in your own projects.  
The only requirements are X11, OpenGL and GLEW.

The engine offers a (hopefully) easy-to-use API and you can refer to the `examples` folder to see how to use the engine in practice.

Before creating amazing applications, you need to get a copy of the repository and compile the source code using CMake.

### Install dependencies
```bash
sudo apt update
sudo apt install build-essential cmake git
sudo apt install mesa-common-dev libglew-dev
```

### Build Sandbox Engine
```bash
# retrieve source code and move into
git clone https://github.com/mcarletti/sandbox-engine.git
cd sandbox-engine

# prepare output folder
mkdir -p build/cmake_cache
cd build/cmake_cache

# generate the project and compile
cmake ../..
make -j4
```

Now you are free to include the `include` folder and link the compiled libraries in your project.

Additional options could be passed to the cmake command to customize the build process. Options could be passed as `-DNAME=VALUE` and can be combined together.  
Read the cmake file to a full list of build settings. Here, a few examples:

```bash
# build the engine with samples
cmake ../.. -DBUILD_SAMPLES=1

# build the engine with debug symbols
cmake ../.. -DCMAKE_BUILD_TYPE=Debug

# build the engine with release symbols (default)
cmake ../.. -DCMAKE_BUILD_TYPE=Release

# build the engine in double precision
cmake ../.. -DDOUBLE_PRECISION=1
```

### Run examples

Move to the root directory and run the example you want to test. For example:

```bash
./build/Release/bin/00_create_window
```

<img src="assets/public/hello-sandbox.png" alt="screenshot" width="420"/>

### Generate documentation

The documentation is generated using [Doxygen](https://www.doxygen.nl/) and [Doxygen Awesome](https://github.com/jothepro/doxygen-awesome-css) theme.  
Simply run the following command to generate the documentation in the `doc` folder.

```bash
doxygen doxygen.conf
```

## Licence
**Sandbox Engine** by [Marco Carletti](https://www.marcocarletti.it/) is licensed under LGPL v3.

You may copy, distribute and modify the software provided that modifications are described and licensed for free under LGPL. Derivatives works (including modifications or anything statically linked to the library) can only be redistributed under LGPL, but applications that use the library don't have to be.

To view a copy of this license, check [LICENCE.txt](LICENCE.txt) file or visit [https://www.gnu.org/licenses/lgpl-3.0.html](https://www.gnu.org/licenses/lgpl-3.0.html).

## About the author
My name is [Marco Carletti](https://www.marcocarletti.it/). I love computer graphics, programming and premature optimization. That's why I started **Sandbox Engine**. This is my playground, a place where I can have fun, learn and create OpenGL stuff.
