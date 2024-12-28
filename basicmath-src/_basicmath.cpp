// #include <nanobind/nanobind.h>
#include <pybind11/pybind11.h>

#include "./miller_rabin.hpp"

// NB_MODULE(_basicmath, m) {
PYBIND11_MODULE(_basicmath, m) {
    m.def("miller_rabin", &miller_rabin);
}