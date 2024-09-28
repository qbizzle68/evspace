#ifndef _EVSPACE_PCH_H_
#define _EVSPACE_PCH_H_

#include <gtest/gtest.h>
#include <sstream>  // std::ostringstream
#include <array>    // std::array
#include <initializer_list> //std::initializer_list

#define EVSPACE_PI      3.14159265358979323846264338327950288
#define EVSPACE_PI_2    (EVSPACE_PI / 2.0)
#define EVSPACE_PI_4    (EVSPACE_PI / 4.0)

#define COMPARE_MATRIX(mat, ans, msg) \
    for (int i = 0; i < 3; i++) { \
        for (int j = 0; j < 3; j++) { \
            std::ostringstream oss; \
            oss << " at index (" << i << ", " << j << ")"; \
            EXPECT_DOUBLE_EQ(mat[i][j], ans[i][j]) << oss.str(); \
        } \
    }

typedef std::array<std::array<double, 3>, 3> MatrixArray;

// Create a 3x3 std::array from an initializer list for quick construction.
inline MatrixArray create_array(const std::initializer_list<std::initializer_list<double>> init) {
    MatrixArray array;
    std::size_t row_count = 0;
    for (const auto& row : init) {
        std::size_t column_count = 0;
        for (const auto& value : row) {
            array[row_count][column_count++] = value;
        }
        row_count++;
    }

    return array;
}

// Create a 3x3 std::array where each component is the same value.
inline MatrixArray create_array(double value) {
    std::array<double, 3> row = { value, value, value };

    return MatrixArray{ row, row, row };
}

#endif // _EVSPACE_PCH_H_