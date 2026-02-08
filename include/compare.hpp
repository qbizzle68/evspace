#ifndef __EVSPACE_COMPARE_HPP__
#define __EVSPACE_COMPARE_HPP__

#include <cmath>        // std::isnan
#include <cstdint>      // int64_t
#include <cstring>      // std::memcpy

namespace evspace
{

static constexpr double DEFAULT_REL_TOL = 1e-9;
static constexpr double DEFAULT_ABS_TOL = 1e-15;
    
// Casts the IEEE 754 representation of a 64-bit double
// to it's bit representation in a uint64_t and then
// adjusts the bits to ensure lexicographically monontonic
// ordering for all bit numeric values.
inline std::uint64_t _ordered_cast_u64(double x)
{
    uint64_t c;
    std::memcpy(&c, &x, sizeof(double));
    
    // invert negative values so they appear less than
    // positive values (MSB is 0).
    if (c & (1LL << 63)) {
        return ~c;
    }
    // positive values flip the sign bit to 1 so they are
    // larger than negative values.
    else {
        return c | (1LL << 63);
    }
}

// ULP based comparison of two double values. `max_ulps` can be
// used to determine the maximum number of ULPs `a` and `b` can
// differ by and still be considered equal.
inline bool
_double_almost_equal(double a, double b, std::size_t max_ulps = 10)
{
    if (a == b) {
        return true;
    }

    if (!std::isfinite(a) || !std::isfinite(b)) {
        return false;
    }
    
    if (std::isnan(a) || std::isnan(b)) {
        return false;
    }
    
    std::uint64_t a_int = _ordered_cast_u64(a);
    std::uint64_t b_int = _ordered_cast_u64(b);
    
    return (a_int < b_int ? b_int - a_int : a_int - b_int) <= max_ulps;
}

// Tolerance based comparison of two double values. Combines
// absolute and relative errors for a smooth transition between
// absolute dominate and relative dominate error regimes.
inline bool
_double_almost_equal(double a, double b, double rel_tol, double abs_tol)
{
    if (a == b) {
        return true;
    }

    if (!std::isfinite(a) || !std::isfinite(b)) {
        return false;
    }

    if (std::isnan(a) || std::isnan(b)) {
        return false;
    }

    double diff = std::fabs(a - b);

    return diff <= abs_tol + rel_tol * std::max(std::abs(a), std::abs(b));
}
    
}

#endif  // __EVSPACE_COMPARE_HPP__