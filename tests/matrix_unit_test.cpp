/**
* Test files are built using cmake precompiled headers which are made
* visible to this file when building tests and are not explicitly
* included.
*
*/

#include <vector.hpp>
#include <matrix.hpp>

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
    const Matrix matrix_default;
    const Matrix matrix_123;
    const double array_123[3][3] = { {1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0} };
    const double array_246[3][3] = { {2.0, 4.0, 6.0}, {8.0, 10.0, 12.0}, {14.0, 16.0, 18.0} };

    MatrixUnitTest() : matrix_default(Matrix()),
        matrix_123(Matrix({ {1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0} })) { }

    static Matrix create_homogenous_matrix(double value) {
        return Matrix({ {value, value, value}, {value, value, value}, {value, value, value} });
    }
};

TEST_F(MatrixUnitTest, TestDefaultConstruction) {
    Matrix matrix = Matrix();
    MatrixArray answer = create_array(0.0);

    COMPARE_MATRIX(matrix, answer, "Default constructor valud invalid")
}

TEST_F(MatrixUnitTest, TestArrayConstruction) {
    Matrix matrix({ {1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0} });
    COMPARE_MATRIX(matrix, array_123, "Array constructor value from initializer_list<double> invalid");

    matrix = Matrix(array_123);
    COMPARE_MATRIX(matrix, array_123, "Array constructor value from array invalid");

    matrix = Matrix({ {1, 2, 3}, {4, 5, 6}, {7, 8, 9} });
    COMPARE_MATRIX(matrix, array_123, "Array constructor value from initializer_list<int> invalid");
}

TEST_F(MatrixUnitTest, TestCopyConstructor) {
    Matrix matrix_copy = Matrix(matrix_123);
    COMPARE_MATRIX(matrix_copy, array_123, "Copy constructor value invalid");
}

TEST_F(MatrixUnitTest, TestMoveConstructor) {
    Matrix matrix = Matrix(matrix_123);
    Matrix matrix_move = Matrix(std::move(matrix));

    COMPARE_MATRIX(matrix_move, array_123, "Move constructor value invalid");
}

TEST_F(MatrixUnitTest, TestAssignment) {
    Matrix matrix_copy = matrix_123;
    COMPARE_MATRIX(matrix_copy, array_123, "Assignment operator value invalid");
}

TEST_F(MatrixUnitTest, TestMoveAssignment) {
    Matrix matrix = Matrix(matrix_123);
    Matrix matrix_move = std::move(matrix);

    COMPARE_MATRIX(matrix_move, array_123, "Move assignment value invalid");
}

TEST_F(MatrixUnitTest, TestAddition) {
    Matrix result = matrix_123 + matrix_123;
    COMPARE_MATRIX(result, array_246, "Addition result value invalid");
}

TEST_F(MatrixUnitTest, TestAdditionAssignment) {
    Matrix result = matrix_123;
    
    result += matrix_123;
    COMPARE_MATRIX(result, array_246, "Addition assignemnt result value invalid");
}

TEST_F(MatrixUnitTest, TestSubtraction) {
    Matrix matrix1 = Matrix({ {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}, {10.0, 11.0, 12.0} });
    Matrix matrix2 = Matrix({ {9.0, 8.0, 7.0}, {6.0, 5.0, 4.0}, {3.0, 2.0, 1.0} });

    Matrix result = matrix1 - matrix2;
    MatrixArray answer = create_array({ {-5.0, -3.0, -1.0}, {1.0, 3.0, 5.0}, {7.0, 9.0, 11.0} });
    COMPARE_MATRIX(result, answer, "Subtraction result value invalid");
}

TEST_F(MatrixUnitTest, TestSubtractionAssignment) {
    Matrix matrix1 = Matrix(
        { {4, 5, 6}, {7, 8, 9}, {10, 11, 12} }
    );
    Matrix matrix2 = Matrix(
        { {9, 8, 7}, {6, 5, 4}, {3, 2, 1} }
    );

    matrix1 -= matrix2;
    MatrixArray answer = create_array({ {-5, -3, -1}, {1, 3, 5}, {7, 9, 11} });
    COMPARE_MATRIX(matrix1, answer, "Subtraction assignment result value invalid");
}

