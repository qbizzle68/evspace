#ifndef _EVSPACE_ANGLES_H_
#define _EVSPACE_ANGLES_H_

#include <axis.hpp>
#include <evspace_common.hpp>
#include <cstddef>  // std::size_t

namespace evspace {

    template<typename _axis_1, typename _axis_2, typename _axis_3>
    struct RotationOrder {
        typedef _axis_1 Axis_1;
        typedef _axis_2 Axis_2;
        typedef _axis_3 Axis_3;
    };

    // improper rotations
    typedef RotationOrder<XAxis, YAxis, ZAxis> XYZ;
    typedef RotationOrder<XAxis, ZAxis, YAxis> XZY;
    typedef RotationOrder<YAxis, XAxis, ZAxis> YXZ;
    typedef RotationOrder<YAxis, ZAxis, XAxis> YZX;
    typedef RotationOrder<ZAxis, XAxis, YAxis> ZXY;
    typedef RotationOrder<ZAxis, YAxis, XAxis> ZYX;

    // proper rotations
    typedef RotationOrder<XAxis, YAxis, XAxis> XYX;
    typedef RotationOrder<XAxis, ZAxis, XAxis> XZX;
    typedef RotationOrder<YAxis, XAxis, YAxis> YXY;
    typedef RotationOrder<YAxis, ZAxis, YAxis> YZY;
    typedef RotationOrder<ZAxis, XAxis, ZAxis> ZXZ;
    typedef RotationOrder<ZAxis, YAxis, ZAxis> ZYZ;

    class EVSPACE_API EulerAngles {
    private:
        double m_values[3];

    public:
        EulerAngles();
        EulerAngles(double, double, double);
        EulerAngles(const EulerAngles&);

        double& operator[](std::size_t);
        const double& operator[](std::size_t) const;
    };

}

#endif // _EVSPACE_ANGLES_H_