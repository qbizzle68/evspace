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

using namespace evspace;

TEST(RotationUnitTest, TestSingleAxisRotationMatrix) {
    const double angle = EVSPACE_PI_4;
    Matrix result;
    MatrixArray answer;

    result = compute_rotation_matrix<XAxis>(angle);
    answer = create_array(X_AXIS_ROTATION_MATRIX);
    _COMPARE_MATRIX_NEAR(result, answer, "X axis rotation matrix error");
    result = compute_rotation_matrix<YAxis>(angle);
    answer = create_array(Y_AXIS_ROTATION_MATRIX);
    _COMPARE_MATRIX_NEAR(result, answer, "Y axis rotation matrix error");
    result = compute_rotation_matrix<ZAxis>(angle);
    answer = create_array(Z_AXIS_ROTATION_MATRIX);
    _COMPARE_MATRIX_NEAR(result, answer, "Z axis rotation matrix error");

    //  extrinsic axis rotations (this should be sufficient to test
    result = compute_rotation_matrix(angle, Vector::e1);
    answer = create_array(X_AXIS_ROTATION_MATRIX);
    _COMPARE_MATRIX_NEAR(result, answer, "X axis extrinsic rotation matrix error");
    result = compute_rotation_matrix(angle, Vector::e2);
    answer = create_array(Y_AXIS_ROTATION_MATRIX);
    _COMPARE_MATRIX_NEAR(result, answer, "Y axis extrinsic rotation matrix error");
    result = compute_rotation_matrix(angle, Vector::e3);
    answer = create_array(Z_AXIS_ROTATION_MATRIX);
    _COMPARE_MATRIX_NEAR(result, answer, "Z axis extrinsic rotation matrix error");
}

TEST(RotationUnitTest, TestEulerRotationMatrix) {
    EulerAngles angles = EulerAngles(EVSPACE_PI / 6, EVSPACE_PI / 4, EVSPACE_PI / 3);
    Matrix result;
    MatrixArray answer;

    result = compute_rotation_matrix<XYZ, IntrinsicRotation>(angles);
    answer = create_array(XYZ_ROTATION_MATRIX);
    _COMPARE_MATRIX_NEAR(result, answer, "XYZ intrinsic rotation matrix error");
    result = compute_rotation_matrix<XZY, IntrinsicRotation>(angles);
    answer = create_array(XZY_ROTATION_MATRIX);
    _COMPARE_MATRIX_NEAR(result, answer, "XZY intrinsic rotation matrix error");
    result = compute_rotation_matrix<XYX, IntrinsicRotation>(angles);
    answer = create_array(XYX_ROTATION_MATRIX);
    _COMPARE_MATRIX_NEAR(result, answer, "XYX intrinsic rotation matrix error");
    result = compute_rotation_matrix<ZXZ, IntrinsicRotation>(angles);
    answer = create_array(ZXZ_ROTATION_MATRIX);
    _COMPARE_MATRIX_NEAR(result, answer, "ZXZ intrinsic rotation matrix error");

    // our answers are for intrinsic rotations only, so we build the equivalent extrinsic rotation
    angles = EulerAngles(EVSPACE_PI / 3, EVSPACE_PI / 4, EVSPACE_PI / 6);
    result = compute_rotation_matrix<ZYX, ExtrinsicRotation>(angles);
    answer = create_array(XYZ_ROTATION_MATRIX);
    _COMPARE_MATRIX_NEAR(result, answer, "XYZ extrinsic rotation matrix error");
    result = compute_rotation_matrix<YZX, ExtrinsicRotation>(angles);
    answer = create_array(XZY_ROTATION_MATRIX);
    _COMPARE_MATRIX_NEAR(result, answer, "XZY extrinsic rotation matrix error");
    result = compute_rotation_matrix<XYX, ExtrinsicRotation>(angles);
    answer = create_array(XYX_ROTATION_MATRIX);
    _COMPARE_MATRIX_NEAR(result, answer, "XYX extrinsic rotation matrix error");
    result = compute_rotation_matrix<ZXZ, ExtrinsicRotation>(angles);
    answer = create_array(ZXZ_ROTATION_MATRIX);
    _COMPARE_MATRIX_NEAR(result, answer, "ZXZ extrinsic rotation matrix error");
}

