#include <pybind11/pybind11.h>

#include "./miller_rabin.hpp"

PYBIND11_MODULE(_basicmath, m) {
    m.def("miller_rabin", &miller_rabin);
}