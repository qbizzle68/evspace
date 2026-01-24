/**
* Test files are built using cmake precompiled headers which are made
* visible to this file when building tests and are not explicitly
* included.
*
*/

#include <axis.hpp>
#include <angles.hpp>
#include <vector.hpp>
#include <matrix.hpp>
#include <rotation.hpp>
#include <resources/test_rotation_matrices.hpp>
#include <resources/test_rotation_vectors.hpp>
#include <gtest/gtest.h>
#include <helpers.hpp>

namespace evs = evspace;

TEST(RotationUnitTest, TestSingleAxisRotationMatrix) {
    const double angle = EVSPACE_PI_4;
    evs::Matrix result;
    MatrixArray answer;

    result = evs::compute_rotation_matrix<evs::XAxis>(angle);
    answer = create_array(X_AXIS_ROTATION_MATRIX);
    _COMPARE_MATRIX_NEAR(result, answer, "X axis rotation matrix error");
    result = evs::compute_rotation_matrix<evs::YAxis>(angle);
    answer = create_array(Y_AXIS_ROTATION_MATRIX);
    _COMPARE_MATRIX_NEAR(result, answer, "Y axis rotation matrix error");
    result = evs::compute_rotation_matrix<evs::ZAxis>(angle);
    answer = create_array(Z_AXIS_ROTATION_MATRIX);
    _COMPARE_MATRIX_NEAR(result, answer, "Z axis rotation matrix error");

    //  extrinsic axis rotations (this should be sufficient to test
    result = evs::compute_rotation_matrix(angle, evs::Vector::e1);
    answer = create_array(X_AXIS_ROTATION_MATRIX);
    _COMPARE_MATRIX_NEAR(result, answer, "X axis extrinsic rotation matrix error");
    result = evs::compute_rotation_matrix(angle, evs::Vector::e2);
    answer = create_array(Y_AXIS_ROTATION_MATRIX);
    _COMPARE_MATRIX_NEAR(result, answer, "Y axis extrinsic rotation matrix error");
    result = evs::compute_rotation_matrix(angle, evs::Vector::e3);
    answer = create_array(Z_AXIS_ROTATION_MATRIX);
    _COMPARE_MATRIX_NEAR(result, answer, "Z axis extrinsic rotation matrix error");
}

TEST(RotationUnitTest, TestEulerRotationMatrix) {
    evs::EulerAngles angles = evs::EulerAngles(EVSPACE_PI / 6, EVSPACE_PI / 4, EVSPACE_PI / 3);
    evs::Matrix result;
    MatrixArray answer;

    result = evs::compute_rotation_matrix<evs::XYZ, evs::IntrinsicRotation>(angles);
    answer = create_array(XYZ_ROTATION_MATRIX);
    _COMPARE_MATRIX_NEAR(result, answer, "XYZ intrinsic rotation matrix error");
    result = evs::compute_rotation_matrix<evs::XZY, evs::IntrinsicRotation>(angles);
    answer = create_array(XZY_ROTATION_MATRIX);
    _COMPARE_MATRIX_NEAR(result, answer, "XZY intrinsic rotation matrix error");
    result = evs::compute_rotation_matrix<evs::XYX, evs::IntrinsicRotation>(angles);
    answer = create_array(XYX_ROTATION_MATRIX);
    _COMPARE_MATRIX_NEAR(result, answer, "XYX intrinsic rotation matrix error");
    result = evs::compute_rotation_matrix<evs::ZXZ, evs::IntrinsicRotation>(angles);
    answer = create_array(ZXZ_ROTATION_MATRIX);
    _COMPARE_MATRIX_NEAR(result, answer, "ZXZ intrinsic rotation matrix error");

    // our answers are for intrinsic rotations only, so we build the equivalent extrinsic rotation
    angles = evs::EulerAngles(EVSPACE_PI / 3, EVSPACE_PI / 4, EVSPACE_PI / 6);
    result = evs::compute_rotation_matrix<evs::ZYX, evs::ExtrinsicRotation>(angles);
    answer = create_array(XYZ_ROTATION_MATRIX);
    _COMPARE_MATRIX_NEAR(result, answer, "XYZ extrinsic rotation matrix error");
    result = evs::compute_rotation_matrix<evs::YZX, evs::ExtrinsicRotation>(angles);
    answer = create_array(XZY_ROTATION_MATRIX);
    _COMPARE_MATRIX_NEAR(result, answer, "XZY extrinsic rotation matrix error");
    result = evs::compute_rotation_matrix<evs::XYX, evs::ExtrinsicRotation>(angles);
    answer = create_array(XYX_ROTATION_MATRIX);
    _COMPARE_MATRIX_NEAR(result, answer, "XYX extrinsic rotation matrix error");
    result = evs::compute_rotation_matrix<evs::ZXZ, evs::ExtrinsicRotation>(angles);
    answer = create_array(ZXZ_ROTATION_MATRIX);
    _COMPARE_MATRIX_NEAR(result, answer, "ZXZ extrinsic rotation matrix error");
}

