/**
* Test files are built using cmake precompiled headers which are made
* visible to this file when building tests and are not explicitly
* included.
*
*/

#include <vector.hpp>
#include <sstream>    // std::stringstream

using namespace evspace;

TEST(VectorUnitTest, TestDefaultInitialization) {
    Vector vector = Vector();
    EXPECT_EQ(vector[0], 0.0) << "Default construction has non-zero x-components";
    EXPECT_EQ(vector[1], 0.0) << "Default construction has non-zero y-components";
    EXPECT_EQ(vector[2], 0.0) << "Default construction has non-zero z-components";
}

TEST(VectorUnitTest, TestComponentInitialization) {
    Vector vector = Vector(1.1, 2, 3.0);
    EXPECT_EQ(vector[0], 1.1) << "Invalid x-component after construction";
    EXPECT_EQ(vector[1], 2.0) << "Invalid y-component after construction";
    EXPECT_EQ(vector[2], 3.0) << "Invalid z-component after construction";
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

TEST(VectorUnitTest, TestCopyConstructor) {
    Vector vector = Vector(1, 2, 3);
    Vector vector_copy = Vector(vector);

    EXPECT_EQ(vector_copy[0], 1.0) << "Copy constructor invalid x-component";
    EXPECT_EQ(vector_copy[1], 2.0) << "Copy constructor invalid y-component";
    EXPECT_EQ(vector_copy[2], 3.0) << "Copy constructor invalid z-component";
}

TEST(VectorUnitTest, TestMoveConstructor) {
    Vector vector = Vector(1, 2, 3);
    Vector vector_move = std::move(vector);

    EXPECT_EQ(vector_move[0], 1.0) << "Move constructor invalid x-components";
    EXPECT_EQ(vector_move[1], 2.0) << "Move constructor invalid y-components";
    EXPECT_EQ(vector_move[2], 3.0) << "Move constructor invalid z-components";
}

TEST(VectorUnitTest, TestAssignment) {
    Vector vector = Vector(1, 2, 3);
    Vector vector_assigned = vector;

    EXPECT_EQ(vector_assigned[0], 1.0) << "Assignment operator invalid x-component";
    EXPECT_EQ(vector_assigned[1], 2.0) << "Assignment operator invalid y-component";
    EXPECT_EQ(vector_assigned[2], 3.0) << "Assignment operator invalid z-component";
}

TEST(VectorUnitTest, TestAddition) {
    Vector lhs = Vector(1, 2, 3);
    Vector rhs = Vector(lhs);

    Vector result = lhs + rhs;

    EXPECT_EQ(result[0], 2.0) << "Addition operator invalid x-component";
    EXPECT_EQ(result[1], 4.0) << "Addition operator invalid y-component";
    EXPECT_EQ(result[2], 6.0) << "Addition operator invalid z-component";
}

TEST(VectorUnitTest, TestAdditionAssignment) {
    Vector lhs = Vector(1, 2, 3);
    Vector rhs = Vector(1, 2, 3);

    lhs += rhs;
    EXPECT_EQ(lhs[0], 2.0) << "Addition assignment operator invalid x-component";
    EXPECT_EQ(lhs[1], 4.0) << "Addition assignment operator invalid y-component";
    EXPECT_EQ(lhs[2], 6.0) << "Addition assignment operator invalid z-component";
}

TEST(VectorUnitTest, TestNegation) {
    Vector vector = Vector(1, 2, 3);
    Vector negated = -vector;

    EXPECT_EQ(negated[0], -1.0) << "Negation invalid x-component";
    EXPECT_EQ(negated[1], -2.0) << "Negation invalid y-component";
    EXPECT_EQ(negated[2], -3.0) << "Negation invalid z-component";
}

TEST(VectorUnitTest, TestSubtraction) {
    Vector lhs = Vector(3, 5, 7);
    Vector rhs = Vector(2, 3, 4);

    Vector result = lhs - rhs;
    EXPECT_EQ(result[0], 1.0) << "Subtraction invalid x-component";
    EXPECT_EQ(result[1], 2.0) << "Subtraction invalid y-component";
    EXPECT_EQ(result[2], 3.0) << "Subtraction invalid z-component";
}

TEST(VectorUnitTest, TestSubtractionAssignment) {
    Vector lhs = Vector(3, 5, 7);
    Vector rhs = Vector(2, 3, 4);

    lhs -= rhs;
    EXPECT_EQ(lhs[0], 1.0) << "Subtraction assignment invalid x-component";
    EXPECT_EQ(lhs[1], 2.0) << "Subtraction assignment invalid y-component";
    EXPECT_EQ(lhs[2], 3.0) << "Subtraction assignment invalid z-component";
}

TEST(VectorUnitTest, TestScalarMultiplication) {
    Vector vector = Vector(1, 2, 3);

    Vector result = vector * 1.1;
    EXPECT_DOUBLE_EQ(result[0], 1.1) << "Scalar multiplication invalid x-component";
    EXPECT_DOUBLE_EQ(result[1], 2.2) << "Scalar multiplication invalid y-component";
    EXPECT_DOUBLE_EQ(result[2], 3.3) << "Scalar multiplication invalid z-component";

    result = 1.1 * vector;
    EXPECT_DOUBLE_EQ(result[0], 1.1) << "Scalar multiplication invalid x-component";
    EXPECT_DOUBLE_EQ(result[1], 2.2) << "Scalar multiplication invalid y-component";
    EXPECT_DOUBLE_EQ(result[2], 3.3) << "Scalar multiplication invalid z-component";
}

TEST(VectorUnitTest, TestScalarMultiplicationAssignment) {
    Vector vector = Vector(1, 2, 3);

    vector *= 1.1;
    EXPECT_DOUBLE_EQ(vector[0], 1.1) << "Scalar multiplication assignment invalid x-component";
    EXPECT_DOUBLE_EQ(vector[1], 2.2) << "Scalar multiplication assignment invalid y-component";
    EXPECT_DOUBLE_EQ(vector[2], 3.3) << "Scalar multiplication assignment invalid z-component";
}

TEST(VectorUnitTest, TestScalarDivision) {
    Vector vector = Vector(1, 2, 3);

    Vector result = vector / 0.5;
    EXPECT_DOUBLE_EQ(result[0], 2.0) << "Scalar division invalid x-component";
    EXPECT_DOUBLE_EQ(result[1], 4.0) << "Scalar division invalid y-component";
    EXPECT_DOUBLE_EQ(result[2], 6.0) << "Scalar division invalid z-component";
}

TEST(VectorUnitTest, TestScalarDivisionAssignment) {
    Vector vector = Vector(1, 2, 3);

    vector /= 0.5;
    EXPECT_DOUBLE_EQ(vector[0], 2.0) << "Scalar division assignment invalid x-component";
    EXPECT_DOUBLE_EQ(vector[1], 4.0) << "Scalar division assignment invalid y-component";
    EXPECT_DOUBLE_EQ(vector[2], 6.0) << "Scalar division assignment invalid z-component";
}

TEST(VectorUnitTest, TestVectorCompare) {
    Vector lhs = Vector(2, 4, 6);
    Vector rhs = Vector(1, 2, 3) / 0.5;

    EXPECT_TRUE(lhs == rhs) << "Equal vectors do not compare as equal";
    EXPECT_FALSE(lhs != rhs) << "Equal vectors compare as unequal";

    rhs = Vector(1, 2, 3);

    EXPECT_TRUE(lhs != rhs) << "Unequal vectors do not compare as unequal";
    EXPECT_FALSE(lhs == rhs) << "Unequal vectors compare as equal";
}

TEST(VectorUnitTest, TestMagnitude) {
    // vector creates a Pythogorean quadruple (9, 12, 20, 25)
    Vector vector = Vector(9, 12, 20);

    EXPECT_DOUBLE_EQ(vector.magnitude(), 25.0) << "Vector magintude invalid result";
    EXPECT_DOUBLE_EQ(vector.magnitude_squared(), 625.0) << "Vector magnitude_squared invalid result";
}

TEST(VectorUnitTest, TestNormalization) {
    // vector creates a Pythogorean quadruple (9, 12, 20, 25)
    Vector vector = Vector(9, 12, 20);
    Vector vector_norm = vector.norm();
    vector.normalize();

    Vector result = Vector(0.36, 0.48, 0.8);
    EXPECT_EQ(vector_norm, result) << "Vector class norm() method returned invalid result";
    EXPECT_EQ(vector, result) << "Vector class normalize() resulted in invalid result";
}

TEST(VectorUnitTest, TestDotProduct) {
    Vector vector1 = Vector(1, 2, 3);
    Vector vector2 = Vector(2, 4, 6);

    EXPECT_DOUBLE_EQ(vector_dot(vector1, vector2), 28.0) << "Vector dot product invalid result";
    EXPECT_DOUBLE_EQ(vector_dot(vector1, vector1), vector1.magnitude_squared()) << "Vector dotted with itself not equal to magnitude squared";
}

TEST(VectorUnitTest, TestCrossProduct) {
    Vector vector1 = Vector(1, 2, 3);
    Vector vector2 = Vector(3, 4, 0);

    Vector vector_1_cross_2 = vector_cross(vector1, vector2);
    Vector vector_2_cross_1 = vector_cross(vector2, vector1);

    EXPECT_EQ(vector_1_cross_2, Vector(-12, 9, -2)) << "Vector cross product from 1 to 2 invalid result";
    EXPECT_EQ(vector_2_cross_1, Vector(12, -9, 2)) << "Vector cross product from 2 to 1 invalid result";
}

TEST(VectorUnitTest, TestVectorAngle) {
    Vector vector1 = Vector(1, 1, 0);
    Vector vector2 = Vector(1, 0, 0);

    EXPECT_DOUBLE_EQ(vector_angle(vector1, vector2), EVSPACE_PI_4) << "Vector angle non-trivial example invalid result";
    EXPECT_DOUBLE_EQ(vector_angle(e1, e2), EVSPACE_PI_2) << "Vector angle trivial example invalid result";
}

TEST(VectorUnitTest, TestVectorExclude) {
    Vector vector = Vector(1, 2, 3);
    Vector result;

    result = vector_exclude(vector, e1);
    EXPECT_EQ(result, Vector(0, 2, 3)) << "Vector excluding e1 elementary vector invalid result";
    result = vector_exclude(vector, e2);
    EXPECT_EQ(result, Vector(1, 0, 3)) << "Vector excluding e2 elementary vector invalid result";
    result = vector_exclude(vector, e3);
    EXPECT_EQ(result, Vector(1, 2, 0)) << "Vector excluding e3 elementary vector invalid result";
}

TEST(VectorUnitTest, TestVectorProjection) {
    Vector vector1 = Vector(1, 1, 7);
    Vector vector2 = Vector(1, 1, 1);

    Vector result = vector_projection(vector1, vector2);
    EXPECT_EQ(result, Vector(3, 3, 3)) << "Vector projection invalid result";
}

TEST(VectorUnitTest, TestVectorInsertionOperator) {
    Vector vector = Vector(1.234, 2, -3.1415);
    std::stringstream ss;
    ss << vector;

    const char* expected_output = "[ 1.234, 2, -3.1415 ]";
    //EXPECT_STREQ(ss.str(), expected_output) << "Vector insertion operator invalid result";
    EXPECT_EQ(ss.str(), expected_output) << "Vector insertion operator invalid result";
}