TEST(RotationUnitTest, TestEulerFromTo) {
    auto angles_to = EulerAngles(0.0, EVSPACE_PI_4, EVSPACE_PI_2);
    auto angles_from = EulerAngles(EVSPACE_PI / 6, EVSPACE_PI_4, EVSPACE_PI / 3);
    Matrix result;
    MatrixArray answer;

    result = compute_rotation_matrix<XYZ, YXY, IntrinsicRotation, IntrinsicRotation>(angles_from, angles_to);
    answer = create_array(XYZ_TO_YXY_ROTATION_MATRIX);
    _COMPARE_MATRIX_NEAR(result, answer, "from XYZ to YXY euler rotation matrix error");
    result = compute_rotation_matrix<XZY, XYX, IntrinsicRotation, IntrinsicRotation>(angles_from, angles_to);
    answer = create_array(XZY_TO_XYX_ROTATION_MATRIX);
    _COMPARE_MATRIX_NEAR(result, answer, "from XZY to XYX euler rotation matrix error");
    result = compute_rotation_matrix<XYX, ZYX, IntrinsicRotation, IntrinsicRotation>(angles_from, angles_to);
    answer = create_array(XYX_TO_ZYX_ROTATION_MATRIX);
    _COMPARE_MATRIX_NEAR(result, answer, "from XYX to ZYX euler rotation matrix error");
    result = compute_rotation_matrix<ZXZ, YZY, IntrinsicRotation, IntrinsicRotation>(angles_from, angles_to);
    answer = create_array(ZXZ_TO_YZY_ROTATION_MATRIX);
    _COMPARE_MATRIX_NEAR(result, answer, "from ZXZ to YZY euler rotation matrix error");

    // make the first rotation be extrinsic (need to make orders to reflect the answers we have)
    angles_from = EulerAngles(EVSPACE_PI / 3, EVSPACE_PI_4, EVSPACE_PI / 6);
    result = compute_rotation_matrix<ZYX, YXY, ExtrinsicRotation, IntrinsicRotation>(angles_from, angles_to);
    answer = create_array(XYZ_TO_YXY_ROTATION_MATRIX);
    _COMPARE_MATRIX_NEAR(result, answer, "from XYZ to YXY euler rotation matrix error");
    result = compute_rotation_matrix<YZX, XYX, ExtrinsicRotation, IntrinsicRotation>(angles_from, angles_to);
    answer = create_array(XZY_TO_XYX_ROTATION_MATRIX);
    _COMPARE_MATRIX_NEAR(result, answer, "from XZY to XYX euler rotation matrix error");
    result = compute_rotation_matrix<XYX, ZYX, ExtrinsicRotation, IntrinsicRotation>(angles_from, angles_to);
    answer = create_array(XYX_TO_ZYX_ROTATION_MATRIX);
    _COMPARE_MATRIX_NEAR(result, answer, "from XYX to ZYX euler rotation matrix error");
    result = compute_rotation_matrix<ZXZ, YZY, ExtrinsicRotation, IntrinsicRotation>(angles_from, angles_to);
    answer = create_array(ZXZ_TO_YZY_ROTATION_MATRIX);
    _COMPARE_MATRIX_NEAR(result, answer, "from ZXZ to YZY euler rotation matrix error");
}

