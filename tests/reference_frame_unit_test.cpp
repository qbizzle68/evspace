/**
* Test files are built using cmake precompiled headers which are made
* visible to this file when building tests and are not explicitly
* included.
*
*/

#include <angles.hpp>
#include <vector.hpp>
#include <matrix.hpp>
#include <rotation.hpp>
#include "resources/test_rotation_matrices.hpp"
#include "resources/test_rotation_vectors.hpp"

using namespace evspace;

TEST(ReferenceFrameUnitTest, TestCreation) {
    Matrix matrix_result;
    MatrixArray matrix_answer;
    Vector vector_result;
    VectorArray vector_answer;

    EulerAngles angles = EulerAngles(EVSPACE_PI / 6, EVSPACE_PI_4, EVSPACE_PI / 3);
    auto frame = ReferenceFrame<XYZ, IntrinsicRotation>(angles);
    matrix_result = frame.get_matrix();
    matrix_answer = create_array(XYZ_ROTATION_MATRIX);
    _COMPARE_MATRIX_NEAR(matrix_result, matrix_answer, "ReferenceFrame initialization XYZ 30-45-60 matrix error");

    vector_result = frame.get_offset();
    vector_answer = create_array({ 0, 0, 0 });
    _COMPARE_VECTOR_NEAR(vector_result, vector_answer, "ReferenceFrame without offset, offset vector error");

    auto frame_angles = frame.get_angles();
    EXPECT_EQ(angles[0], frame_angles[0]) << "ReferenceFrame 30-45-60 angles getter alpha angle error";
    EXPECT_EQ(angles[1], frame_angles[1]) << "ReferenceFrame 30-45-60 angles getter beta angle error";
    EXPECT_EQ(angles[2], frame_angles[2]) << "ReferenceFrame 30-45-60 angles getter gamma angle error";

    Vector offset = Vector(1, 2, 3);
    angles = EulerAngles(EVSPACE_PI / 3, EVSPACE_PI_4, EVSPACE_PI / 6);
    auto extrinsic_frame = ReferenceFrame<ZYX, ExtrinsicRotation>(angles, offset);
    vector_result = extrinsic_frame.get_offset();
    COMPARE_VECTOR(vector_result, offset, "ReferenceFrame offset initialization get_offset error");
    matrix_result = extrinsic_frame.get_matrix();
    _COMPARE_MATRIX_NEAR(matrix_result, matrix_answer, "Extrinsic ReferenceFrame XYZ 30-45-60 matrix error");
}

TEST(ReferenceFrameUnitTest, TestSetters) {
    EulerAngles angles = EulerAngles(0, 0, 0);
    auto frame = ReferenceFrame<XYZ, IntrinsicRotation>(angles);

    angles = EulerAngles(EVSPACE_PI / 6, EVSPACE_PI_4, EVSPACE_PI / 3);
    frame.set_angles(angles);
    Matrix matrix_result = frame.get_matrix();
    MatrixArray matrix_answer = create_array(XYZ_ROTATION_MATRIX);
    _COMPARE_MATRIX_NEAR(matrix_result, matrix_answer, "ReferenceFrame set angles new matrix error");
    EulerAngles frame_angles = frame.get_angles();
    EXPECT_EQ(angles[0], frame_angles[0]) << "ReferenceFrame 30-45-60 angles getter alpha angle error";
    EXPECT_EQ(angles[1], frame_angles[1]) << "ReferenceFrame 30-45-60 angles getter beta angle error";
    EXPECT_EQ(angles[2], frame_angles[2]) << "ReferenceFrame 30-45-60 angles getter gamma angle error";

    Vector offset = Vector(1, 2, 3);
    frame.set_offset(offset);
    Vector vector_result = frame.get_offset();
    COMPARE_VECTOR(vector_result, offset, "ReferenceFrame set offset error");
}

