#ifndef _EVSPACE_DOT_PRODUCT_H_
#define _EVSPACE_DOT_PRODUCT_H_

#include <cstddef>
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
    double _compute_dot_product(double* const row, double* const column) {
        return row[0] * column[0]
            + row[1] * *(column + dphelpers::column_skips<T>())
            + row[2] * *(column + 2 * dphelpers::column_skips<T>());
    }

}

#endif // _EVSPACE_DOT_PRODUCT_H_