/**
* Test files are built using cmake precompiled headers which are made
* visible to this file when building tests and are not explicitly
* included.
*
*/

#include <vector.hpp>
#include <matrix.hpp>
#include <sstream>      // std::stringstream

using namespace evspace;

class MatrixRowUnitTest : public testing::Test {
protected:
    const Matrix matrix_123;

    MatrixRowUnitTest() : matrix_123(Matrix({ {1, 2, 3}, {4, 5, 6}, {7, 8, 9} })) { }
};

TEST_F(MatrixRowUnitTest, TestConstruction) {
    double* ptr = new double[3] {1, 2, 3 };

    MatrixRow row = MatrixRow(ptr);
    EXPECT_EQ(row[0], 1.0) << "Constructor result x-value invalid";
    EXPECT_EQ(row[1], 2.0) << "Constructor result y-value invalid";
    EXPECT_EQ(row[2], 3.0) << "Constructor result z-value invalid";

    MatrixRow row_copy = MatrixRow(row);
    EXPECT_EQ(row_copy[0], 1.0) << "Copy constructor result x-value invalid";
    EXPECT_EQ(row_copy[1], 2.0) << "Copy constructor result y-value invalid";
    EXPECT_EQ(row_copy[2], 3.0) << "Copy constructor result z-value invalid";

    MatrixRow row_move = MatrixRow(std::move(row));
    EXPECT_EQ(row_move[0], 1.0) << "Move constructor result x-value invalid";
    EXPECT_EQ(row_move[1], 2.0) << "Move constructor result y-value invalid";
    EXPECT_EQ(row_move[2], 3.0) << "Move constructor result z-value invalid";
}

TEST_F(MatrixRowUnitTest, TestAssignment) {
    double* ptr = new double[3] {1, 2, 3};
    MatrixRow row = MatrixRow(ptr);
    
    MatrixRow row_copy = row;
    EXPECT_EQ(row_copy[0], 1.0) << "Assignment result x-value invalid";
    EXPECT_EQ(row_copy[1], 2.0) << "Assignment result y-value invalid";
    EXPECT_EQ(row_copy[2], 3.0) << "Assignment result z-value invalid";

    MatrixRow row_move = std::move(row);
    EXPECT_EQ(row_move[0], 1.0) << "Move assignment result x-value invalid";
    EXPECT_EQ(row_move[1], 2.0) << "Move assignment result y-value invalid";
    EXPECT_EQ(row_move[2], 3.0) << "Move assignment result z-value invalid";
}

class MatrixUnitTest : public testing::Test {
protected:
    /*const Matrix matrix_default;
    const Matrix matrix_123;
    const double array_123[3][3] = { {1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0} };
    const double array_246[3][3] = { {2.0, 4.0, 6.0}, {8.0, 10.0, 12.0}, {14.0, 16.0, 18.0} };

    MatrixUnitTest() : matrix_default(Matrix()),
        matrix_123(Matrix({ {1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0} })) { }*/
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

TEST_F(MatrixUnitTest, TestIndexSetter) {
    lhs = Matrix();
    lhs[0][0] = 1;
    lhs[1][2] = 2;
    lhs[2][1] = 3;
    
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

    lhs = Matrix({ {1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}, {7.7, 8.8, 9.9} });
    result = lhs / 1.1;
    _COMPARE_MATRIX_NEAR(result, array_123, "Matrix scalar division operator error");

    result = Matrix({ {1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}, {7.7, 8.8, 9.9} });
    result /= 0.5;
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

    COMPARE_MATRIX(IDENTITY, answer, "Matrix identity error");
}