TEST(RotationUnitTest, TestSingleAxisRotationVectors) {
    const double angle = EVSPACE_PI_4;
    Vector offset_vector = Vector(10, 20, 30);
    const Vector test_vector = Vector(1, 2, 3);
    Vector result;
    VectorArray answer;

    result = rotate_to<XAxis>(angle, test_vector);
    answer = create_array(X_AXIS_ROTATION_TO);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate to X-axis vector error");
    result = rotate_to<YAxis>(angle, test_vector);
    answer = create_array(Y_AXIS_ROTATION_TO);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate to Y-axis vector error");
    result = rotate_to<ZAxis>(angle, test_vector);
    answer = create_array(Z_AXIS_ROTATION_TO);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate to Z-axis vector error");

    result = rotate_from<XAxis>(angle, test_vector);
    answer = create_array(X_AXIS_ROTATION_FROM);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate from X-axis vector error");
    result = rotate_from<YAxis>(angle, test_vector);
    answer = create_array(Y_AXIS_ROTATION_FROM);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate from Y-axis vector error");
    result = rotate_from<ZAxis>(angle, test_vector);
    answer = create_array(Z_AXIS_ROTATION_FROM);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate from Z-axis vector error");

    result = rotate_to<XAxis>(angle, test_vector, offset_vector);
    answer = create_array(X_AXIS_ROTATION_OFFSET_TO);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate to offset X-axis vector error");
    result = rotate_to<YAxis>(angle, test_vector, offset_vector);
    answer = create_array(Y_AXIS_ROTATION_OFFSET_TO);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate to offset Y-axis vector error");
    result = rotate_to<ZAxis>(angle, test_vector, offset_vector);
    answer = create_array(Z_AXIS_ROTATION_OFFSET_TO);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate to offset Z-axis vector error");

    result = rotate_from<XAxis>(angle, test_vector, offset_vector);
    answer = create_array(X_AXIS_ROTATION_OFFSET_FROM);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate from offset X-axis vector error");
    result = rotate_from<YAxis>(angle, test_vector, offset_vector);
    answer = create_array(Y_AXIS_ROTATION_OFFSET_FROM);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate from offset Y-axis vector error");
    result = rotate_from<ZAxis>(angle, test_vector, offset_vector);
    answer = create_array(Z_AXIS_ROTATION_OFFSET_FROM);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate from offset Z-axis vector error");
}

