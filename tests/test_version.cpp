#include <doctest/doctest.h>

#include "inh/version.hpp"

TEST_CASE("version string is set") {
    CHECK(inh::version() == "0.1.0");
}
