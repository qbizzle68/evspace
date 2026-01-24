/**
* Test files are built using cmake precompiled headers which are made
* visible to this file when building tests and are not explicitly
* included.
* 
*/

#include <axis.hpp>
#include <angles.hpp>
#include <gtest/gtest.h>

namespace evs = evspace;

TEST(AxisUnitTest, TestDirection) {
    EXPECT_EQ(evs::XAxis::direction, evs::AxisDirection::X) << "X-axis typedef invalid enum direction value";
    EXPECT_EQ(evs::YAxis::direction, evs::AxisDirection::Y) << "Y-axis typedef invalid enum direction value";
    EXPECT_EQ(evs::ZAxis::direction, evs::AxisDirection::Z) << "Z-axis typedef invalid enum direction value";

    EXPECT_NE(evs::XAxis::direction, evs::AxisDirection::Z) << "X-axis direction incorrectly equal to invalid direction";
}

TEST(AnglesUnitTest, TestRotationOrderTypedefs) {
    typedef evs::RotationOrder<evs::XAxis, evs::YAxis, evs::ZAxis> TestAxis;
    EXPECT_EQ(TestAxis::Axis_1::direction, evs::AxisDirection::X) << "First axis(x) typedef direction incorrect";
    EXPECT_EQ(TestAxis::Axis_2::direction, evs::AxisDirection::Y) << "Second axis(y) typedef direction incorrect";
    EXPECT_EQ(TestAxis::Axis_3::direction, evs::AxisDirection::Z) << "Third axis(z) typedef direction incorrect";
}