TEST(RotationUnitTest, TestEulerRotationVectors) {
    EulerAngles angles = EulerAngles(EVSPACE_PI / 6, EVSPACE_PI_4, EVSPACE_PI / 3);
    Vector result;
    VectorArray answer;
    const Vector test_vector = Vector(1, 2, 3);
    const Vector offset_vector = Vector(10, 20, 30);

    result = rotate_to<XYZ, IntrinsicRotation>(angles, test_vector);
    answer = create_array(XYZ_ROTATION_TO);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector to XYZ error");
    result = rotate_to<XZY, IntrinsicRotation>(angles, test_vector);
    answer = create_array(XZY_ROTATION_TO);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector to XZY error");
    result = rotate_to<XYX, IntrinsicRotation>(angles, test_vector);
    answer = create_array(XYX_ROTATION_TO);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector to XYX error");
    result = rotate_to<ZXZ, IntrinsicRotation>(angles, test_vector);
    answer = create_array(ZXZ_ROTATION_TO);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector to ZXZ error");

    result = rotate_from<XYZ, IntrinsicRotation>(angles, test_vector);
    answer = create_array(XYZ_ROTATION_FROM);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from XYZ error");
    result = rotate_from<XZY, IntrinsicRotation>(angles, test_vector);
    answer = create_array(XZY_ROTATION_FROM);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from XZY error");
    result = rotate_from<XYX, IntrinsicRotation>(angles, test_vector);
    answer = create_array(XYX_ROTATION_FROM);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from XYX error");
    result = rotate_from<ZXZ, IntrinsicRotation>(angles, test_vector);
    answer = create_array(ZXZ_ROTATION_FROM);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from ZXZ error");

    result = rotate_to<XYZ, IntrinsicRotation>(angles, test_vector, offset_vector);
    answer = create_array(XYZ_ROTATION_OFFSET_TO);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector to offset XYZ error");
    result = rotate_to<XZY, IntrinsicRotation>(angles, test_vector, offset_vector);
    answer = create_array(XZY_ROTATION_OFFSET_TO);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector to offset XZY error");
    result = rotate_to<XYX, IntrinsicRotation>(angles, test_vector, offset_vector);
    answer = create_array(XYX_ROTATION_OFFSET_TO);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector to offset XYX error");
    result = rotate_to<ZXZ, IntrinsicRotation>(angles, test_vector, offset_vector);
    answer = create_array(ZXZ_ROTATION_OFFSET_TO);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector to offset ZXZ error");

    result = rotate_from<XYZ, IntrinsicRotation>(angles, test_vector, offset_vector);
    answer = create_array(XYZ_ROTATION_OFFSET_FROM);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset XYZ error");
    result = rotate_from<XZY, IntrinsicRotation>(angles, test_vector, offset_vector);
    answer = create_array(XZY_ROTATION_OFFSET_FROM);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset XZY error");
    result = rotate_from<XYX, IntrinsicRotation>(angles, test_vector, offset_vector);
    answer = create_array(XYX_ROTATION_OFFSET_FROM);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset XYX error");
    result = rotate_from<ZXZ, IntrinsicRotation>(angles, test_vector, offset_vector);
    answer = create_array(ZXZ_ROTATION_OFFSET_FROM);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset ZXZ error");

    // extrinsic tests
    angles = EulerAngles(EVSPACE_PI / 3, EVSPACE_PI_4, EVSPACE_PI / 6);
    result = rotate_to<ZYX, ExtrinsicRotation>(angles, test_vector);
    answer = create_array(XYZ_ROTATION_TO);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector to XYZ extrinsic error");
    result = rotate_to<YZX, ExtrinsicRotation>(angles, test_vector);
    answer = create_array(XZY_ROTATION_TO);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector to XZY extrinsic error");
    result = rotate_to<XYX, ExtrinsicRotation>(angles, test_vector);
    answer = create_array(XYX_ROTATION_TO);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector to XYX extrinsic error");
    result = rotate_to<ZXZ, ExtrinsicRotation>(angles, test_vector);
    answer = create_array(ZXZ_ROTATION_TO);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector to ZXZ extrinsic error");

    result = rotate_from<ZYX, ExtrinsicRotation>(angles, test_vector);
    answer = create_array(XYZ_ROTATION_FROM);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from XYZ extrinsic error");
    result = rotate_from<YZX, ExtrinsicRotation>(angles, test_vector);
    answer = create_array(XZY_ROTATION_FROM);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from XZY extrinsic error");
    result = rotate_from<XYX, ExtrinsicRotation>(angles, test_vector);
    answer = create_array(XYX_ROTATION_FROM);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from XYX extrinsic error");
    result = rotate_from<ZXZ, ExtrinsicRotation>(angles, test_vector);
    answer = create_array(ZXZ_ROTATION_FROM);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from ZXZ extrinsic error");

    result = rotate_to<ZYX, ExtrinsicRotation>(angles, test_vector, offset_vector);
    answer = create_array(XYZ_ROTATION_OFFSET_TO);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector to offset XYZ extrinsic error");
    result = rotate_to<YZX, ExtrinsicRotation>(angles, test_vector, offset_vector);
    answer = create_array(XZY_ROTATION_OFFSET_TO);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector to offset XZY extrinsic error");
    result = rotate_to<XYX, ExtrinsicRotation>(angles, test_vector, offset_vector);
    answer = create_array(XYX_ROTATION_OFFSET_TO);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector to offset XYX extrinsic error");
    result = rotate_to<ZXZ, ExtrinsicRotation>(angles, test_vector, offset_vector);
    answer = create_array(ZXZ_ROTATION_OFFSET_TO);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector to offset ZXZ extrinsic error");

    result = rotate_from<ZYX, ExtrinsicRotation>(angles, test_vector, offset_vector);
    answer = create_array(XYZ_ROTATION_OFFSET_FROM);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset XYZ extrinsic error");
    result = rotate_from<YZX, ExtrinsicRotation>(angles, test_vector, offset_vector);
    answer = create_array(XZY_ROTATION_OFFSET_FROM);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset XZY extrinsic error");
    result = rotate_from<XYX, ExtrinsicRotation>(angles, test_vector, offset_vector);
    answer = create_array(XYX_ROTATION_OFFSET_FROM);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset XYX extrinsic error");
    result = rotate_from<ZXZ, ExtrinsicRotation>(angles, test_vector, offset_vector);
    answer = create_array(ZXZ_ROTATION_OFFSET_FROM);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset ZXZ extrinsic error");
}