TEST(RotationUnitTest, TestEulerFromTo) {
    auto angles_to = evs::EulerAngles(0.0, EVSPACE_PI_4, EVSPACE_PI_2);
    auto angles_from = evs::EulerAngles(EVSPACE_PI / 6, EVSPACE_PI_4, EVSPACE_PI / 3);
    evs::Matrix result;
    MatrixArray answer;

    result = evs::compute_rotation_matrix<evs::XYZ, evs::YXY, evs::IntrinsicRotation, evs::IntrinsicRotation>(angles_from, angles_to);
    answer = create_array(XYZ_TO_YXY_ROTATION_MATRIX);
    _COMPARE_MATRIX_NEAR(result, answer, "from XYZ to YXY euler rotation matrix error");
    result = evs::compute_rotation_matrix<evs::XZY, evs::XYX, evs::IntrinsicRotation, evs::IntrinsicRotation>(angles_from, angles_to);
    answer = create_array(XZY_TO_XYX_ROTATION_MATRIX);
    _COMPARE_MATRIX_NEAR(result, answer, "from XZY to XYX euler rotation matrix error");
    result = evs::compute_rotation_matrix<evs::XYX, evs::ZYX, evs::IntrinsicRotation, evs::IntrinsicRotation>(angles_from, angles_to);
    answer = create_array(XYX_TO_ZYX_ROTATION_MATRIX);
    _COMPARE_MATRIX_NEAR(result, answer, "from XYX to ZYX euler rotation matrix error");
    result = evs::compute_rotation_matrix<evs::ZXZ, evs::YZY, evs::IntrinsicRotation, evs::IntrinsicRotation>(angles_from, angles_to);
    answer = create_array(ZXZ_TO_YZY_ROTATION_MATRIX);
    _COMPARE_MATRIX_NEAR(result, answer, "from ZXZ to YZY euler rotation matrix error");

    // make the first rotation be extrinsic (need to make orders to reflect the answers we have)
    angles_from = evs::EulerAngles(EVSPACE_PI / 3, EVSPACE_PI_4, EVSPACE_PI / 6);
    result = evs::compute_rotation_matrix<evs::ZYX, evs::YXY, evs::ExtrinsicRotation, evs::IntrinsicRotation>(angles_from, angles_to);
    answer = create_array(XYZ_TO_YXY_ROTATION_MATRIX);
    _COMPARE_MATRIX_NEAR(result, answer, "from XYZ to YXY euler rotation matrix error");
    result = evs::compute_rotation_matrix<evs::YZX, evs::XYX, evs::ExtrinsicRotation, evs::IntrinsicRotation>(angles_from, angles_to);
    answer = create_array(XZY_TO_XYX_ROTATION_MATRIX);
    _COMPARE_MATRIX_NEAR(result, answer, "from XZY to XYX euler rotation matrix error");
    result = evs::compute_rotation_matrix<evs::XYX, evs::ZYX, evs::ExtrinsicRotation, evs::IntrinsicRotation>(angles_from, angles_to);
    answer = create_array(XYX_TO_ZYX_ROTATION_MATRIX);
    _COMPARE_MATRIX_NEAR(result, answer, "from XYX to ZYX euler rotation matrix error");
    result = evs::compute_rotation_matrix<evs::ZXZ, evs::YZY, evs::ExtrinsicRotation, evs::IntrinsicRotation>(angles_from, angles_to);
    answer = create_array(ZXZ_TO_YZY_ROTATION_MATRIX);
    _COMPARE_MATRIX_NEAR(result, answer, "from ZXZ to YZY euler rotation matrix error");
}