TEST(ReferenceFrameUnitTest, TestRotationMatrices) {
    EulerAngles angles = EulerAngles(EVSPACE_PI / 6, EVSPACE_PI_4, EVSPACE_PI / 3);
    Matrix result;
    MatrixArray answer;

    auto frame_XYZ = ReferenceFrame<XYZ, IntrinsicRotation>(angles);
    result = frame_XYZ.get_matrix();
    answer = create_array(XYZ_ROTATION_MATRIX);
    _COMPARE_MATRIX_NEAR(result, answer, "XYZ intrinsic rotation matrix error");
    auto frame_XZY = ReferenceFrame<XZY, IntrinsicRotation>(angles);
    result = frame_XZY.get_matrix();
    answer = create_array(XZY_ROTATION_MATRIX);
    _COMPARE_MATRIX_NEAR(result, answer, "XZY intrinsic rotation matrix error");
    auto frame_XYX = ReferenceFrame<XYX, IntrinsicRotation>(angles);
    result = frame_XYX.get_matrix();
    answer = create_array(XYX_ROTATION_MATRIX);
    _COMPARE_MATRIX_NEAR(result, answer, "XYX intrinsic rotation matrix error");
    auto frame_ZXZ = ReferenceFrame<ZXZ, IntrinsicRotation>(angles);
    result = frame_ZXZ.get_matrix();
    answer = create_array(ZXZ_ROTATION_MATRIX);
    _COMPARE_MATRIX_NEAR(result, answer, "ZXZ intrinsic rotation matrix error");

    // our answers are for intrinsic rotations only, so we build the equivalent extrinsic rotation
    angles = EulerAngles(EVSPACE_PI / 3, EVSPACE_PI / 4, EVSPACE_PI / 6);
    auto frame_XYZ_extrinsic = ReferenceFrame<ZYX, ExtrinsicRotation>(angles);
    result = frame_XYZ_extrinsic.get_matrix();
    answer = create_array(XYZ_ROTATION_MATRIX);
    _COMPARE_MATRIX_NEAR(result, answer, "XYZ extrinsic rotation matrix error");
    auto frame_XZY_extrinsic = ReferenceFrame<YZX, ExtrinsicRotation>(angles);
    result = frame_XZY_extrinsic.get_matrix();
    answer = create_array(XZY_ROTATION_MATRIX);
    _COMPARE_MATRIX_NEAR(result, answer, "XZY extrinsic rotation matrix error");
    auto frame_XYX_extrinsic = ReferenceFrame<XYX, ExtrinsicRotation>(angles);
    result = frame_XYX_extrinsic.get_matrix();
    answer = create_array(XYX_ROTATION_MATRIX);
    _COMPARE_MATRIX_NEAR(result, answer, "XYX extrinsic rotation matrix error");
    auto frame_ZXZ_extrinsic = ReferenceFrame<ZXZ, ExtrinsicRotation>(angles);
    result = frame_ZXZ_extrinsic.get_matrix();
    answer = create_array(ZXZ_ROTATION_MATRIX);
    _COMPARE_MATRIX_NEAR(result, answer, "ZXZ extrinsic rotation matrix error");
}

