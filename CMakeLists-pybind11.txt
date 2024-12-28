cmake_minimum_required(VERSION 3.15...3.27)

project(
    ${SKBUILD_PROJECT_NAME}
    VERSION ${SKBUILD_PROJECT_VERSION}
    LANGUAGES CXX
)

find_package(Python REQUIRED COMPONENTS Interpreter Development.Module)

set(PYBIND11_NEWPYTHON ON)
find_package(pybind11 CONFIG REQUIRED)

pybind11_add_module(
    _basicmath MODULE
    basicmath-src/_basicmath.cpp
    basicmath-src/miller_rabin.cpp
    basicmath-src/miller_rabin.hpp
)
target_link_libraries(_basicmath PRIVATE pybind11::headers)
target_compile_definitions(_basicmath PRIVATE VERSION_INFO=${PROJECT_VERSION})

install(TARGETS _basicmath DESTINATION ${SKBUILD_PROJECT_NAME})
