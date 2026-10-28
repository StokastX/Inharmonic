#include <doctest/doctest.h>

#include "inh/string_description.hpp"

namespace {

// Relative comparison: doctest::Approx adds an absolute 1.0 to its
// tolerance, which makes it meaningless for small values
doctest::Approx relative(double value, double tolerance = 1e-9) {
    return doctest::Approx(value).epsilon(tolerance).scale(0.0);
}
} // namespace

TEST_CASE("Default string has C4 values") {
    const inh::StringDescription s;
    CHECK(inh::fundamental_frequency(s) == relative(265.75, 1e-4));
    CHECK(inh::inharmonicity(s) == relative(3.762e-4, 1e-3));

}

TEST_CASE("String scaling laws") {
    inh::StringDescription s;
    const double f0 = inh::fundamental_frequency(s);
    const double B = inh::inharmonicity(s);

    SUBCASE("With E = 0.0, partials are harmonic") {
        s.youngs_modulus = 0.0;
        CHECK(inh::partial_frequency(s, 4) == relative(f0 * 4.0));
    }

    SUBCASE("Stiffness raises partials above harmonics") {
        CHECK(inh::partial_frequency(s, 4) > 4.0 * f0);
    }

    SUBCASE("Doubling speaking_length halves f0 and divides B by 4") {
        s.speaking_length *= 2.0;
        CHECK(inh::fundamental_frequency(s) == relative(f0 / 2.0));
        CHECK(inh::inharmonicity(s) == relative(B / 4.0));
    }

    SUBCASE("Quadrupling tension doubles f0") {
        s.tension *= 4.0;
        CHECK(inh::fundamental_frequency(s) == relative(f0 * 2.0));
    }
}
