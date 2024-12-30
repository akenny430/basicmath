cmake_minimum_required(VERSION 3.15...3.27)

project(
    ${SKBUILD_PROJECT_NAME}
    VERSION ${SKBUILD_PROJECT_VERSION}
    LANGUAGES CXX
)

find_package(Python REQUIRED COMPONENTS Interpreter Development.Module)

find_package(nanobind CONFIG REQUIRED)

nanobind_add_module(
    _basicmath
    STABLE_ABI
    NB_STATIC
    # binding file
    basicmath-src/py_bindings.cpp
    # src files
    basicmath-src/miller_rabin.cpp
    basicmath-src/miller_rabin.hpp
)

install(TARGETS _basicmath LIBRARY DESTINATION basicmath)
