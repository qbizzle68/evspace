/**
* Test files are built using cmake precompiled headers which are made
* visible to this file when building tests and are not explicitly
* included.
*
*/

#include <vector.hpp>
#include <matrix.hpp>
#include <sstream>    // std::stringstream

using namespace evspace;

TEST(VectorUnitTest, TestConstruction) {
    Vector vector = Vector();
    EXPECT_EQ(vector[0], 0.0) << "Default construction has non-zero x-components";
    EXPECT_EQ(vector[1], 0.0) << "Default construction has non-zero y-components";
    EXPECT_EQ(vector[2], 0.0) << "Default construction has non-zero z-components";

    vector = Vector(1.1, 2, 3.0);
    EXPECT_EQ(vector[0], 1.1) << "Invalid x-component after construction";
    EXPECT_EQ(vector[1], 2.0) << "Invalid y-component after construction";
    EXPECT_EQ(vector[2], 3.0) << "Invalid z-component after construction";

    vector = Vector(1, 2, 3);
    Vector vector_copy = Vector(vector);
    EXPECT_EQ(vector_copy[0], 1.0) << "Copy constructor invalid x-component";
    EXPECT_EQ(vector_copy[1], 2.0) << "Copy constructor invalid y-component";
    EXPECT_EQ(vector_copy[2], 3.0) << "Copy constructor invalid z-component";

    Vector vector_move = Vector(std::move(vector));
    EXPECT_EQ(vector_move[0], 1.0) << "Move constructor invalid x-components";
    EXPECT_EQ(vector_move[1], 2.0) << "Move constructor invalid y-components";
    EXPECT_EQ(vector_move[2], 3.0) << "Move constructor invalid z-components";

    vector = Vector(1, 2, 3);
    Vector vector_assigned = vector;
    EXPECT_EQ(vector_assigned[0], 1.0) << "Assignment operator invalid x-component";
    EXPECT_EQ(vector_assigned[1], 2.0) << "Assignment operator invalid y-component";
    EXPECT_EQ(vector_assigned[2], 3.0) << "Assignment operator invalid z-component";

    vector_move = std::move(vector);
    EXPECT_EQ(vector_assigned[0], 1.0) << "Move assignment operator invalid x-component";
    EXPECT_EQ(vector_assigned[1], 2.0) << "Move assignment operator invalid y-component";
    EXPECT_EQ(vector_assigned[2], 3.0) << "Move assignment operator invalid z-component";
}

TEST(VectorUnitTest, TestElementaryVectors) {
    EXPECT_EQ(e1[0], 1.0) << "e1 elementary vector x component not 1.0";
    EXPECT_EQ(e1[1], 0.0) << "e1 elementary vector y component not 0.0";
    EXPECT_EQ(e1[2], 0.0) << "e1 elementary vector z component not 0.0";

    EXPECT_EQ(e2[0], 0.0) << "e2 elementary vector x component not 0.0";
    EXPECT_EQ(e2[1], 1.0) << "e2 elementary vector y component not 1.0";
    EXPECT_EQ(e2[2], 0.0) << "e2 elementary vector z component not 0.0";

    EXPECT_EQ(e3[0], 0.0) << "e3 elementary vector x component not 0.0";
    EXPECT_EQ(e3[1], 0.0) << "e3 elementary vector y component not 0.0";
    EXPECT_EQ(e3[2], 1.0) << "e3 elementary vector z component not 1.0";
}

TEST(VectorUnitTest, TestMathOperators) {
    Vector lhs = Vector(1, 2, 3);
    Vector rhs = Vector(10, 20, 30);
    VectorArray answer;

    Vector result = lhs + rhs;
    answer = create_array({ 11, 22, 33 });
    COMPARE_VECTOR(answer, result, "Addition operator error");

    result = lhs;
    result += rhs;
    COMPARE_VECTOR(answer, result, "Addition assignment operator error");

    result = -lhs;
    answer = create_array({ -1, -2, -3 });
    COMPARE_VECTOR(answer, result, "Negation operator error");

    result = lhs - rhs;
    answer = create_array({ -9, -18, -27 });
    COMPARE_VECTOR(answer, result, "Subtraction operator error");

    result = lhs;
    result -= rhs;
    answer = create_array({ -9, -18, -27 });
    COMPARE_VECTOR(answer, result, "Subtraction assignment operator error");

    result = lhs;
    result = lhs * 1.1;
    answer = create_array({ 1.1, 2.2, 3.3 });
    COMPARE_VECTOR(answer, result, "Scalar multiplication operator error");

    result = lhs;
    result = 1.1 * lhs;
    COMPARE_VECTOR(answer, result, "Scalar multiplication friend operator error");

    result = lhs;
    result *= 1.1;
    COMPARE_VECTOR(answer, result, "Scalar multiplication assignment operator error");

    result = lhs / 0.1;
    answer = create_array({ 10, 20, 30 });
    COMPARE_VECTOR(answer, result, "Scalar division operator error");

    result = lhs;
    result /= 0.1;
    COMPARE_VECTOR(answer, result, "Scalar division assignment operator error");

    Matrix matrix = Matrix({ {1, 2, 3}, {4, 5, 6}, {7, 8, 9} });
    result = lhs * matrix;
    answer = create_array({ 30, 36, 42 });
    COMPARE_VECTOR(answer, result, "Matrix multiplication operator error");

    result = lhs;
    result *= matrix;
    COMPARE_VECTOR(answer, result, "Matrix multiplication assignment operator error");
}

