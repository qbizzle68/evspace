/**
* Test files are built using cmake precompiled headers which are made
* visible to this file when building tests and are not explicitly
* included.
* 
*/

#include <axis.hpp>
#include <angles.hpp>

using namespace evspace;

TEST(AxisUnitTest, TestDirection) {
    EXPECT_EQ(XAxis::direction, AxisDirection::X) << "X-axis typedef invalid enum direction value";
    EXPECT_EQ(YAxis::direction, AxisDirection::Y) << "Y-axis typedef invalid enum direction value";
    EXPECT_EQ(ZAxis::direction, AxisDirection::Z) << "Z-axis typedef invalid enum direction value";

    EXPECT_NE(XAxis::direction, AxisDirection::Z) << "X-axis direction incorrectly equal to invalid direction";
}

TEST(AnglesUnitTest, TestRotationOrderTypedefs) {
    typedef RotationOrder<XAxis, YAxis, ZAxis> TestAxis;
    EXPECT_EQ(TestAxis::Axis_1::direction, AxisDirection::X) << "First axis(x) typedef direction incorrect";
    EXPECT_EQ(TestAxis::Axis_2::direction, AxisDirection::Y) << "Second axis(y) typedef direction incorrect";
    EXPECT_EQ(TestAxis::Axis_3::direction, AxisDirection::Z) << "Third axis(z) typedef direction incorrect";
}

TEST(AnglesUnitTest, TestGlobalOrders) {
    // hard-coding here ensures that if we make changes to code we still have all 12 rotation
    // orders validated, and we shouldn't run into the problem of only 1 is broken and we can't find the problem

    EXPECT_EQ(XYZ::Axis_1::direction, XAxis::direction) << "XYZ first axis invalid axis type";
    EXPECT_EQ(XYZ::Axis_2::direction, YAxis::direction) << "XYZ second axis invalid axis type";
    EXPECT_EQ(XYZ::Axis_3::direction, ZAxis::direction) << "XYZ third axis invalid axis type";
    EXPECT_EQ(XZY::Axis_1::direction, XAxis::direction) << "XZY axis first invalid axis type";
    EXPECT_EQ(XZY::Axis_2::direction, ZAxis::direction) << "XZY axis second invalid axis type";
    EXPECT_EQ(XZY::Axis_3::direction, YAxis::direction) << "XZY axis third invalid axis type";
    EXPECT_EQ(YXZ::Axis_1::direction, YAxis::direction) << "YXZ axis first invalid axis type";
    EXPECT_EQ(YXZ::Axis_2::direction, XAxis::direction) << "YXZ axis second invalid axis type";
    EXPECT_EQ(YXZ::Axis_3::direction, ZAxis::direction) << "YXZ axis third invalid axis type";
    EXPECT_EQ(YZX::Axis_1::direction, YAxis::direction) << "YZX axis first invalid axis type";
    EXPECT_EQ(YZX::Axis_2::direction, ZAxis::direction) << "YZX axis second invalid axis type";
    EXPECT_EQ(YZX::Axis_3::direction, XAxis::direction) << "YZX axis third invalid axis type";
    EXPECT_EQ(ZXY::Axis_1::direction, ZAxis::direction) << "ZXY axis first invalid axis type";
    EXPECT_EQ(ZXY::Axis_2::direction, XAxis::direction) << "ZXY axis second invalid axis type";
    EXPECT_EQ(ZXY::Axis_3::direction, YAxis::direction) << "ZXY axis third invalid axis type";
    EXPECT_EQ(ZYX::Axis_1::direction, ZAxis::direction) << "ZYX axis first invalid axis type";
    EXPECT_EQ(ZYX::Axis_2::direction, YAxis::direction) << "ZYX axis second invalid axis type";
    EXPECT_EQ(ZYX::Axis_3::direction, XAxis::direction) << "ZYX axis third invalid axis type";
    EXPECT_EQ(XYX::Axis_1::direction, XAxis::direction) << "XYX axis first invalid axis type";
    EXPECT_EQ(XYX::Axis_2::direction, YAxis::direction) << "XYX axis second invalid axis type";
    EXPECT_EQ(XYX::Axis_3::direction, XAxis::direction) << "XYX axis third invalid axis type";
    EXPECT_EQ(XZX::Axis_1::direction, XAxis::direction) << "XZX axis first invalid axis type";
    EXPECT_EQ(XZX::Axis_2::direction, ZAxis::direction) << "XZX axis second invalid axis type";
    EXPECT_EQ(XZX::Axis_3::direction, XAxis::direction) << "XZX axis third invalid axis type";
    EXPECT_EQ(YXY::Axis_1::direction, YAxis::direction) << "YXY axis first invalid axis type";
    EXPECT_EQ(YXY::Axis_2::direction, XAxis::direction) << "YXY axis second invalid axis type";
    EXPECT_EQ(YXY::Axis_3::direction, YAxis::direction) << "YXY axis third invalid axis type";
    EXPECT_EQ(YZY::Axis_1::direction, YAxis::direction) << "YZY axis first invalid axis type";
    EXPECT_EQ(YZY::Axis_2::direction, ZAxis::direction) << "YZY axis second invalid axis type";
    EXPECT_EQ(YZY::Axis_3::direction, YAxis::direction) << "YZY axis third invalid axis type";
    EXPECT_EQ(ZXZ::Axis_1::direction, ZAxis::direction) << "ZXZ axis first invalid axis type";
    EXPECT_EQ(ZXZ::Axis_2::direction, XAxis::direction) << "ZXZ axis second invalid axis type";
    EXPECT_EQ(ZXZ::Axis_3::direction, ZAxis::direction) << "ZXZ axis third invalid axis type";
    EXPECT_EQ(ZYZ::Axis_1::direction, ZAxis::direction) << "ZYZ axis first invalid axis type";
    EXPECT_EQ(ZYZ::Axis_2::direction, YAxis::direction) << "ZYZ axis second invalid axis type";
    EXPECT_EQ(ZYZ::Axis_3::direction, ZAxis::direction) << "ZYZ axis third invalid axis type";
}

TEST(AnglesUnitTest, TestDefaultConstruction) {
    const EulerAngles angles = EulerAngles();

    EXPECT_EQ(angles[0], 0.0) << "Default Euler angles alpha value should be zero";
    EXPECT_EQ(angles[1], 0.0) << "Default Euler angles beta value should be zero";
    EXPECT_EQ(angles[1], 0.0) << "Default Euler angles gamma value should be zero";
}

TEST(AnglesUnitTest, TestAngleConstructor) {
    const EulerAngles angles = EulerAngles(10, 20.5, 33);

    EXPECT_EQ(angles[0], 10.0) << "EulerAngles constructor alpha angle invalid";
    EXPECT_EQ(angles[1], 20.5) << "EulerAngles constructor beta angle invalid";
    EXPECT_EQ(angles[2], 33.0) << "EulerAngles constructor gamma angle invalid";
}

TEST(AnglesUnitTest, TestAngleCopyConstructor) {
    const EulerAngles angles = EulerAngles(1, 2, 3);
    const EulerAngles angles_copy = EulerAngles(angles);

    EXPECT_EQ(angles_copy[0], 1.0) << "EulerAngles copy constructor alpha angle invalid";
    EXPECT_EQ(angles_copy[1], 2.0) << "EulerAngles copy constructor beta angle invalid";
    EXPECT_EQ(angles_copy[2], 3.0) << "EulerAngles copy constructor gamma angle invalid";
}