TEST(RotationUnitTest, TestSingleAxisRotationVectors) {
    const double angle = EVSPACE_PI_4;
    evs::Vector offset_vector = evs::Vector(10, 20, 30);
    const evs::Vector test_vector = evs::Vector(1, 2, 3);
    evs::Vector result;
    VectorArray answer;

    result = evs::rotate_to<evs::XAxis>(angle, test_vector);
    answer = create_array(X_AXIS_ROTATION_TO);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate to X-axis vector error");
    result = evs::rotate_to<evs::YAxis>(angle, test_vector);
    answer = create_array(Y_AXIS_ROTATION_TO);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate to Y-axis vector error");
    result = evs::rotate_to<evs::ZAxis>(angle, test_vector);
    answer = create_array(Z_AXIS_ROTATION_TO);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate to Z-axis vector error");

    result = evs::rotate_from<evs::XAxis>(angle, test_vector);
    answer = create_array(X_AXIS_ROTATION_FROM);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate from X-axis vector error");
    result = evs::rotate_from<evs::YAxis>(angle, test_vector);
    answer = create_array(Y_AXIS_ROTATION_FROM);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate from Y-axis vector error");
    result = evs::rotate_from<evs::ZAxis>(angle, test_vector);
    answer = create_array(Z_AXIS_ROTATION_FROM);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate from Z-axis vector error");

    result = evs::rotate_to<evs::XAxis>(angle, test_vector, offset_vector);
    answer = create_array(X_AXIS_ROTATION_OFFSET_TO);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate to offset X-axis vector error");
    result = evs::rotate_to<evs::YAxis>(angle, test_vector, offset_vector);
    answer = create_array(Y_AXIS_ROTATION_OFFSET_TO);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate to offset Y-axis vector error");
    result = evs::rotate_to<evs::ZAxis>(angle, test_vector, offset_vector);
    answer = create_array(Z_AXIS_ROTATION_OFFSET_TO);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate to offset Z-axis vector error");

    result = evs::rotate_from<evs::XAxis>(angle, test_vector, offset_vector);
    answer = create_array(X_AXIS_ROTATION_OFFSET_FROM);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate from offset X-axis vector error");
    result = evs::rotate_from<evs::YAxis>(angle, test_vector, offset_vector);
    answer = create_array(Y_AXIS_ROTATION_OFFSET_FROM);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate from offset Y-axis vector error");
    result = evs::rotate_from<evs::ZAxis>(angle, test_vector, offset_vector);
    answer = create_array(Z_AXIS_ROTATION_OFFSET_FROM);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate from offset Z-axis vector error");
}

