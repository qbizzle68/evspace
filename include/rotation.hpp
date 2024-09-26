#ifndef _EVSPACE_ROTATION_H_
#define _EVSPACE_ROTATION_H_

#include <angles.hpp>
#include <matrix.hpp>
#include <vector.hpp>
#include <cstddef>      // std::size_t
#include <stdexcept>    // std::out_of_range

#ifndef EVSPACE_ANGLE_CONVERSIONS
#define EVSPACE_ANGLE_CONVERSIONS

#define EVSPACE_PI          3.14159265358979323846
#define RADIAN_TO_DEGREE    (180.0 / EVSPACE_PI)
#define DEGREE_TO_RADIAN    (EVSPACE_PI / 180.0)

#endif // EVSPACE_ANGLE_CONVERSIONS

namespace evspace {

    /**
     * Forward declarations for delegate classes.
     */
    template<typename rotation_order, typename rotation_type>
    struct _EulerAngleDelegate {
        static inline Matrix derive_matrix(double, double, double);
    };

    template<typename _axis>
    struct _SingleAxisDelegate {
        static inline Matrix derive_matrix(double);
    };

    /**
     * Rotation types to distinguish intrinsic vs extrensic.
     */
    struct RotationType { };
    struct IntrinsicRotation : RotationType { };
    struct ExtrensicRotation : RotationType { };

    // Internal variable for fuction default
    const Vector _zero_vector = Vector(0.0, 0.0, 0.0);

    template<typename _rotation_order, typename _rotation_type>
    class ReferenceFrame {
    private:
        EulerAngles m_angles;
        Vector m_offset;
        Matrix m_matrix;

        void update_matrix();

    public:
        ReferenceFrame() = delete;
        ReferenceFrame(const EulerAngles&, const Vector & = _zero_vector);

        double& operator[](std::size_t);
        const double& operator[](std::size_t) const;

        const EulerAngles& get_angles() const;
        const Vector& get_offset() const;
        const Matrix& get_matrix() const;
        void set_angles(const EulerAngles&);
        void set_offset(const Vector&);

        Vector rotate_to(const Vector&) const;
        template<typename param_order, typename param_type>
        Vector rotate_to(const ReferenceFrame<param_order, param_type>&, const Vector&) const;
        Vector rotate_from(const Vector&) const;
        template<typename param_order, typename param_type>
        Vector rotate_fro(const ReferenceFrame<param_order, param_type>&, const Vector&) const;

        typedef rotation_order  RotationOrder;
        typedef rotation_type   RotationType;
    };

}

#endif // _EVSPACE_ROTATION_H_