/**
* Test files are built using cmake precompiled headers which are made
* visible to this file when building tests and are not explicitly
* included.
*
*/

#include <vector.hpp>
#include <matrix.hpp>
#include <sstream>      // std::stringstream
#include <gtest/gtest.h>
#include <helpers.hpp>

using namespace evspace;

class MatrixUnitTest : public testing::Test {
protected:
    Matrix lhs, rhs, result;
    MatrixArray answer;
    const MatrixArray array_123 = create_array({ {1, 2, 3}, {4, 5, 6}, {7, 8, 9} });

    MatrixUnitTest() : lhs(Matrix()), rhs(Matrix()), result(Matrix()),
        answer(create_array({ {0, 0, 0}, {0, 0, 0}, {0, 0, 0} })) { };
};

TEST_F(MatrixUnitTest, TestCreation) {
    // MatrixUnitTest constructor should set result and answer to zero values
    COMPARE_MATRIX(result, answer, "Default matrix construction error");

    // initializer list (both int and double)
    result = Matrix({ {1, 2, 3}, {4, 5, 6}, {7, 8, 9} });
    COMPARE_MATRIX(result, array_123, "Matrix construction from initializer_list< with double error");
    result = Matrix({ {1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0} });
    COMPARE_MATRIX(result, array_123, "Matrix construction from initializer_list with int error");

    // c-style array (both int and double)
    double double_arr[3][3]{ {9, 8, 7}, {6, 5, 4}, {3, 2, 1} };
    result = Matrix(double_arr);
    answer = create_array({ {9, 8, 7}, {6, 5, 4}, {3, 2, 1} });
    COMPARE_MATRIX(result, answer, "Matrix construction from c-style double array error");
    int int_arr[3][3]{ {9, 8, 7}, {6, 5, 4}, {3, 2, 1} };
    result = Matrix(int_arr);
    COMPARE_MATRIX(result, answer, "Matrix construction from c-style int array error");

    // std::array with type double
    result = Matrix(array_123);
    COMPARE_MATRIX(result, array_123, "Matrix construction from std::array error");

    // flat containers (both int and double)
    std::vector<double> cvector_d{1, 2, 3, 4, 5, 6, 7, 8, 9};
    result = Matrix(cvector_d);
    answer = create_array({ {1, 2, 3}, {4, 5, 6}, {7, 8, 9} });
    COMPARE_MATRIX(result, answer, "Matrix construction from std::vector (flat double)");
    std::vector<int> cvector_l{1, 2, 3, 4, 5, 6, 7, 8, 9};
    result = Matrix(cvector_l);
    COMPARE_MATRIX(result, answer, "Matrix construction from std::vector (flat int)");
    cvector_d.pop_back();
    EXPECT_THROW(result = Matrix(cvector_d), std::out_of_range)
        << "Matrix construction from flat container with < 9 elements";
    cvector_d.push_back(9);
    cvector_d.push_back(10);
    EXPECT_THROW(result = Matrix(cvector_d), std::out_of_range)
        << "Matrix construction from flat container with > 9 elements";

    // folded containers (both int and double)
    std::vector<std::vector<double>> cvector_fd{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    result = Matrix(cvector_fd);
    COMPARE_MATRIX(result, answer, "Matrix construction from std::vector (folded double)");
    cvector_fd.push_back(std::vector<double>{1, 2, 3});
    EXPECT_THROW(result = Matrix(cvector_fd), std::out_of_range)
        << "Matrix construction from folded double container with > 3 rows";
    cvector_fd.pop_back();
    cvector_fd.pop_back();
    EXPECT_THROW(result = Matrix(cvector_fd), std::out_of_range)
        << "Matrix construction from folded double container with < 3 rows";
    cvector_fd.push_back(std::vector<double>{1, 2});
    EXPECT_THROW(result = Matrix(cvector_fd), std::out_of_range)
        << "Matrix construction from folded double container with < 3 columns";
    cvector_fd.pop_back();
    cvector_fd.push_back(std::vector<double>{1, 2, 3, 4});
    EXPECT_THROW(result = Matrix(cvector_fd), std::out_of_range)
        << "Matrix construction from folded double container with > 3 columns";
    std::vector<std::vector<int>> cvector_ld{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    result = Matrix(cvector_ld);
    COMPARE_MATRIX(result, answer, "Matrix construction from std::vector (folded int)");
    cvector_ld.push_back(std::vector<int>{1, 2, 3});
    EXPECT_THROW(result = Matrix(cvector_ld), std::out_of_range)
        << "Matrix construction from folded int container with > 3 rows";
    cvector_ld.pop_back();
    cvector_ld.pop_back();
    EXPECT_THROW(result = Matrix(cvector_ld), std::out_of_range)
        << "Matrix construction from folded int container with < 3 rows";
    cvector_ld.push_back(std::vector<int>{1, 2});
    EXPECT_THROW(result = Matrix(cvector_ld), std::out_of_range)
        << "Matrix construction from folded int container with < 3 columns";
    cvector_ld.pop_back();
    cvector_ld.push_back(std::vector<int>{1, 2, 3, 4});
    EXPECT_THROW(result = Matrix(cvector_ld), std::out_of_range)
        << "Matrix construction from folded int container with > 3 columns";

    // copy constructor
    lhs = Matrix({ {1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}, {7.7, 8.8, 9.9} });
    result = Matrix(lhs);
    answer = create_array({ {1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}, {7.7, 8.8, 9.9} });
    COMPARE_MATRIX(result, answer, "Matrix copy constructor error");

    // move constructor
    Matrix tmp = Matrix({ {2, 4, 6}, {8, 10, 12}, {14, 16, 18} });
    result = Matrix(std::move(tmp));
    answer = create_array({ {2, 4, 6}, {8, 10, 12}, {14, 16, 18} });
    COMPARE_MATRIX(result, answer, "Matrix move constructor error");

    // assignment operator
    lhs = Matrix({ {1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}, {7.7, 8.8, 9.9} });
    result = lhs;
    answer = create_array({ {1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}, {7.7, 8.8, 9.9} });
    COMPARE_MATRIX(result, answer, "Matrix assignment operator error");

    // move assignment operator
    tmp = Matrix({ {1, 2, 3}, {4, 5, 6}, {7, 8, 9} });
    lhs = std::move(tmp);
    COMPARE_MATRIX(lhs, array_123, "Matrix move assignment operator error");
}

TEST_F(MatrixUnitTest, TestCommaInitialization) {
    Matrix matrix;
    matrix << 1, 2, 3,
              4, 5, 6,
              7, 8, 9;
    answer = create_array({ {1, 2, 3}, {4, 5, 6}, {7, 8, 9} });
    COMPARE_MATRIX(matrix, answer, "Matrix comma initialization error");

    matrix = Matrix();
    matrix << 1, 2, 3, 4, 5, 6, 7, 8;
    answer = create_array({ {1, 2, 3}, {4, 5, 6}, {7, 8, 0} });
    COMPARE_MATRIX(matrix, answer, "Matrix initialization error");

    EXPECT_THROW((
        matrix << 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
    ), std::out_of_range);
}

TEST_F(MatrixUnitTest, TestIndexSetter) {
    lhs = Matrix();
    lhs(0, 0) = 1;
    lhs(1, 2) = 2;
    lhs(2, 1) = 3;
    
    answer = create_array({ {1, 0, 0}, {0, 0, 2}, {0, 3, 0} });
    COMPARE_MATRIX(lhs, answer, "Matrix index setter operator error");
}

TEST_F(MatrixUnitTest, TestInertionOperator) {
    std::stringstream ss;

    lhs = Matrix({ {1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}, {7.7, 8.8, 9.9} });
    ss << lhs;
    const char* answer = "[ [ 1.1, 2.2, 3.3 ], [ 4.4, 5.5, 6.6 ], [ 7.7, 8.8, 9.9 ] ]";
    EXPECT_EQ(ss.str(), answer) << "Matrix insertion operator error";
}

TEST_F(MatrixUnitTest, TestMathOperators) {
    lhs = Matrix({ {1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}, {7.7, 8.8, 9.9} });
    rhs = Matrix({ {1, 2, 3}, {4, 5, 6}, {7, 8, 9} });

    result = lhs + rhs;
    answer = create_array({ {2.1, 4.2, 6.3}, {8.4, 10.5, 12.6}, {14.7, 16.8, 18.9} });
    _COMPARE_MATRIX_NEAR(result, answer, "Matrix addition operator error");

    result = lhs;
    result += rhs;
    _COMPARE_MATRIX_NEAR(result, answer, "Matrix addition assignment operator error");

    rhs = Matrix(array_123);
    result = -rhs;
    answer = create_array({ {-1, -2, -3}, {-4, -5, -6}, {-7, -8, -9} });
    _COMPARE_MATRIX_NEAR(result, answer, "Matrix negation operator error");

    result = lhs - rhs;
    answer = create_array({ {0.1, 0.2, 0.3}, {0.4, 0.5, 0.6}, {0.7, 0.8, 0.9} });
    _COMPARE_MATRIX_NEAR(result, answer, "Matrix subtraction operator error");

    result = lhs;
    result -= rhs;
    _COMPARE_MATRIX_NEAR(result, answer, "Matrix subtraction assignment operator error");

    result = lhs * 2.0;
    answer = create_array({ {2.2, 4.4, 6.6}, {8.8, 11, 13.2}, {15.4, 17.6, 19.8} });
    _COMPARE_MATRIX_NEAR(result, answer, "Matrix scalar multiplication operator error");

    result = lhs;
    result *= 2.0;
    _COMPARE_MATRIX_NEAR(result, answer, "Matrix scalar multiplication assignment operator error");

    result = rhs;
    result *= lhs;
    answer = create_array({ {33, 39.6, 46.2}, {72.6, 89.1, 105.6}, {112.2, 138.6, 165} });
    _COMPARE_MATRIX_NEAR(result, answer, "Matrix matrix multiplication assignment operator error");

    result = rhs;
    result *= result;
    answer = create_array({ {30, 36, 42}, {66, 81, 96}, {102, 126, 150} });
    _COMPARE_MATRIX_NEAR(result, answer, "Matrix matrix multiplication assignment operator on self error");

    lhs = Matrix({ {1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}, {7.7, 8.8, 9.9} });
    result = lhs / 1.1;
    _COMPARE_MATRIX_NEAR(result, array_123, "Matrix scalar division operator error");

    result = Matrix({ {1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}, {7.7, 8.8, 9.9} });
    result /= 0.5;
    answer = create_array({ {2.2, 4.4, 6.6}, {8.8, 11, 13.2}, {15.4, 17.6, 19.8} });
    _COMPARE_MATRIX_NEAR(result, answer, "Matrix scalar division assignment operator error");

    Vector vector = Vector(1, 2, 3);
    lhs = Matrix(array_123);
    Vector vector_result = lhs * vector;
    VectorArray vector_answer = create_array({ 14, 32, 50 });
    _COMPARE_VECTOR_NEAR(vector_result, vector_answer, "Matrix vector multiplication operator error");

    vector_result = vector * lhs;
    vector_answer = create_array({ 30, 36, 42 });
    _COMPARE_VECTOR_NEAR(vector_result, vector_answer, "Vector matrix multiplication operator error");

    vector_result = vector;
    vector_result *= lhs;
    _COMPARE_VECTOR_NEAR(vector_result, vector_answer, "Vector matrix multiplication assignment operator error");

    lhs = array_123;
    rhs = array_123;
    result = lhs * rhs;
    answer = create_array({ {30, 36, 42}, {66, 81, 96}, {102, 126, 150} });
    _COMPARE_MATRIX_NEAR(result, answer, "Matrix multiplication operator error");

    result = lhs;
    result *= rhs;
    _COMPARE_MATRIX_NEAR(result, answer, "Matrix multiplication assignment operator error");

    result << 1.0, 0.0, 0.0,
              0.0, 0.0707372016677029, -0.9974949866040544,
              0.0, 0.9974949866040544, 0.0707372016677029;
    answer = create_array({
        {1.0, 0.0, 0.0},
        {0.0, 0.0707372016677029, 0.9974949866040544},
        {0.0, -0.9974949866040544, 0.0707372016677029}
    });
    _COMPARE_MATRIX_NEAR(result.inverse(), answer, "Matrix inverse error");
    answer = create_array({ {1, 0, 0}, {0, 1, 0}, {0, 0, 1} });
    _COMPARE_MATRIX_NEAR((result.inverse() * result), answer,
        "Matrix inverse check error");
}

TEST_F(MatrixUnitTest, TestMatrixComparison) {
    lhs = Matrix(array_123);
    rhs = Matrix(array_123) * 2.0;
    Matrix lhs_copy = lhs;

    EXPECT_TRUE(lhs == lhs_copy) << "Equality operator on equal matrices error";
    EXPECT_FALSE(lhs == rhs) << "Equality operator on unequal matrices error";
    EXPECT_TRUE(lhs != rhs) << "Unequality operator on unequal matrices error";
    EXPECT_FALSE(lhs != lhs_copy) << "Unequality operator on equal matrices error";
}

TEST_F(MatrixUnitTest, TestMatrixOperators) {
    lhs = Matrix(array_123);
    double determinate = lhs.determinate();
    EXPECT_DOUBLE_EQ(determinate, 0.0) << "Matrix determinate operator error";

    lhs = Matrix({ {1, 2, 3}, {3, 2, 1}, {5, 0, 5} });
    determinate = lhs.determinate();
    EXPECT_DOUBLE_EQ(determinate, -40.0) << "Matrix determinate operator error";

    lhs = Matrix(array_123);
    result = lhs.transpose();
    answer = create_array({ {1, 4, 7}, {2, 5, 8}, {3, 6, 9} });
    COMPARE_MATRIX(result, answer, "Matrix transpose error");

    result = lhs;
    result.transpose_inplace();
    COMPARE_MATRIX(result, answer, "Matrix transpose inplace error");
}

TEST_F(MatrixUnitTest, TestIdentity) {
    answer = create_array({ {1, 0, 0}, {0, 1, 0}, {0, 0, 1} });

    COMPARE_MATRIX(Matrix::IDENTITY, answer, "Matrix identity error");
}

TEST(MatrixUnitTestData, TestDataAccessors) {
    Matrix matrix{1, 2, 3, 4, 5, 6, 7, 8, 9};
    span_t<double> span = matrix.data();
    EXPECT_EQ(span[0], 1) << "matrix span error in index 0";
    EXPECT_EQ(span[1], 2) << "matrix span error in index 1";
    EXPECT_EQ(span[2], 3) << "matrix span error in index 2";
    EXPECT_EQ(span[3], 4) << "matrix span error in index 3";
    EXPECT_EQ(span[4], 5) << "matrix span error in index 4";
    EXPECT_EQ(span[5], 6) << "matrix span error in index 5";
    EXPECT_EQ(span[6], 7) << "matrix span error in index 6";
    EXPECT_EQ(span[7], 8) << "matrix span error in index 7";
    EXPECT_EQ(span[8], 9) << "matrix span error in index 8";
    EXPECT_EQ(span.size(), 9) << "matrix span size error";
    EXPECT_EQ(span.size_bytes(), 9 * sizeof(double)) << "matrix span size_bytes error";
    span[5] = 10;
    EXPECT_EQ(matrix(1, 2), 10) << "matrix span modify error";

    span_t<const double> span_const = matrix.data();
    EXPECT_EQ(span[0], 1) << "matrix const span error in index 0";
    EXPECT_EQ(span[1], 2) << "matrix const span error in index 1";
    EXPECT_EQ(span[2], 3) << "matrix const span error in index 2";
    EXPECT_EQ(span[3], 4) << "matrix const span error in index 3";
    EXPECT_EQ(span[4], 5) << "matrix const span error in index 4";
    EXPECT_EQ(span[5], 10) << "matrix const span error in index 5";
    EXPECT_EQ(span[6], 7) << "matrix const span error in index 6";
    EXPECT_EQ(span[7], 8) << "matrix const span error in index 7";
    EXPECT_EQ(span[8], 9) << "matrix const span error in index 8";
    EXPECT_EQ(span.size(), 9) << "matrix const span size error";
    EXPECT_EQ(span.size_bytes(), 9 * sizeof(double)) << "matrix const span size_bytes error";
}