TEST(RotationUnitTest, TestEulerRotationVectors) {
    evs::EulerAngles angles = evs::EulerAngles(EVSPACE_PI / 6, EVSPACE_PI_4, EVSPACE_PI / 3);
    evs::Vector result;
    VectorArray answer;
    const evs::Vector test_vector = evs::Vector(1, 2, 3);
    const evs::Vector offset_vector = evs::Vector(10, 20, 30);

    result = evs::rotate_to<evs::XYZ, evs::IntrinsicRotation>(angles, test_vector);
    answer = create_array(XYZ_ROTATION_TO);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector to XYZ error");
    result = evs::rotate_to<evs::XZY, evs::IntrinsicRotation>(angles, test_vector);
    answer = create_array(XZY_ROTATION_TO);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector to XZY error");
    result = evs::rotate_to<evs::XYX, evs::IntrinsicRotation>(angles, test_vector);
    answer = create_array(XYX_ROTATION_TO);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector to XYX error");
    result = evs::rotate_to<evs::ZXZ, evs::IntrinsicRotation>(angles, test_vector);
    answer = create_array(ZXZ_ROTATION_TO);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector to ZXZ error");

    result = evs::rotate_from<evs::XYZ, evs::IntrinsicRotation>(angles, test_vector);
    answer = create_array(XYZ_ROTATION_FROM);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from XYZ error");
    result = evs::rotate_from<evs::XZY, evs::IntrinsicRotation>(angles, test_vector);
    answer = create_array(XZY_ROTATION_FROM);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from XZY error");
    result = evs::rotate_from<evs::XYX, evs::IntrinsicRotation>(angles, test_vector);
    answer = create_array(XYX_ROTATION_FROM);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from XYX error");
    result = evs::rotate_from<evs::ZXZ, evs::IntrinsicRotation>(angles, test_vector);
    answer = create_array(ZXZ_ROTATION_FROM);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from ZXZ error");

    result = evs::rotate_to<evs::XYZ, evs::IntrinsicRotation>(angles, test_vector, offset_vector);
    answer = create_array(XYZ_ROTATION_OFFSET_TO);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector to offset XYZ error");
    result = evs::rotate_to<evs::XZY, evs::IntrinsicRotation>(angles, test_vector, offset_vector);
    answer = create_array(XZY_ROTATION_OFFSET_TO);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector to offset XZY error");
    result = evs::rotate_to<evs::XYX, evs::IntrinsicRotation>(angles, test_vector, offset_vector);
    answer = create_array(XYX_ROTATION_OFFSET_TO);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector to offset XYX error");
    result = evs::rotate_to<evs::ZXZ, evs::IntrinsicRotation>(angles, test_vector, offset_vector);
    answer = create_array(ZXZ_ROTATION_OFFSET_TO);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector to offset ZXZ error");

    result = evs::rotate_from<evs::XYZ, evs::IntrinsicRotation>(angles, test_vector, offset_vector);
    answer = create_array(XYZ_ROTATION_OFFSET_FROM);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset XYZ error");
    result = evs::rotate_from<evs::XZY, evs::IntrinsicRotation>(angles, test_vector, offset_vector);
    answer = create_array(XZY_ROTATION_OFFSET_FROM);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset XZY error");
    result = evs::rotate_from<evs::XYX, evs::IntrinsicRotation>(angles, test_vector, offset_vector);
    answer = create_array(XYX_ROTATION_OFFSET_FROM);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset XYX error");
    result = evs::rotate_from<evs::ZXZ, evs::IntrinsicRotation>(angles, test_vector, offset_vector);
    answer = create_array(ZXZ_ROTATION_OFFSET_FROM);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset ZXZ error");

    // extrinsic tests
    angles = evs::EulerAngles(EVSPACE_PI / 3, EVSPACE_PI_4, EVSPACE_PI / 6);
    result = evs::rotate_to<evs::ZYX, evs::ExtrinsicRotation>(angles, test_vector);
    answer = create_array(XYZ_ROTATION_TO);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector to XYZ extrinsic error");
    result = evs::rotate_to<evs::YZX, evs::ExtrinsicRotation>(angles, test_vector);
    answer = create_array(XZY_ROTATION_TO);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector to XZY extrinsic error");
    result = evs::rotate_to<evs::XYX, evs::ExtrinsicRotation>(angles, test_vector);
    answer = create_array(XYX_ROTATION_TO);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector to XYX extrinsic error");
    result = evs::rotate_to<evs::ZXZ, evs::ExtrinsicRotation>(angles, test_vector);
    answer = create_array(ZXZ_ROTATION_TO);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector to ZXZ extrinsic error");

    result = evs::rotate_from<evs::ZYX, evs::ExtrinsicRotation>(angles, test_vector);
    answer = create_array(XYZ_ROTATION_FROM);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from XYZ extrinsic error");
    result = evs::rotate_from<evs::YZX, evs::ExtrinsicRotation>(angles, test_vector);
    answer = create_array(XZY_ROTATION_FROM);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from XZY extrinsic error");
    result = evs::rotate_from<evs::XYX, evs::ExtrinsicRotation>(angles, test_vector);
    answer = create_array(XYX_ROTATION_FROM);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from XYX extrinsic error");
    result = evs::rotate_from<evs::ZXZ, evs::ExtrinsicRotation>(angles, test_vector);
    answer = create_array(ZXZ_ROTATION_FROM);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from ZXZ extrinsic error");

    result = evs::rotate_to<evs::ZYX, evs::ExtrinsicRotation>(angles, test_vector, offset_vector);
    answer = create_array(XYZ_ROTATION_OFFSET_TO);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector to offset XYZ extrinsic error");
    result = evs::rotate_to<evs::YZX, evs::ExtrinsicRotation>(angles, test_vector, offset_vector);
    answer = create_array(XZY_ROTATION_OFFSET_TO);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector to offset XZY extrinsic error");
    result = evs::rotate_to<evs::XYX, evs::ExtrinsicRotation>(angles, test_vector, offset_vector);
    answer = create_array(XYX_ROTATION_OFFSET_TO);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector to offset XYX extrinsic error");
    result = evs::rotate_to<evs::ZXZ, evs::ExtrinsicRotation>(angles, test_vector, offset_vector);
    answer = create_array(ZXZ_ROTATION_OFFSET_TO);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector to offset ZXZ extrinsic error");

    result = evs::rotate_from<evs::ZYX, evs::ExtrinsicRotation>(angles, test_vector, offset_vector);
    answer = create_array(XYZ_ROTATION_OFFSET_FROM);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset XYZ extrinsic error");
    result = evs::rotate_from<evs::YZX, evs::ExtrinsicRotation>(angles, test_vector, offset_vector);
    answer = create_array(XZY_ROTATION_OFFSET_FROM);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset XZY extrinsic error");
    result = evs::rotate_from<evs::XYX, evs::ExtrinsicRotation>(angles, test_vector, offset_vector);
    answer = create_array(XYX_ROTATION_OFFSET_FROM);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset XYX extrinsic error");
    result = evs::rotate_from<evs::ZXZ, evs::ExtrinsicRotation>(angles, test_vector, offset_vector);
    answer = create_array(ZXZ_ROTATION_OFFSET_FROM);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset ZXZ extrinsic error");
}

