#ifndef _EVSPACE_DOT_PRODUCT_H_
#define _EVSPACE_DOT_PRODUCT_H_

#include <cstddef>  // std::size_t
#include <cmath>    // std::fma
#include <evspace_common.hpp>
#include <vector.hpp>

namespace evspace {

    // dot product helpers
    namespace dphelpers {

        template<typename T>
        struct NonLiteralDelegate { };
        template<>
        struct NonLiteralDelegate<evspace::Vector> {
            static constexpr inline std::size_t get_size() { return 1; }
        };
        template<>
        struct NonLiteralDelegate<evspace::Matrix> {
            static constexpr inline std::size_t get_size() { return 3; }
        };

        template<typename T>
        constexpr std::size_t column_skips() {
            return NonLiteralDelegate<T>::get_size();
        }

    }

    template<typename T>
    constexpr inline double _compute_dot_product(
        const double* const EVSPACE_RESTRICT row,
        const double* const EVSPACE_RESTRICT column) noexcept
    {
        constexpr std::size_t stride = dphelpers::column_skips<T>();
        return std::fma(row[0], column[0],
               std::fma(row[1], column[stride],
                            row[2] * column[2 * stride]));
    }

}

#endif // _EVSPACE_DOT_PRODUCT_H_
