#include <nanobind/nanobind.h>

#include "./miller_rabin.hpp"

NB_MODULE(_basicmath, m) {
    m.def("miller_rabin", &miller_rabin);
}