TEST(RotationUnitTest, TestEulerFromToVectors) {
    EulerAngles angles_from = EulerAngles(EVSPACE_PI / 6, EVSPACE_PI_4, EVSPACE_PI / 3);
    EulerAngles angles_to = EulerAngles(0, EVSPACE_PI_4, EVSPACE_PI / 2);
    Vector result;
    VectorArray answer;
    const Vector offset_from = Vector(10, 20, 30);
    const Vector offset_to = Vector(100, 200, 300);
    const Vector test_vector = Vector(1, 2, 3);
    const Vector zero_vector = Vector(0, 0, 0);

    result = rotate_between<XYZ, YXY, IntrinsicRotation, IntrinsicRotation>(angles_from, angles_to, test_vector);
    answer = create_array(FROM_XYZ_TO_YXY_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from XYZ to YXY error");
    result = rotate_between<XZY, XYX, IntrinsicRotation, IntrinsicRotation>(angles_from, angles_to, test_vector);
    answer = create_array(FROM_XZY_TO_XYX_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from XZY to XYX error");
    result = rotate_between<XYX, ZYX, IntrinsicRotation, IntrinsicRotation>(angles_from, angles_to, test_vector);
    answer = create_array(FROM_XYX_TO_ZYX_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from XYX to ZYX error");
    result = rotate_between<ZXZ, YZY, IntrinsicRotation, IntrinsicRotation>(angles_from, angles_to, test_vector);
    answer = create_array(FROM_ZXZ_TO_YZY_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from ZXZ to YZY error");

    result = rotate_between<XYZ, YXY, IntrinsicRotation, IntrinsicRotation>(angles_from, angles_to, test_vector, offset_from);
    answer = create_array(FROM_OFFSET_XYZ_TO_YXY_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset XYZ to YXY error");
    result = rotate_between<XZY, XYX, IntrinsicRotation, IntrinsicRotation>(angles_from, angles_to, test_vector, offset_from);
    answer = create_array(FROM_OFFSET_XZY_TO_XYX_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset XZY to XYX error");
    result = rotate_between<XYX, ZYX, IntrinsicRotation, IntrinsicRotation>(angles_from, angles_to, test_vector, offset_from);
    answer = create_array(FROM_OFFSET_XYX_TO_ZYX_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset XYX to ZYX error");
    result = rotate_between<ZXZ, YZY, IntrinsicRotation, IntrinsicRotation>(angles_from, angles_to, test_vector, offset_from);
    answer = create_array(FROM_OFFSET_ZXZ_TO_YZY_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset ZXZ to YZY error");

    result = rotate_between<XYZ, YXY, IntrinsicRotation, IntrinsicRotation>(angles_from, angles_to, test_vector, zero_vector, offset_to);
    answer = create_array(FROM_XYZ_TO_OFFSET_YXY_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from XYZ to offset YXY error");
    result = rotate_between<XZY, XYX, IntrinsicRotation, IntrinsicRotation>(angles_from, angles_to, test_vector, zero_vector, offset_to);
    answer = create_array(FROM_XZY_TO_OFFSET_XYX_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from XZY to offset XYX error");
    result = rotate_between<XYX, ZYX, IntrinsicRotation, IntrinsicRotation>(angles_from, angles_to, test_vector, zero_vector, offset_to);
    answer = create_array(FROM_XYX_TO_OFFSET_ZYX_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from XYX to offset ZYX error");
    result = rotate_between<ZXZ, YZY, IntrinsicRotation, IntrinsicRotation>(angles_from, angles_to, test_vector, zero_vector, offset_to);
    answer = create_array(FROM_ZXZ_TO_OFFSET_YZY_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from ZXZ to offset YZY error");

    result = rotate_between<XYZ, YXY, IntrinsicRotation, IntrinsicRotation>(angles_from, angles_to, test_vector, offset_from, offset_to);
    answer = create_array(FROM_OFFSET_XYZ_TO_OFFSET_YXY_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset XYZ to offset YXY error");
    result = rotate_between<XZY, XYX, IntrinsicRotation, IntrinsicRotation>(angles_from, angles_to, test_vector, offset_from, offset_to);
    answer = create_array(FROM_OFFSET_XZY_TO_OFFSET_XYX_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset XZY to offset XYX error");
    result = rotate_between<XYX, ZYX, IntrinsicRotation, IntrinsicRotation>(angles_from, angles_to, test_vector, offset_from, offset_to);
    answer = create_array(FROM_OFFSET_XYX_TO_OFFSET_ZYX_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset XYX to offset ZYX error");
    result = rotate_between<ZXZ, YZY, IntrinsicRotation, IntrinsicRotation>(angles_from, angles_to, test_vector, offset_from, offset_to);
    answer = create_array(FROM_OFFSET_ZXZ_TO_OFFSET_YZY_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset ZXZ to offset YZY error");

    //  extrinsic tests (only the first reference frame will be extrinsic
    angles_from = EulerAngles(EVSPACE_PI / 3, EVSPACE_PI_4, EVSPACE_PI / 6);
    result = rotate_between<ZYX, YXY, ExtrinsicRotation, IntrinsicRotation>(angles_from, angles_to, test_vector);
    answer = create_array(FROM_XYZ_TO_YXY_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from extrinsic XYZ to YXY error");
    result = rotate_between<YZX, XYX, ExtrinsicRotation, IntrinsicRotation>(angles_from, angles_to, test_vector);
    answer = create_array(FROM_XZY_TO_XYX_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from extrinsic XZY to XYX error");
    result = rotate_between<XYX, ZYX, ExtrinsicRotation, IntrinsicRotation>(angles_from, angles_to, test_vector);
    answer = create_array(FROM_XYX_TO_ZYX_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from extrinsic XYX to ZYX error");
    result = rotate_between<ZXZ, YZY, ExtrinsicRotation, IntrinsicRotation>(angles_from, angles_to, test_vector);
    answer = create_array(FROM_ZXZ_TO_YZY_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from extrinsic ZXZ to YZY error");

    result = rotate_between<ZYX, YXY, ExtrinsicRotation, IntrinsicRotation>(angles_from, angles_to, test_vector, offset_from);
    answer = create_array(FROM_OFFSET_XYZ_TO_YXY_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset extrinsic XYZ to YXY error");
    result = rotate_between<YZX, XYX, ExtrinsicRotation, IntrinsicRotation>(angles_from, angles_to, test_vector, offset_from);
    answer = create_array(FROM_OFFSET_XZY_TO_XYX_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset extrinsic XZY to XYX error");
    result = rotate_between<XYX, ZYX, ExtrinsicRotation, IntrinsicRotation>(angles_from, angles_to, test_vector, offset_from);
    answer = create_array(FROM_OFFSET_XYX_TO_ZYX_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset extrinsic XYX to ZYX error");
    result = rotate_between<ZXZ, YZY, ExtrinsicRotation, IntrinsicRotation>(angles_from, angles_to, test_vector, offset_from);
    answer = create_array(FROM_OFFSET_ZXZ_TO_YZY_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset extrinsic ZXZ to YZY error");

    result = rotate_between<ZYX, YXY, ExtrinsicRotation, IntrinsicRotation>(angles_from, angles_to, test_vector, zero_vector, offset_to);
    answer = create_array(FROM_XYZ_TO_OFFSET_YXY_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from extrinsic XYZ to offset YXY error");
    result = rotate_between<YZX, XYX, ExtrinsicRotation, IntrinsicRotation>(angles_from, angles_to, test_vector, zero_vector, offset_to);
    answer = create_array(FROM_XZY_TO_OFFSET_XYX_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from extrinsic XZY to offset XYX error");
    result = rotate_between<XYX, ZYX, ExtrinsicRotation, IntrinsicRotation>(angles_from, angles_to, test_vector, zero_vector, offset_to);
    answer = create_array(FROM_XYX_TO_OFFSET_ZYX_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from extrinsic XYX to offset ZYX error");
    result = rotate_between<ZXZ, YZY, ExtrinsicRotation, IntrinsicRotation>(angles_from, angles_to, test_vector, zero_vector, offset_to);
    answer = create_array(FROM_ZXZ_TO_OFFSET_YZY_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from extrinsic ZXZ to offset YZY error");
    
    result = rotate_between<ZYX, YXY, ExtrinsicRotation, IntrinsicRotation>(angles_from, angles_to, test_vector, offset_from, offset_to);
    answer = create_array(FROM_OFFSET_XYZ_TO_OFFSET_YXY_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset extrinsic XYZ to offset YXY error");
    result = rotate_between<YZX, XYX, ExtrinsicRotation, IntrinsicRotation>(angles_from, angles_to, test_vector, offset_from, offset_to);
    answer = create_array(FROM_OFFSET_XZY_TO_OFFSET_XYX_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset extrinsic XZY to offset XYX error");
    result = rotate_between<XYX, ZYX, ExtrinsicRotation, IntrinsicRotation>(angles_from, angles_to, test_vector, offset_from, offset_to);
    answer = create_array(FROM_OFFSET_XYX_TO_OFFSET_ZYX_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset extrinsic XYX to offset ZYX error");
    result = rotate_between<ZXZ, YZY, ExtrinsicRotation, IntrinsicRotation>(angles_from, angles_to, test_vector, offset_from, offset_to);
    answer = create_array(FROM_OFFSET_ZXZ_TO_OFFSET_YZY_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset extrinsic ZXZ to offset YZY error");
}