TEST(RotationUnitTest, TestEulerFromToVectors) {
    evs::EulerAngles angles_from = evs::EulerAngles(EVSPACE_PI / 6, EVSPACE_PI_4, EVSPACE_PI / 3);
    evs::EulerAngles angles_to = evs::EulerAngles(0, EVSPACE_PI_4, EVSPACE_PI / 2);
    evs::Vector result;
    VectorArray answer;
    const evs::Vector offset_from = evs::Vector(10, 20, 30);
    const evs::Vector offset_to = evs::Vector(100, 200, 300);
    const evs::Vector test_vector = evs::Vector(1, 2, 3);
    const evs::Vector zero_vector = evs::Vector(0, 0, 0);

    result = evs::rotate_between<evs::XYZ, evs::YXY, evs::IntrinsicRotation, evs::IntrinsicRotation>(angles_from, angles_to, test_vector);
    answer = create_array(FROM_XYZ_TO_YXY_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from XYZ to YXY error");
    result = evs::rotate_between<evs::XZY, evs::XYX, evs::IntrinsicRotation, evs::IntrinsicRotation>(angles_from, angles_to, test_vector);
    answer = create_array(FROM_XZY_TO_XYX_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from XZY to XYX error");
    result = evs::rotate_between<evs::XYX, evs::ZYX, evs::IntrinsicRotation, evs::IntrinsicRotation>(angles_from, angles_to, test_vector);
    answer = create_array(FROM_XYX_TO_ZYX_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from XYX to ZYX error");
    result = evs::rotate_between<evs::ZXZ, evs::YZY, evs::IntrinsicRotation, evs::IntrinsicRotation>(angles_from, angles_to, test_vector);
    answer = create_array(FROM_ZXZ_TO_YZY_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from ZXZ to YZY error");

    result = evs::rotate_between<evs::XYZ, evs::YXY, evs::IntrinsicRotation, evs::IntrinsicRotation>(angles_from, angles_to, test_vector, offset_from);
    answer = create_array(FROM_OFFSET_XYZ_TO_YXY_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset XYZ to YXY error");
    result = evs::rotate_between<evs::XZY, evs::XYX, evs::IntrinsicRotation, evs::IntrinsicRotation>(angles_from, angles_to, test_vector, offset_from);
    answer = create_array(FROM_OFFSET_XZY_TO_XYX_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset XZY to XYX error");
    result = evs::rotate_between<evs::XYX, evs::ZYX, evs::IntrinsicRotation, evs::IntrinsicRotation>(angles_from, angles_to, test_vector, offset_from);
    answer = create_array(FROM_OFFSET_XYX_TO_ZYX_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset XYX to ZYX error");
    result = evs::rotate_between<evs::ZXZ, evs::YZY, evs::IntrinsicRotation, evs::IntrinsicRotation>(angles_from, angles_to, test_vector, offset_from);
    answer = create_array(FROM_OFFSET_ZXZ_TO_YZY_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset ZXZ to YZY error");

    result = evs::rotate_between<evs::XYZ, evs::YXY, evs::IntrinsicRotation, evs::IntrinsicRotation>(angles_from, angles_to, test_vector, zero_vector, offset_to);
    answer = create_array(FROM_XYZ_TO_OFFSET_YXY_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from XYZ to offset YXY error");
    result = evs::rotate_between<evs::XZY, evs::XYX, evs::IntrinsicRotation, evs::IntrinsicRotation>(angles_from, angles_to, test_vector, zero_vector, offset_to);
    answer = create_array(FROM_XZY_TO_OFFSET_XYX_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from XZY to offset XYX error");
    result = evs::rotate_between<evs::XYX, evs::ZYX, evs::IntrinsicRotation, evs::IntrinsicRotation>(angles_from, angles_to, test_vector, zero_vector, offset_to);
    answer = create_array(FROM_XYX_TO_OFFSET_ZYX_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from XYX to offset ZYX error");
    result = evs::rotate_between<evs::ZXZ, evs::YZY, evs::IntrinsicRotation, evs::IntrinsicRotation>(angles_from, angles_to, test_vector, zero_vector, offset_to);
    answer = create_array(FROM_ZXZ_TO_OFFSET_YZY_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from ZXZ to offset YZY error");

    result = evs::rotate_between<evs::XYZ, evs::YXY, evs::IntrinsicRotation, evs::IntrinsicRotation>(angles_from, angles_to, test_vector, offset_from, offset_to);
    answer = create_array(FROM_OFFSET_XYZ_TO_OFFSET_YXY_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset XYZ to offset YXY error");
    result = evs::rotate_between<evs::XZY, evs::XYX, evs::IntrinsicRotation, evs::IntrinsicRotation>(angles_from, angles_to, test_vector, offset_from, offset_to);
    answer = create_array(FROM_OFFSET_XZY_TO_OFFSET_XYX_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset XZY to offset XYX error");
    result = evs::rotate_between<evs::XYX, evs::ZYX, evs::IntrinsicRotation, evs::IntrinsicRotation>(angles_from, angles_to, test_vector, offset_from, offset_to);
    answer = create_array(FROM_OFFSET_XYX_TO_OFFSET_ZYX_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset XYX to offset ZYX error");
    result = evs::rotate_between<evs::ZXZ, evs::YZY, evs::IntrinsicRotation, evs::IntrinsicRotation>(angles_from, angles_to, test_vector, offset_from, offset_to);
    answer = create_array(FROM_OFFSET_ZXZ_TO_OFFSET_YZY_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset ZXZ to offset YZY error");

    //  extrinsic tests (only the first reference frame will be extrinsic
    angles_from = evs::EulerAngles(EVSPACE_PI / 3, EVSPACE_PI_4, EVSPACE_PI / 6);
    result = evs::rotate_between<evs::ZYX, evs::YXY, evs::ExtrinsicRotation, evs::IntrinsicRotation>(angles_from, angles_to, test_vector);
    answer = create_array(FROM_XYZ_TO_YXY_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from extrinsic XYZ to YXY error");
    result = evs::rotate_between<evs::YZX, evs::XYX, evs::ExtrinsicRotation, evs::IntrinsicRotation>(angles_from, angles_to, test_vector);
    answer = create_array(FROM_XZY_TO_XYX_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from extrinsic XZY to XYX error");
    result = evs::rotate_between<evs::XYX, evs::ZYX, evs::ExtrinsicRotation, evs::IntrinsicRotation>(angles_from, angles_to, test_vector);
    answer = create_array(FROM_XYX_TO_ZYX_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from extrinsic XYX to ZYX error");
    result = evs::rotate_between<evs::ZXZ, evs::YZY, evs::ExtrinsicRotation, evs::IntrinsicRotation>(angles_from, angles_to, test_vector);
    answer = create_array(FROM_ZXZ_TO_YZY_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from extrinsic ZXZ to YZY error");

    result = evs::rotate_between<evs::ZYX, evs::YXY, evs::ExtrinsicRotation, evs::IntrinsicRotation>(angles_from, angles_to, test_vector, offset_from);
    answer = create_array(FROM_OFFSET_XYZ_TO_YXY_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset extrinsic XYZ to YXY error");
    result = evs::rotate_between<evs::YZX, evs::XYX, evs::ExtrinsicRotation, evs::IntrinsicRotation>(angles_from, angles_to, test_vector, offset_from);
    answer = create_array(FROM_OFFSET_XZY_TO_XYX_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset extrinsic XZY to XYX error");
    result = evs::rotate_between<evs::XYX, evs::ZYX, evs::ExtrinsicRotation, evs::IntrinsicRotation>(angles_from, angles_to, test_vector, offset_from);
    answer = create_array(FROM_OFFSET_XYX_TO_ZYX_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset extrinsic XYX to ZYX error");
    result = evs::rotate_between<evs::ZXZ, evs::YZY, evs::ExtrinsicRotation, evs::IntrinsicRotation>(angles_from, angles_to, test_vector, offset_from);
    answer = create_array(FROM_OFFSET_ZXZ_TO_YZY_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset extrinsic ZXZ to YZY error");

    result = evs::rotate_between<evs::ZYX, evs::YXY, evs::ExtrinsicRotation, evs::IntrinsicRotation>(angles_from, angles_to, test_vector, zero_vector, offset_to);
    answer = create_array(FROM_XYZ_TO_OFFSET_YXY_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from extrinsic XYZ to offset YXY error");
    result = evs::rotate_between<evs::YZX, evs::XYX, evs::ExtrinsicRotation, evs::IntrinsicRotation>(angles_from, angles_to, test_vector, zero_vector, offset_to);
    answer = create_array(FROM_XZY_TO_OFFSET_XYX_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from extrinsic XZY to offset XYX error");
    result = evs::rotate_between<evs::XYX, evs::ZYX, evs::ExtrinsicRotation, evs::IntrinsicRotation>(angles_from, angles_to, test_vector, zero_vector, offset_to);
    answer = create_array(FROM_XYX_TO_OFFSET_ZYX_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from extrinsic XYX to offset ZYX error");
    result = evs::rotate_between<evs::ZXZ, evs::YZY, evs::ExtrinsicRotation, evs::IntrinsicRotation>(angles_from, angles_to, test_vector, zero_vector, offset_to);
    answer = create_array(FROM_ZXZ_TO_OFFSET_YZY_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from extrinsic ZXZ to offset YZY error");
    
    result = evs::rotate_between<evs::ZYX, evs::YXY, evs::ExtrinsicRotation, evs::IntrinsicRotation>(angles_from, angles_to, test_vector, offset_from, offset_to);
    answer = create_array(FROM_OFFSET_XYZ_TO_OFFSET_YXY_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset extrinsic XYZ to offset YXY error");
    result = evs::rotate_between<evs::YZX, evs::XYX, evs::ExtrinsicRotation, evs::IntrinsicRotation>(angles_from, angles_to, test_vector, offset_from, offset_to);
    answer = create_array(FROM_OFFSET_XZY_TO_OFFSET_XYX_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset extrinsic XZY to offset XYX error");
    result = evs::rotate_between<evs::XYX, evs::ZYX, evs::ExtrinsicRotation, evs::IntrinsicRotation>(angles_from, angles_to, test_vector, offset_from, offset_to);
    answer = create_array(FROM_OFFSET_XYX_TO_OFFSET_ZYX_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset extrinsic XYX to offset ZYX error");
    result = evs::rotate_between<evs::ZXZ, evs::YZY, evs::ExtrinsicRotation, evs::IntrinsicRotation>(angles_from, angles_to, test_vector, offset_from, offset_to);
    answer = create_array(FROM_OFFSET_ZXZ_TO_OFFSET_YZY_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset extrinsic ZXZ to offset YZY error");
}