TEST(ReferenceFrameUnitTest, TestRotationVectors) {
    EulerAngles angles = EulerAngles(EVSPACE_PI / 6, EVSPACE_PI_4, EVSPACE_PI / 3);
    Vector result;
    VectorArray answer;
    const Vector test_vector = Vector(1, 2, 3);
    const Vector offset_vector = Vector(10, 20, 30);

    auto frame_XYZ = ReferenceFrame<XYZ, IntrinsicRotation>(angles);
    result = frame_XYZ.rotate_to(test_vector);
    answer = create_array(XYZ_ROTATION_TO);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector to XYZ error");
    auto frame_XZY = ReferenceFrame<XZY, IntrinsicRotation>(angles);
    result = frame_XZY.rotate_to(test_vector);
    answer = create_array(XZY_ROTATION_TO);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector to XZY error");
    auto frame_XYX = ReferenceFrame<XYX, IntrinsicRotation>(angles);
    result = frame_XYX.rotate_to(test_vector);
    answer = create_array(XYX_ROTATION_TO);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector to XYX error");
    auto frame_ZXZ = ReferenceFrame<ZXZ, IntrinsicRotation>(angles);
    result = frame_ZXZ.rotate_to(test_vector);
    answer = create_array(ZXZ_ROTATION_TO);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector to ZXZ error");

    result = frame_XYZ.rotate_from(test_vector);
    answer = create_array(XYZ_ROTATION_FROM);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from XYZ error");
    result = frame_XZY.rotate_from(test_vector);
    answer = create_array(XZY_ROTATION_FROM);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from XZY error");
    result = frame_XYX.rotate_from(test_vector);
    answer = create_array(XYX_ROTATION_FROM);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from XYX error");
    result = frame_ZXZ.rotate_from(test_vector);
    answer = create_array(ZXZ_ROTATION_FROM);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from ZXZ error");

    frame_XYZ.set_offset(offset_vector);
    result = frame_XYZ.rotate_to(test_vector);
    answer = create_array(XYZ_ROTATION_OFFSET_TO);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector to offset XYZ error");
    frame_XZY.set_offset(offset_vector);
    result = frame_XZY.rotate_to(test_vector);
    answer = create_array(XZY_ROTATION_OFFSET_TO);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector to offset XZY error");
    frame_XYX.set_offset(offset_vector);
    result = frame_XYX.rotate_to(test_vector);
    answer = create_array(XYX_ROTATION_OFFSET_TO);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector to offset XYX error");
    frame_ZXZ.set_offset(offset_vector);
    result = frame_ZXZ.rotate_to(test_vector);
    answer = create_array(ZXZ_ROTATION_OFFSET_TO);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector to offset ZXZ error");


    result = frame_XYZ.rotate_from(test_vector);
    answer = create_array(XYZ_ROTATION_OFFSET_FROM);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset XYZ error");
    result = frame_XZY.rotate_from(test_vector);
    answer = create_array(XZY_ROTATION_OFFSET_FROM);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset XZY error");
    result = frame_XYX.rotate_from(test_vector);
    answer = create_array(XYX_ROTATION_OFFSET_FROM);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset XYX error");
    result = frame_ZXZ.rotate_from(test_vector);
    answer = create_array(ZXZ_ROTATION_OFFSET_FROM);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset ZXZ error");

    // extrinsic tests
    angles = EulerAngles(EVSPACE_PI / 3, EVSPACE_PI_4, EVSPACE_PI / 6);
    auto frame_XYZ_extrinsic = ReferenceFrame<ZYX, ExtrinsicRotation>(angles);
    result = frame_XYZ_extrinsic.rotate_to(test_vector);
    answer = create_array(XYZ_ROTATION_TO);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector to XYZ extrinsic error");
    auto frame_XZY_extrinsic = ReferenceFrame<YZX, ExtrinsicRotation>(angles);
    result = frame_XZY_extrinsic.rotate_to(test_vector);
    answer = create_array(XZY_ROTATION_TO);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector to XZY extrinsic error");
    auto frame_XYX_extrinsic = ReferenceFrame<XYX, ExtrinsicRotation>(angles);
    result = frame_XYX_extrinsic.rotate_to(test_vector);
    answer = create_array(XYX_ROTATION_TO);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector to XYX extrinsic error");
    auto frame_ZXZ_extrinsic = ReferenceFrame<ZXZ, ExtrinsicRotation>(angles);
    result = frame_ZXZ_extrinsic.rotate_to(test_vector);
    answer = create_array(ZXZ_ROTATION_TO);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector to ZXZ extrinsic error");

    result = frame_XYZ_extrinsic.rotate_from(test_vector);
    answer = create_array(XYZ_ROTATION_FROM);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from XYZ extrinsic error");
    result = frame_XZY_extrinsic.rotate_from(test_vector);
    answer = create_array(XZY_ROTATION_FROM);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from XZY extrinsic error");
    result = frame_XYX_extrinsic.rotate_from(test_vector);
    answer = create_array(XYX_ROTATION_FROM);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from XYX extrinsic error");
    result = frame_ZXZ_extrinsic.rotate_from(test_vector);
    answer = create_array(ZXZ_ROTATION_FROM);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from ZXZ extrinsic error");

    frame_XYZ_extrinsic.set_offset(offset_vector);
    result = frame_XYZ_extrinsic.rotate_to(test_vector);
    answer = create_array(XYZ_ROTATION_OFFSET_TO);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector to offset XYZ extrinsic error");
    frame_XZY_extrinsic.set_offset(offset_vector);
    result = frame_XZY_extrinsic.rotate_to(test_vector);
    answer = create_array(XZY_ROTATION_OFFSET_TO);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector to offset XZY extrinsic error");
    frame_XYX_extrinsic.set_offset(offset_vector);
    result = frame_XYX_extrinsic.rotate_to(test_vector);
    answer = create_array(XYX_ROTATION_OFFSET_TO);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector to offset XYX extrinsic error");
    frame_ZXZ_extrinsic.set_offset(offset_vector);
    result = frame_ZXZ_extrinsic.rotate_to(test_vector);
    answer = create_array(ZXZ_ROTATION_OFFSET_TO);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector to offset ZXZ extrinsic error");
    
    result = frame_XYZ_extrinsic.rotate_from(test_vector);
    answer = create_array(XYZ_ROTATION_OFFSET_FROM);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset XYZ extrinsic error");
    result = frame_XZY_extrinsic.rotate_from(test_vector);
    answer = create_array(XZY_ROTATION_OFFSET_FROM);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset XZY extrinsic error");
    result = frame_XYX_extrinsic.rotate_from(test_vector);
    answer = create_array(XYX_ROTATION_OFFSET_FROM);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset XYX extrinsic error");
    result = frame_ZXZ_extrinsic.rotate_from(test_vector);
    answer = create_array(ZXZ_ROTATION_OFFSET_FROM);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset ZXZ extrinsic error");
}

