# Sandbox Engine

**Sandbox** is a open source game engine for X11 systems.

## Features
* All code is written in C++ and OpenGL/GLEW.
* Create multiple windows with OpenGL context.
* Keyboard and mouse inputs.
* Assets loader and filesystem utilities to read and write data from/to disk.
* High resolution timer, thread safe logger and other debugging tools.
* Math library for vector and matrix algebra.
* Support both 2D and 3D rendering through GLSL shaders (eg. VAO/VBO/EBO, textures, normal maps, skybox, etc).
* Support of fonts and sprites for HUD.
* Different camera types such as first/third person and perspective/orthographic views.

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
Read the cmake file to a full list of build settings.

## Licence
**Sanbox Engine** by [Marco Carletti](https://www.marcocarletti.it/) is licensed under LGPL v3.

You may copy, distribute and modify the software provided that modifications are described and licensed for free under LGPL. Derivatives works (including modifications or anything statically linked to the library) can only be redistributed under LGPL, but applications that use the library don't have to be.

To view a copy of this license, check [LICENCE.txt](LICENCE.txt) file or visit [https://www.gnu.org/licenses/lgpl-3.0.html](https://www.gnu.org/licenses/lgpl-3.0.html).

## About the author
My name is [Marco Carletti](https://www.marcocarletti.it/).
I love computer graphics, programming and premature optimization.
That's why I started **Sanbox Engine**.
This is my playground, a place where I can have fun, learn and create OpenGL stuff.
