#ifndef _EVSPACE_PCH_H_
#define _EVSPACE_PCH_H_

#include <gtest/gtest.h>
#include <sstream>          // std::ostringstream
#include <array>            // std::array
#include <initializer_list> //std::initializer_list

#define EVSPACE_PI      3.14159265358979323846264338327950288
#define EVSPACE_PI_2    (EVSPACE_PI / 2.0)
#define EVSPACE_PI_4    (EVSPACE_PI / 4.0)

// Note these do not have trailing semi-colons so that you can (and must)
// include one so that the macro looks more like a valid statement.

#define COMPARE_MATRIX(mat, ans, msg) \
    EXPECT_DOUBLE_EQ(mat(0, 0), ans[0][0]) << msg << " at index (0, 0)"; \
    EXPECT_DOUBLE_EQ(mat(0, 1), ans[0][1]) << msg << " at index (0, 1)"; \
    EXPECT_DOUBLE_EQ(mat(0, 2), ans[0][2]) << msg << " at index (0, 2)"; \
    EXPECT_DOUBLE_EQ(mat(1, 0), ans[1][0]) << msg << " at index (1, 0)"; \
    EXPECT_DOUBLE_EQ(mat(1, 1), ans[1][1]) << msg << " at index (1, 1)"; \
    EXPECT_DOUBLE_EQ(mat(1, 2), ans[1][2]) << msg << " at index (1, 2)"; \
    EXPECT_DOUBLE_EQ(mat(2, 0), ans[2][0]) << msg << " at index (2, 0)"; \
    EXPECT_DOUBLE_EQ(mat(2, 1), ans[2][1]) << msg << " at index (2, 1)"; \
    EXPECT_DOUBLE_EQ(mat(2, 2), ans[2][2]) << msg << " at index (2, 2)"

#define COMPARE_MATRIX_NEAR(mat, ans, msg, error) \
    EXPECT_NEAR(mat(0, 0), ans[0][0], error) << msg << " at index (0, 0)"; \
    EXPECT_NEAR(mat(0, 1), ans[0][1], error) << msg << " at index (0, 1)"; \
    EXPECT_NEAR(mat(0, 2), ans[0][2], error) << msg << " at index (0, 2)"; \
    EXPECT_NEAR(mat(1, 0), ans[1][0], error) << msg << " at index (1, 0)"; \
    EXPECT_NEAR(mat(1, 1), ans[1][1], error) << msg << " at index (1, 1)"; \
    EXPECT_NEAR(mat(1, 2), ans[1][2], error) << msg << " at index (1, 2)"; \
    EXPECT_NEAR(mat(2, 0), ans[2][0], error) << msg << " at index (2, 0)"; \
    EXPECT_NEAR(mat(2, 1), ans[2][1], error) << msg << " at index (2, 1)"; \
    EXPECT_NEAR(mat(2, 2), ans[2][2], error) << msg << " at index (2, 2)"

#define COMPARE_VECTOR(vec, ans, msg) \
    EXPECT_DOUBLE_EQ(vec[0], ans[0]) << msg << " at index 0"; \
    EXPECT_DOUBLE_EQ(vec[1], ans[1]) << msg << " at index 0"; \
    EXPECT_DOUBLE_EQ(vec[2], ans[2]) << msg << " at index 0"

#define COMPARE_VECTOR_NEAR(vec, ans, msg, error) \
    EXPECT_NEAR(vec[0], ans[0], error) << msg << " at index 0"; \
    EXPECT_NEAR(vec[1], ans[1], error) << msg << " at index 0"; \
    EXPECT_NEAR(vec[2], ans[2], error) << msg << " at index 0"

// Error for EXPECT_NEAR assertions.
constexpr double ABS_ERROR = 1e-10;
#define _COMPARE_VECTOR_NEAR(v, a, m)   COMPARE_VECTOR_NEAR(v, a, m, ABS_ERROR)
#define _COMPARE_MATRIX_NEAR(m, a, msg)   COMPARE_MATRIX_NEAR(m, a, msg, ABS_ERROR)

typedef std::array<double, 3> VectorArray;
typedef std::array<std::array<double, 3>, 3> MatrixArray;

inline VectorArray create_array(const std::initializer_list<double> init) {
    VectorArray array;
    std::size_t count = 0;
    for (const auto& value : init) {
        array[count++] = value;
    }

    return array;
}

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