TEST(ReferenceFrameUnitTest, TestBetweenFramesVectors) {
    EulerAngles angles_from = EulerAngles(EVSPACE_PI / 6, EVSPACE_PI_4, EVSPACE_PI / 3);
    EulerAngles angles_to = EulerAngles(0, EVSPACE_PI_4, EVSPACE_PI / 2);
    Vector result;
    VectorArray answer;
    const Vector offset_from = Vector(10, 20, 30);
    const Vector offset_to = Vector(100, 200, 300);
    const Vector test_vector = Vector(1, 2, 3);
    const Vector zero_vector = Vector(0, 0, 0);

    //  XYZ -> YXY
    auto frame_XYZ = ReferenceFrame<XYZ, IntrinsicRotation>(angles_from);
    auto frame_YXY = ReferenceFrame<YXY, IntrinsicRotation>(angles_to);
    result = frame_XYZ.rotate_to(frame_YXY, test_vector);
    answer = create_array(FROM_XYZ_TO_YXY_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from XYZ to YXY error");
    result = frame_XYZ.rotate_from(frame_YXY, result);
    _COMPARE_VECTOR_NEAR(result, test_vector, "rotate vector from YXY to XYZ error");
    frame_XYZ.set_offset(offset_from);
    result = frame_XYZ.rotate_to(frame_YXY, test_vector);
    answer = create_array(FROM_OFFSET_XYZ_TO_YXY_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset XYZ to YXY error");
    result = frame_XYZ.rotate_from(frame_YXY, result);
    _COMPARE_VECTOR_NEAR(result, test_vector, "rotate vector from YXY to offset XYZ error");
    frame_XYZ.set_offset(zero_vector);
    frame_YXY.set_offset(offset_to);
    result = frame_XYZ.rotate_to(frame_YXY, test_vector);
    answer = create_array(FROM_XYZ_TO_OFFSET_YXY_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from XYZ to offset YXY error");
    result = frame_XYZ.rotate_from(frame_YXY, result);
    _COMPARE_VECTOR_NEAR(result, test_vector, "rotate vector from offset YXY to XYZ error");
    frame_XYZ.set_offset(offset_from);
    result = frame_XYZ.rotate_to(frame_YXY, test_vector);
    answer = create_array(FROM_OFFSET_XYZ_TO_OFFSET_YXY_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset XYZ to offset YXY error");
    result = frame_XYZ.rotate_from(frame_YXY, result);
    _COMPARE_VECTOR_NEAR(result, test_vector, "rotate vector from offset YXY to offset XYZ error");

    //  XZY -> XYX
    auto frame_XZY = ReferenceFrame<XZY, IntrinsicRotation>(angles_from);
    auto frame_XYX = ReferenceFrame<XYX, IntrinsicRotation>(angles_to);
    result = frame_XZY.rotate_to(frame_XYX, test_vector);
    answer = create_array(FROM_XZY_TO_XYX_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from XZY to XYX error");
    result = frame_XZY.rotate_from(frame_XYX, result);
    _COMPARE_VECTOR_NEAR(result, test_vector, "rotate vector from XYX to XZY error");
    frame_XZY.set_offset(offset_from);
    result = frame_XZY.rotate_to(frame_XYX, test_vector);
    answer = create_array(FROM_OFFSET_XZY_TO_XYX_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset XZY to XYX error");
    result = frame_XZY.rotate_from(frame_XYX, result);
    _COMPARE_VECTOR_NEAR(result, test_vector, "rotate vector from XYX to offset XZY error");
    frame_XZY.set_offset(zero_vector);
    frame_XYX.set_offset(offset_to);
    result = frame_XZY.rotate_to(frame_XYX, test_vector);
    answer = create_array(FROM_XZY_TO_OFFSET_XYX_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from XZY to offset XYX error");
    result = frame_XZY.rotate_from(frame_XYX, result);
    _COMPARE_VECTOR_NEAR(result, test_vector, "rotate vector from offset XYX to XZY error");
    frame_XZY.set_offset(offset_from);
    result = frame_XZY.rotate_to(frame_XYX, test_vector);
    answer = create_array(FROM_OFFSET_XZY_TO_OFFSET_XYX_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset XZY to offset XYX error");
    result = frame_XZY.rotate_from(frame_XYX, result);
    _COMPARE_VECTOR_NEAR(result, test_vector, "rotate vector from offset XYX to offset XZY error");

    //  XYX -> ZYX
    frame_XYX = ReferenceFrame<XYX, IntrinsicRotation>(angles_from);
    auto frame_ZYX = ReferenceFrame<ZYX, IntrinsicRotation>(angles_to);
    result = frame_XYX.rotate_to(frame_ZYX, test_vector);
    answer = create_array(FROM_XYX_TO_ZYX_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from XYX to ZYX error");
    result = frame_XYX.rotate_from(frame_ZYX, result);
    _COMPARE_VECTOR_NEAR(result, test_vector, "rotate vector from ZYX to XYX error");
    frame_XYX.set_offset(offset_from);
    result = frame_XYX.rotate_to(frame_ZYX, test_vector);
    answer = create_array(FROM_OFFSET_XYX_TO_ZYX_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset XYX to ZYX error");
    result = frame_XYX.rotate_from(frame_ZYX, result);
    _COMPARE_VECTOR_NEAR(result, test_vector, "rotate vector from ZYX to offset XYX error");
    frame_XYX.set_offset(zero_vector);
    frame_ZYX.set_offset(offset_to);
    result = frame_XYX.rotate_to(frame_ZYX, test_vector);
    answer = create_array(FROM_XYX_TO_OFFSET_ZYX_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from XYX to offset ZYX error");
    result = frame_XYX.rotate_from(frame_ZYX, result);
    _COMPARE_VECTOR_NEAR(result, test_vector, "rotate vector from offset ZYX to XYX error");
    frame_XYX.set_offset(offset_from);
    result = frame_XYX.rotate_to(frame_ZYX, test_vector);
    answer = create_array(FROM_OFFSET_XYX_TO_OFFSET_ZYX_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset XYX to offset ZYX error");
    result = frame_XYX.rotate_from(frame_ZYX, result);
    _COMPARE_VECTOR_NEAR(result, test_vector, "rotate vector from offset ZYX to offset XYX error");

    //  ZXZ -> YZY
    auto frame_ZXZ = ReferenceFrame<ZXZ, IntrinsicRotation>(angles_from);
    auto frame_YZY = ReferenceFrame<YZY, IntrinsicRotation>(angles_to);
    result = frame_ZXZ.rotate_to(frame_YZY, test_vector);
    answer = create_array(FROM_ZXZ_TO_YZY_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from ZXZ to YZY error");
    result = frame_ZXZ.rotate_from(frame_YZY, result);
    _COMPARE_VECTOR_NEAR(result, test_vector, "rotate vector from YZY to ZXZ error");
    frame_ZXZ.set_offset(offset_from);
    result = frame_ZXZ.rotate_to(frame_YZY, test_vector);
    answer = create_array(FROM_OFFSET_ZXZ_TO_YZY_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset ZXZ to YZY error");
    result = frame_ZXZ.rotate_from(frame_YZY, result);
    _COMPARE_VECTOR_NEAR(result, test_vector, "rotate vector from YZY to offset ZXZ error");
    frame_ZXZ.set_offset(zero_vector);
    frame_YZY.set_offset(offset_to);
    result = frame_ZXZ.rotate_to(frame_YZY, test_vector);
    answer = create_array(FROM_ZXZ_TO_OFFSET_YZY_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from ZXZ to offset YZY error");
    result = frame_ZXZ.rotate_from(frame_YZY, result);
    _COMPARE_VECTOR_NEAR(result, test_vector, "rotate vector from offset YZY to ZXZ error");
    frame_ZXZ.set_offset(offset_from);
    result = frame_ZXZ.rotate_to(frame_YZY, test_vector);
    answer = create_array(FROM_OFFSET_ZXZ_TO_OFFSET_YZY_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset ZXZ to offset YZY error");
    result = frame_ZXZ.rotate_from(frame_YZY, result);
    _COMPARE_VECTOR_NEAR(result, test_vector, "rotate vector from offset YZY to offset ZXZ error");

    //  extrinsic tests (only the first reference frame will be extrinsic
    //  extrinsic ZYX -> YXY
    angles_from = EulerAngles(EVSPACE_PI / 3, EVSPACE_PI_4, EVSPACE_PI / 6);
    auto frame_XYZ_extrinsic = ReferenceFrame<ZYX, ExtrinsicRotation>(angles_from);
    frame_YXY = ReferenceFrame<YXY, IntrinsicRotation>(angles_to);
    result = frame_XYZ_extrinsic.rotate_to(frame_YXY, test_vector);
    answer = create_array(FROM_XYZ_TO_YXY_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from extrinsic XYZ to YXY error");
    result = frame_XYZ_extrinsic.rotate_from(frame_YXY, result);
    _COMPARE_VECTOR_NEAR(result, test_vector, "rotate vector from YXY to extrinsic XYZ error");
    frame_XYZ_extrinsic.set_offset(offset_from);
    result = frame_XYZ_extrinsic.rotate_to(frame_YXY, test_vector);
    answer = create_array(FROM_OFFSET_XYZ_TO_YXY_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset extrinsic XYZ to YXY error");
    result = frame_XYZ_extrinsic.rotate_from(frame_YXY, result);
    _COMPARE_VECTOR_NEAR(result, test_vector, "rotate vector from YXY to offset extrinsic XYZ error");
    frame_XYZ_extrinsic.set_offset(zero_vector);
    frame_YXY.set_offset(offset_to);
    result = frame_XYZ_extrinsic.rotate_to(frame_YXY, test_vector);
    answer = create_array(FROM_XYZ_TO_OFFSET_YXY_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from extrinsic XYZ to offset YXY error");
    result = frame_XYZ_extrinsic.rotate_from(frame_YXY, result);
    _COMPARE_VECTOR_NEAR(result, test_vector, "rotate vector from offset YXY to extrinsic XYZ error");
    frame_XYZ_extrinsic.set_offset(offset_from);
    result = frame_XYZ_extrinsic.rotate_to(frame_YXY, test_vector);
    answer = create_array(FROM_OFFSET_XYZ_TO_OFFSET_YXY_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset extrinsic XYZ to offset YXY error");
    result = frame_XYZ_extrinsic.rotate_from(frame_YXY, result);
    _COMPARE_VECTOR_NEAR(result, test_vector, "rotate vector from offset YXY to offset extrinsic XYZ error");

    //  extrinsic YZX -> XYX
    auto frame_XZY_extrinsic = ReferenceFrame<YZX, ExtrinsicRotation>(angles_from);
    frame_XYX = ReferenceFrame<XYX, IntrinsicRotation>(angles_to);
    result = frame_XZY_extrinsic.rotate_to(frame_XYX, test_vector);
    answer = create_array(FROM_XZY_TO_XYX_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from extrinsic XZY to XYX error");
    result = frame_XZY_extrinsic.rotate_from(frame_XYX, result);
    _COMPARE_VECTOR_NEAR(result, test_vector, "rotate vector from XYX to extrinsic XZY error");
    frame_XZY_extrinsic.set_offset(offset_from);
    result = frame_XZY_extrinsic.rotate_to(frame_XYX, test_vector);
    answer = create_array(FROM_OFFSET_XZY_TO_XYX_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset extrinsic XZY to XYX error");
    result = frame_XZY_extrinsic.rotate_from(frame_XYX, result);
    _COMPARE_VECTOR_NEAR(result, test_vector, "rotate vector from XYX to offset extrinsic XZY error");
    frame_XZY_extrinsic.set_offset(zero_vector);
    frame_XYX.set_offset(offset_to);
    result = frame_XZY_extrinsic.rotate_to(frame_XYX, test_vector);
    answer = create_array(FROM_XZY_TO_OFFSET_XYX_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from extrinsic XZY to offset XYX error");
    result = frame_XZY_extrinsic.rotate_from(frame_XYX, result);
    _COMPARE_VECTOR_NEAR(result, test_vector, "rotate vector from offset XYX to extrinsic XZY error");
    frame_XZY_extrinsic.set_offset(offset_from);
    result = frame_XZY_extrinsic.rotate_to(frame_XYX, test_vector);
    answer = create_array(FROM_OFFSET_XZY_TO_OFFSET_XYX_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset extrinsic XZY to offset XYX error");
    result = frame_XZY_extrinsic.rotate_from(frame_XYX, result);
    _COMPARE_VECTOR_NEAR(result, test_vector, "rotate vector from offset XYX to offset extrinsic XZY error");

    //  extrinsic XYX -> ZYX
    auto frame_XYX_extrinsic = ReferenceFrame<XYX, ExtrinsicRotation>(angles_from);
    frame_ZYX = ReferenceFrame<ZYX, IntrinsicRotation>(angles_to);
    result = frame_XYX_extrinsic.rotate_to(frame_ZYX, test_vector);
    answer = create_array(FROM_XYX_TO_ZYX_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from extrinsic XYX to ZYX error");
    result = frame_XYX_extrinsic.rotate_from(frame_ZYX, result);
    _COMPARE_VECTOR_NEAR(result, test_vector, "rotate vector from ZYX to extrinsic XYX error");
    frame_XYX_extrinsic.set_offset(offset_from);
    result = frame_XYX_extrinsic.rotate_to(frame_ZYX, test_vector);
    answer = create_array(FROM_OFFSET_XYX_TO_ZYX_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset extrinsic XYX to ZYX error");
    result = frame_XYX_extrinsic.rotate_from(frame_ZYX, result);
    _COMPARE_VECTOR_NEAR(result, test_vector, "rotate vector from ZYX to offset extrinsic XYX error");
    frame_XYX_extrinsic.set_offset(zero_vector);
    frame_ZYX.set_offset(offset_to);
    result = frame_XYX_extrinsic.rotate_to(frame_ZYX, test_vector);
    answer = create_array(FROM_XYX_TO_OFFSET_ZYX_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from extrinsic XYX to offset ZYX error");
    result = frame_XYX_extrinsic.rotate_from(frame_ZYX, result);
    _COMPARE_VECTOR_NEAR(result, test_vector, "rotate vector from offset ZYX to extrinsic XYX error");
    frame_XYX_extrinsic.set_offset(offset_from);
    result = frame_XYX_extrinsic.rotate_to(frame_ZYX, test_vector);
    answer = create_array(FROM_OFFSET_XYX_TO_OFFSET_ZYX_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset extrinsic XYX to offset ZYX error");
    result = frame_XYX_extrinsic.rotate_from(frame_ZYX, result);
    _COMPARE_VECTOR_NEAR(result, test_vector, "rotate vector from offset ZYX to offset extrinsic XYX error");

    //  extrinsic ZXZ -> YZY
    auto frame_ZXZ_extrinsic = ReferenceFrame<ZXZ, ExtrinsicRotation>(angles_from);
    frame_YZY = ReferenceFrame<YZY, IntrinsicRotation>(angles_to);
    result = frame_ZXZ_extrinsic.rotate_to(frame_YZY, test_vector);
    answer = create_array(FROM_ZXZ_TO_YZY_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from extrinsic ZXZ to YZY error");
    result = frame_ZXZ_extrinsic.rotate_from(frame_YZY, result);
    _COMPARE_VECTOR_NEAR(result, test_vector, "rotate vector from YZY to extrinsic ZXZ error");
    frame_ZXZ_extrinsic.set_offset(offset_from);
    result = frame_ZXZ_extrinsic.rotate_to(frame_YZY, test_vector);
    answer = create_array(FROM_OFFSET_ZXZ_TO_YZY_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset extrinsic ZXZ to YZY error");
    result = frame_ZXZ_extrinsic.rotate_from(frame_YZY, result);
    _COMPARE_VECTOR_NEAR(result, test_vector, "rotate vector from YZY to offset extrinsic ZXZ error");
    frame_ZXZ_extrinsic.set_offset(zero_vector);
    frame_YZY.set_offset(offset_to);
    result = frame_ZXZ_extrinsic.rotate_to(frame_YZY, test_vector);
    answer = create_array(FROM_ZXZ_TO_OFFSET_YZY_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from extrinsic ZXZ to offset YZY error");
    result = frame_ZXZ_extrinsic.rotate_from(frame_YZY, result);
    _COMPARE_VECTOR_NEAR(result, test_vector, "rotate vector from offset YZY to extrinsic ZXZ error");
    frame_ZXZ_extrinsic.set_offset(offset_from);
    result = frame_ZXZ_extrinsic.rotate_to(frame_YZY, test_vector);
    answer = create_array(FROM_OFFSET_ZXZ_TO_OFFSET_YZY_ROTATION);
    _COMPARE_VECTOR_NEAR(result, answer, "rotate vector from offset extrinsic ZXZ to offset YZY error");
    result = frame_ZXZ_extrinsic.rotate_from(frame_YZY, result);
    _COMPARE_VECTOR_NEAR(result, test_vector, "rotate vector from offset YZY to offset extrinsic ZXZ error");
}
