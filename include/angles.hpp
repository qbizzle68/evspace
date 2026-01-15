#ifndef _EVSPACE_ANGLES_H_
#define _EVSPACE_ANGLES_H_

#include <axis.hpp>
#include <cstddef>      // std::size_t
#include <stdexcept>    // std::out_of_range

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

    class EulerAngles {
    private:
        double m_values[3];

    public:
        constexpr EulerAngles() noexcept;
        constexpr EulerAngles(double, double, double) noexcept;
        constexpr EulerAngles(const EulerAngles&) noexcept;

        EulerAngles& operator=(const EulerAngles&) = default;

        double& operator[](std::size_t);
        const double& operator[](std::size_t) const;
    };

    inline constexpr
    EulerAngles::EulerAngles() noexcept : m_values{ 0.0, 0.0, 0.0 } { }

    inline constexpr
    EulerAngles::EulerAngles(double alpha, double beta, double gamma) noexcept
        : m_values{ alpha, beta, gamma } { }
    
    inline constexpr
    EulerAngles::EulerAngles(const EulerAngles& cpy) noexcept
        : m_values{ cpy.m_values[0], cpy.m_values[1], cpy.m_values[2] } { }

    inline double& EulerAngles::EulerAngles::operator[](std::size_t index) {
        if (index > 2) {
            throw std::out_of_range("Angle index out of range");
        }

        return this->m_values[index];
    }

    inline const double&
    EulerAngles::EulerAngles::operator[](std::size_t index) const {
        if (index > 2) {
            throw std::out_of_range("Angle index out of range");
        }

        return this->m_values[index];
    }
}

#endif // _EVSPACE_ANGLES_H_
