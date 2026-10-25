#include <nanobind/nanobind.h>
#include <nanobind/stl/string_view.h>

#include "inh/version.hpp"

namespace nb = nanobind;

NB_MODULE(_core, m) {
    m.doc() = "Inharmonic engine bindings";
    m.def("version", &inh::version, "Engine version string.");
}
