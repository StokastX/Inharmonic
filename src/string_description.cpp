#include "inh/string_description.hpp"

#include <cmath>
#include <numbers>

namespace inh {

double wave_speed(const StringDescription& s) noexcept {
    return std::sqrt(s.tension / s.linear_density);
}

double stiffness_coefficient(const StringDescription& s) noexcept {
    const double r_2 = s.core_radius * s.core_radius;
    const double area_moment = std::numbers::pi * r_2 * r_2 / 4.0;
    return std::sqrt(s.youngs_modulus * area_moment / s.linear_density);
}

double fundamental_frequency(const StringDescription& s) noexcept {
    return wave_speed(s) / (2.0 * s.speaking_length);
}

double inharmonicity(const StringDescription& s) noexcept {
    const double root = std::numbers::pi * stiffness_coefficient(s) / (wave_speed(s) * s.speaking_length);
    return root * root;
}

double partial_frequency(const StringDescription& s, int n) noexcept {
    return n * fundamental_frequency(s) * std::sqrt(1.0 + inharmonicity(s) * n * n);
}

} // namespace inh