TEST(VectorUnitTest, TestVectorComparison) {
    Vector lhs = Vector(2, 4, 6);
    Vector rhs = Vector(1, 2, 3) / 0.5;

    EXPECT_TRUE(lhs == rhs) << "Equal vectors do not compare as equal";
    EXPECT_FALSE(lhs != rhs) << "Equal vectors compare as unequal";

    rhs = Vector(1, 2, 3);

    EXPECT_TRUE(lhs != rhs) << "Unequal vectors do not compare as unequal";
    EXPECT_FALSE(lhs == rhs) << "Unequal vectors compare as equal";
}

TEST(VectorUnitTest, TestVectorOperators) {
    Vector lhs = Vector(9, 12, 20); 
    Vector rhs;
    Vector result;
    VectorArray answer;

    EXPECT_DOUBLE_EQ(lhs.magnitude(), 25.0) << "Vector magnitude error";
    EXPECT_DOUBLE_EQ(lhs.magnitude_squared(), 625.0) << "Vector magnitude squared error";

    Vector vector_norm = lhs.norm();
    answer = create_array({ 0.36, 0.48, 0.8 });
    _COMPARE_VECTOR_NEAR(vector_norm, answer, "Vector class norm() method error");
    vector_norm = lhs;
    vector_norm.normalize();
    _COMPARE_VECTOR_NEAR(vector_norm, answer, "Vector class normalize() method error");

    lhs = Vector(1, 2, 3);
    rhs = Vector(2, 4, 6);
    EXPECT_DOUBLE_EQ(vector_dot(lhs, rhs), 28.0) << "Vector dot product error";
    EXPECT_DOUBLE_EQ(vector_dot(lhs, lhs), lhs.magnitude_squared())
        << "Vector dot with itself not equal to magnitude squared";

    rhs = Vector(3, 4, 0);
    Vector vector_1_cross_2 = vector_cross(lhs, rhs);
    answer = create_array({ -12, 9, -2 });
    _COMPARE_VECTOR_NEAR(vector_1_cross_2, answer, "Vector cross product lhs X rhs error");
    Vector vector_2_cross_1 = vector_cross(rhs, lhs);
    answer = create_array({ 12, -9, 2 });
    _COMPARE_VECTOR_NEAR(vector_2_cross_1, answer, "Vector cross product rhs X lhs error");

    lhs = Vector(1, 1, 0);
    rhs = Vector(1, 0, 0);
    EXPECT_DOUBLE_EQ(vector_angle(lhs, rhs), EVSPACE_PI_4) << "Vector angle non-trivial example error";
    EXPECT_DOUBLE_EQ(vector_angle(e1, e2), EVSPACE_PI_2) << "Vector angle trivial example error";

    lhs = Vector(1, 2, 3);
    result = vector_exclude(lhs, e1);
    answer = create_array({ 0, 2, 3 });
    COMPARE_VECTOR(result, answer, "Vector excluding X-axis error");
    result = vector_exclude(lhs, e2);
    answer = create_array({ 1, 0, 3 });
    COMPARE_VECTOR(result, answer, "Vector excluding Y-axis error");
    result = vector_exclude(lhs, e3);
    answer = create_array({ 1, 2, 0 });
    COMPARE_VECTOR(result, answer, "Vector excluding Z-axis error");

    lhs = Vector(1, 1, 7);
    rhs = Vector(1, 1, 1);

    result = vector_projection(lhs, rhs);
    answer = create_array({ 3, 3, 3 });
    COMPARE_VECTOR(result, answer, "Vector projection error");
}

TEST(VectorUnitTest, TestVectorSetIndex) {
    Vector vector = Vector(1, 2, 3);
    
    vector[0] = 1.1;
    vector[1] = 2.2;
    vector[2] = 3.3;

    VectorArray answer = create_array({ 1.1, 2.2, 3.3 });
    COMPARE_VECTOR(vector, answer, "Vector setting by index error");
}

TEST(VectorUnitTest, TestVectorInsertionOperator) {
    Vector vector = Vector(1.234, 2, -3.1415);
    std::stringstream ss;
    ss << vector;

    const char* expected_output = "[ 1.234, 2, -3.1415 ]";
    EXPECT_EQ(ss.str(), expected_output) << "Vector insertion operator invalid result";
}
