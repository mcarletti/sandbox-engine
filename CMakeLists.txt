# set cmake requirements and project info
cmake_minimum_required(VERSION 3.16.3 FATAL_ERROR)
project("sandbox")

# list of supported settings the user can set:
#
# CMAKE_BUILD_TYPE      default: Release
# BUILD_SAMPLES         default: 0
# DOUBLE_PRECISION      default: unset/0

# set default values for undefined options
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()
add_definitions(-D __${CMAKE_BUILD_TYPE})

if(NOT BUILD_SAMPLES)
set(BUILD_SAMPLES 0)
endif()

if(NOT DOUBLE_PRECISION)
set(DOUBLE_PRECISION 0)
else()
add_definitions(-D __DOUBLE_PRECISION)
endif()

message("Build type:       " ${CMAKE_BUILD_TYPE})
message("Build samples:    " ${BUILD_SAMPLES})
message("Double precision: " ${DOUBLE_PRECISION})

# set compilatoin flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS                "${CMAKE_CXX_FLAGS}                -std=c++17 -Wall")
set(CMAKE_CXX_FLAGS_DEBUG          "${CMAKE_CXX_FLAGS_DEBUG}          -O0 -g  -ggdb -rdynamic")
set(CMAKE_CXX_FLAGS_RELEASE        "${CMAKE_CXX_FLAGS_RELEASE}        -O2 -g0      ")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -O2     -ggdb")

# set output folders
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/lib)

# retrieve dependencies
find_package(X11 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

# get all include and source paths
include_directories("include")
file(GLOB_RECURSE sources_sandbox  "source/sandbox/*.cpp")

# build sandbox engine as a shared library
add_library(${PROJECT_NAME} SHARED ${sources_sandbox})
target_link_libraries(${PROJECT_NAME} PUBLIC X11::X11 OpenGL::GL OpenGL::GLU GLEW::GLEW)

# compile all engine example scripts
if(BUILD_SAMPLES)
    add_executable(00_create_window "source/examples/00_create_window.cpp")
    target_link_libraries(00_create_window PUBLIC ${PROJECT_NAME})

    add_executable(01_shaders_and_vao "source/examples/01_shaders_and_vao.cpp")
    target_link_libraries(01_shaders_and_vao PUBLIC ${PROJECT_NAME})

    add_executable(02_textures "source/examples/02_textures.cpp")
    target_link_libraries(02_textures PUBLIC ${PROJECT_NAME})

    add_executable(03_transforms "source/examples/03_transforms.cpp")
    target_link_libraries(03_transforms PUBLIC ${PROJECT_NAME})

    add_executable(04_model_view_projection "source/examples/04_model_view_projection.cpp")
    target_link_libraries(04_model_view_projection PUBLIC ${PROJECT_NAME})
endif()