TEST_F(MatrixUnitTest, TestNegation) {
    Matrix result = -matrix_123;
    MatrixArray answer = create_array({ {-1, -2, -3}, {-4, -5, -6}, {-7, -8, -9} });
    COMPARE_MATRIX(result, answer, "Negation result value invalid");
}

TEST_F(MatrixUnitTest, TestScalarMultiplication) {
    Matrix result = matrix_123 * 2;
    COMPARE_MATRIX(result, array_246, "Scalar multiplication result value invalid");
}

TEST_F(MatrixUnitTest, TestScalarAssignmentMultiplication) {
    Matrix result = matrix_123;
    result *= 2;
    COMPARE_MATRIX(result, array_246, "Scalar multiplication assignment result value invalid");
}

TEST_F(MatrixUnitTest, TestMatrixMultiplication) {
    Matrix result = matrix_123 * matrix_123;
    MatrixArray answer = create_array({ {30, 36, 42}, {66, 81, 96}, {102, 126, 150} });

    COMPARE_MATRIX(result, answer, "Matrix multiplication result value invalid");
}

TEST_F(MatrixUnitTest, TestMatrixAssignmentMultiplication) {
    Matrix result = matrix_123;
    result *= matrix_123;
    MatrixArray answer = create_array({ {30, 36, 42}, {66, 81, 96}, {102, 126, 150} });

    COMPARE_MATRIX(result, answer, "Matrix multiplication assignment result value invalid");
}

TEST_F(MatrixUnitTest, TestVectorMultiplication) {
    Vector vector = Vector(1, 2, 3);
    Vector result = matrix_123 * vector;

    double answer[3] = { 14, 32, 50 };
    for (int i = 0; i < 3; i++) {
        EXPECT_DOUBLE_EQ(result[i], answer[i]) << "Vector multiplication result value invalid at index " << i;
    }

    result = vector * matrix_123;
    answer[0] = 30; answer[1] = 36; answer[2] = 42;
    for (int i = 0; i < 3; i++) {
        EXPECT_DOUBLE_EQ(result[i], answer[i]) << "Vector multiplication result value invalid at index " << i;
    }
}

TEST_F(MatrixUnitTest, TestScalarDivision) {
    Matrix result = matrix_123 / 0.5;

    COMPARE_MATRIX(result, array_246, "Scalar division result invalid");
}

TEST_F(MatrixUnitTest, TestScalarAssignmentDivision) {
    Matrix result = matrix_123;
    result /= 0.5;

    COMPARE_MATRIX(result, array_246, "Scalar division assignment result invalid");
}

TEST_F(MatrixUnitTest, TestMatrixComparison) {
    Matrix matrix_123_copy = matrix_123;
    Matrix matrix_246 = matrix_123 * 2;

    EXPECT_TRUE(matrix_123 == matrix_123_copy) << "Comparison of equal matricies should be true";
    EXPECT_FALSE(matrix_123 == matrix_246) << "Comparison of unequal matricies should be false";
    EXPECT_TRUE(matrix_123 != matrix_246) << "Comparison of unequal matricies should be false";
    EXPECT_FALSE(matrix_123 != matrix_123_copy) << "Comparison of equal matricies should be true";
}

TEST_F(MatrixUnitTest, TestDeterminate) {
    double determinate = matrix_123.determinate();

    EXPECT_DOUBLE_EQ(determinate, 0.0) << "Matrix determinate value invalid";
}

TEST_F(MatrixUnitTest, TestTransponse) {
    Matrix transposed = matrix_123.transpose();
    MatrixArray answer = create_array({ {1, 4, 7}, {2, 5, 8}, {3, 6, 9} });

    COMPARE_MATRIX(transposed, answer, "Matrix transpose value invalid");

    transposed = matrix_123;
    transposed.transpose_inplace();
    COMPARE_MATRIX(transposed, answer, "Matrix transpose inplace value invalid");
}

TEST_F(MatrixUnitTest, TestIdentity) {
    MatrixArray answer = create_array({ {1, 0, 0}, {0, 1, 0}, {0, 0, 1} });

    COMPARE_MATRIX(IDENTITY, answer, "Matrix identity value invalid");
}