TEST(AnglesUnitTest, TestGlobalOrders) {
    // hard-coding here ensures that if we make changes to code we still have all 12 rotation
    // orders validated, and we shouldn't run into the problem of only 1 is broken and we can't find the problem

    EXPECT_EQ(evs::XYZ::Axis_1::direction, evs::XAxis::direction) << "XYZ first axis invalid axis type";
    EXPECT_EQ(evs::XYZ::Axis_2::direction, evs::YAxis::direction) << "XYZ second axis invalid axis type";
    EXPECT_EQ(evs::XYZ::Axis_3::direction, evs::ZAxis::direction) << "XYZ third axis invalid axis type";
    EXPECT_EQ(evs::XZY::Axis_1::direction, evs::XAxis::direction) << "XZY axis first invalid axis type";
    EXPECT_EQ(evs::XZY::Axis_2::direction, evs::ZAxis::direction) << "XZY axis second invalid axis type";
    EXPECT_EQ(evs::XZY::Axis_3::direction, evs::YAxis::direction) << "XZY axis third invalid axis type";
    EXPECT_EQ(evs::YXZ::Axis_1::direction, evs::YAxis::direction) << "YXZ axis first invalid axis type";
    EXPECT_EQ(evs::YXZ::Axis_2::direction, evs::XAxis::direction) << "YXZ axis second invalid axis type";
    EXPECT_EQ(evs::YXZ::Axis_3::direction, evs::ZAxis::direction) << "YXZ axis third invalid axis type";
    EXPECT_EQ(evs::YZX::Axis_1::direction, evs::YAxis::direction) << "YZX axis first invalid axis type";
    EXPECT_EQ(evs::YZX::Axis_2::direction, evs::ZAxis::direction) << "YZX axis second invalid axis type";
    EXPECT_EQ(evs::YZX::Axis_3::direction, evs::XAxis::direction) << "YZX axis third invalid axis type";
    EXPECT_EQ(evs::ZXY::Axis_1::direction, evs::ZAxis::direction) << "ZXY axis first invalid axis type";
    EXPECT_EQ(evs::ZXY::Axis_2::direction, evs::XAxis::direction) << "ZXY axis second invalid axis type";
    EXPECT_EQ(evs::ZXY::Axis_3::direction, evs::YAxis::direction) << "ZXY axis third invalid axis type";
    EXPECT_EQ(evs::ZYX::Axis_1::direction, evs::ZAxis::direction) << "ZYX axis first invalid axis type";
    EXPECT_EQ(evs::ZYX::Axis_2::direction, evs::YAxis::direction) << "ZYX axis second invalid axis type";
    EXPECT_EQ(evs::ZYX::Axis_3::direction, evs::XAxis::direction) << "ZYX axis third invalid axis type";
    EXPECT_EQ(evs::XYX::Axis_1::direction, evs::XAxis::direction) << "XYX axis first invalid axis type";
    EXPECT_EQ(evs::XYX::Axis_2::direction, evs::YAxis::direction) << "XYX axis second invalid axis type";
    EXPECT_EQ(evs::XYX::Axis_3::direction, evs::XAxis::direction) << "XYX axis third invalid axis type";
    EXPECT_EQ(evs::XZX::Axis_1::direction, evs::XAxis::direction) << "XZX axis first invalid axis type";
    EXPECT_EQ(evs::XZX::Axis_2::direction, evs::ZAxis::direction) << "XZX axis second invalid axis type";
    EXPECT_EQ(evs::XZX::Axis_3::direction, evs::XAxis::direction) << "XZX axis third invalid axis type";
    EXPECT_EQ(evs::YXY::Axis_1::direction, evs::YAxis::direction) << "YXY axis first invalid axis type";
    EXPECT_EQ(evs::YXY::Axis_2::direction, evs::XAxis::direction) << "YXY axis second invalid axis type";
    EXPECT_EQ(evs::YXY::Axis_3::direction, evs::YAxis::direction) << "YXY axis third invalid axis type";
    EXPECT_EQ(evs::YZY::Axis_1::direction, evs::YAxis::direction) << "YZY axis first invalid axis type";
    EXPECT_EQ(evs::YZY::Axis_2::direction, evs::ZAxis::direction) << "YZY axis second invalid axis type";
    EXPECT_EQ(evs::YZY::Axis_3::direction, evs::YAxis::direction) << "YZY axis third invalid axis type";
    EXPECT_EQ(evs::ZXZ::Axis_1::direction, evs::ZAxis::direction) << "ZXZ axis first invalid axis type";
    EXPECT_EQ(evs::ZXZ::Axis_2::direction, evs::XAxis::direction) << "ZXZ axis second invalid axis type";
    EXPECT_EQ(evs::ZXZ::Axis_3::direction, evs::ZAxis::direction) << "ZXZ axis third invalid axis type";
    EXPECT_EQ(evs::ZYZ::Axis_1::direction, evs::ZAxis::direction) << "ZYZ axis first invalid axis type";
    EXPECT_EQ(evs::ZYZ::Axis_2::direction, evs::YAxis::direction) << "ZYZ axis second invalid axis type";
    EXPECT_EQ(evs::ZYZ::Axis_3::direction, evs::ZAxis::direction) << "ZYZ axis third invalid axis type";
}

TEST(AnglesUnitTest, TestDefaultConstruction) {
    const evs::EulerAngles angles = evs::EulerAngles();

    EXPECT_EQ(angles[0], 0.0) << "Default Euler angles alpha value should be zero";
    EXPECT_EQ(angles[1], 0.0) << "Default Euler angles beta value should be zero";
    EXPECT_EQ(angles[1], 0.0) << "Default Euler angles gamma value should be zero";
}

TEST(AnglesUnitTest, TestAngleConstructor) {
    const evs::EulerAngles angles = evs::EulerAngles(10, 20.5, 33);

    EXPECT_EQ(angles[0], 10.0) << "EulerAngles constructor alpha angle invalid";
    EXPECT_EQ(angles[1], 20.5) << "EulerAngles constructor beta angle invalid";
    EXPECT_EQ(angles[2], 33.0) << "EulerAngles constructor gamma angle invalid";
}

TEST(AnglesUnitTest, TestAngleCopyConstructor) {
    const evs::EulerAngles angles = evs::EulerAngles(1, 2, 3);
    const evs::EulerAngles angles_copy = evs::EulerAngles(angles);

    EXPECT_EQ(angles_copy[0], 1.0) << "EulerAngles copy constructor alpha angle invalid";
    EXPECT_EQ(angles_copy[1], 2.0) << "EulerAngles copy constructor beta angle invalid";
    EXPECT_EQ(angles_copy[2], 3.0) << "EulerAngles copy constructor gamma angle invalid";
}
