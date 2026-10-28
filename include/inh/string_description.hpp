#pragma once

namespace inh {

// All quantities in SI units
struct StringDescription {
    double speaking_length = 0.62;      // m
    double tension = 670.0;             // N
    double core_radius = 5.0e-4;        // m
    double linear_density = 6.17e-3;    // kg/m
    double youngs_modulus = 2.0e11;     // Pa
};

// Speed in m/s at which a wave propagates on an ideal flexible string
[[nodiscard]] double wave_speed(const StringDescription& s) noexcept;

// Stiffness coefficient √(EI/μ) in m²/s, with I = πr⁴/4 the core's area moment
[[nodiscard]] double stiffness_coefficient(const StringDescription& s) noexcept;

// Fundamental frequency in Hz
[[nodiscard]] double fundamental_frequency(const StringDescription& s) noexcept;

// Inharmonicity coefficient (dimensionless)
[[nodiscard]] double inharmonicity(const StringDescription& s) noexcept;

// Frequency of partial n >= 1 in Hz, taking inharmonicity into account
[[nodiscard]] double partial_frequency(const StringDescription& s, int n) noexcept;

} // namespace inh
