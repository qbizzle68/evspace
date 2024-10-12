#ifndef _EVSPACE_ROTATION_H_
#define _EVSPACE_ROTATION_H_

#include <angles.hpp>
#include <matrix.hpp>
#include <vector.hpp>
#include <evspace_common.hpp>
#include <cstddef>      // std::size_t
#include <stdexcept>    // std::out_of_range
#include <cmath>        // std::cos, std::sin

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
    struct ExtrinsicRotation : RotationType { };

    // Internal variable for fuction default
    const Vector _zero_vector = Vector(0.0, 0.0, 0.0);

    template<typename _rotation_order, typename _rotation_type=IntrinsicRotation>
    class ReferenceFrame {
    private:
        EulerAngles m_angles;
        Vector m_offset;
        Matrix m_matrix;

        void update_matrix();

    public:
        ReferenceFrame() = delete;
        ReferenceFrame(const EulerAngles&, const Vector & = _zero_vector);

        //double& operator[](std::size_t);
        const double& operator[](std::size_t) const;

        const EulerAngles& get_angles() const;
        const Vector& get_offset() const;
        const Matrix& get_matrix() const;
        void set_angles(std::size_t, double);
        void set_angles(const EulerAngles&);
        void set_offset(const Vector&);

        Vector rotate_to(const Vector&) const;
        template<typename param_order, typename param_type>
        Vector rotate_to(const ReferenceFrame<param_order, param_type>&, const Vector&) const;
        Vector rotate_from(const Vector&) const;
        template<typename param_order, typename param_type>
        Vector rotate_from(const ReferenceFrame<param_order, param_type>&, const Vector&) const;

        typedef _rotation_order  RotationOrder;
        typedef _rotation_type   RotationType;
    };

    /**
     * Rotation matrix computation function declarations.
     */

    template<typename axis>
    Matrix compute_rotation_matrix(double);

    EVSPACE_API Matrix compute_rotation_matrix(double angle, const Vector&);

    template<typename rotation_order, typename rotation_type = IntrinsicRotation>
    Matrix compute_rotation_matrix(const EulerAngles&);

    template<typename rotation_from, typename rotation_to, typename from_type = IntrinsicRotation, typename to_type = IntrinsicRotation>
    Matrix compute_rotation_matrix(const EulerAngles& angles_from, const EulerAngles& angles_to);

    /**
     * Rotation function declarations.
     */

    namespace _rotation_exec {

    /**
     *  Rotation function definitions.
     *
     *  VECTOR ROTATIONS:
     *
     *  Vector rotation from an inert reference frame to a rotated reference frame
     *  represented by a rotation matrix is done by multiplying the vector on the
     *  left-hand side by the rotation matrix. For example if v and m are the vector
     *  and matrix respectively, the rotated vector is equal to (m * v). If the
     *  reference frame's origin is offset from the inertial reference frame, the
     *  vector should be subtracted by the offset vector before multiplying. In
     *  this case, the offset vector's basis should be the inert vector space's
     *  basis. If the offset vector is o, rotating to the offset rotated reference
     *  frame would be done by ((v - o) * m). The functions that handle this case
     *  are labeled as rotate_to, as they rotate vectors to rotated reference frames.
     *
     *  Vector rotation from a rotated reference frame to an inter frame is done by
     *  multiplying the rotated vector on the right-hand side by the rotation matrix,
     *  (v * m). On offset reference frame can be rotated from by rotating the vector
     *  to the inert frame, then adding the offset vector. The vector should be a
     *  vector from the inertial reference frame. The computation looks like:
     *  ((m * v) + o). The functions that handle this case are lebeled as rotate_from,
     *  as they rotate vectors from rotated reference frames.
     *
     *  In all examples, the order of matrix and vector in multiplications can be
     *  reversed if the transpose of the matrix is used. This is apparent when you
     *  realize the inverse of a pure rotation matrix (which exists since it's
     *  determinate is always 1, and is equal to it's transpose) just represents
     *  a rotation in the opposite direction. For example is m represents the
     *  rotation matrix from reference frames a -> b, then the transpose of the
     *  matrix m is the rotation from b -> a. Then you switch from 'rotating to',
     *  to 'rotating from', or vis-versa.
     *
     *  Rotating between rotated reference frames just involves first rotating to an
     *  inertial reference frame first, then to the target reference frame. Offset
     *  frames are treated the same in the intermediate steps.
     */

        EVSPACE_API inline Vector _rotate_from_exec(const Matrix& matrix, const Vector& vector) {
            return matrix * vector;
        }

        EVSPACE_API inline Vector _rotate_to_exec(const Matrix& matrix, const Vector& vector) {
            return vector * matrix;
        }

        EVSPACE_API inline Vector _rotate_from_exec(const Matrix& matrix, const Vector& vector, const Vector& offset) {
            return (matrix * vector) + offset;
        }

        EVSPACE_API inline Vector _rotate_to_exec(const Matrix& matrix, const Vector& vector, const Vector& offset) {
            return (vector - offset) * matrix;
        }

    }

    EVSPACE_API Vector rotate_from(const Matrix&, const Vector&);
    EVSPACE_API Vector rotate_from(const Matrix&, const Vector&, const Vector&);
    EVSPACE_API Vector rotate_to(const Matrix&, const Vector&);
    EVSPACE_API Vector rotate_to(const Matrix&, const Vector&, const Vector&);

    template<typename axis>
    Vector rotate_from(double, const Vector&);
    template<typename axis>
    Vector rotate_from(double, const Vector&, const Vector&);
    template<typename axis>
    Vector rotate_to(double, const Vector&);
    template<typename axis>
    Vector rotate_to(double, const Vector&, const Vector&);

    template<typename rotation_order, typename rotation_type = IntrinsicRotation>
    Vector rotate_from(const EulerAngles&, const Vector&);
    template<typename rotation_order, typename rotation_type = IntrinsicRotation>
    Vector rotate_from(const EulerAngles&, const Vector&, const Vector&);
    template<typename rotation_order, typename rotation_type = IntrinsicRotation>
    Vector rotate_to(const EulerAngles&, const Vector&);
    template<typename rotation_order, typename rotation_type = IntrinsicRotation>
    Vector rotate_to(const EulerAngles&, const Vector&, const Vector&);

    template<typename rotation_from, typename rotation_to, typename from_type = IntrinsicRotation, typename to_type = IntrinsicRotation>
    Vector rotate_between(const EulerAngles&, const EulerAngles&, const Vector&, const Vector & = _zero_vector, const Vector & = _zero_vector);

    /**
     * Template specialization of single axis rotation delegate classes.
     * These are the bread and butter of the rotation part of the library.
     */

    template<>
    struct _SingleAxisDelegate<XAxis> {
        static inline Matrix derive_matrix(double angle) {
            double cos_angle = std::cos(angle);
            double sin_angle = std::sin(angle);

            return Matrix(
                {
                    { 1.0, 0.0, 0.0 },
                    { 0.0, cos_angle, -sin_angle },
                    { 0.0, sin_angle, cos_angle }
                }
            );
        }
    };

    template<>
    struct _SingleAxisDelegate<YAxis> {
        static inline Matrix derive_matrix(double angle) {
            double cos_angle = std::cos(angle);
            double sin_angle = std::sin(angle);

            return Matrix(
                {
                    { cos_angle, 0.0, sin_angle },
                    { 0.0, 1.0, 0.0 },
                    { -sin_angle, 0.0, cos_angle }
                }
            );
        }
    };

    template<>
    struct _SingleAxisDelegate<ZAxis> {

        static inline Matrix derive_matrix(double angle) {
            double cos_angle = std::cos(angle);
            double sin_angle = std::sin(angle);

            return Matrix(
                {
                    { cos_angle, -sin_angle, 0.0 },
                    { sin_angle, cos_angle, 0.0 },
                    { 0.0, 0.0, 1.0 }
                }
            );
        }

    };

    /**
     * Template specialization of Euler rotation delegate class.
     */

    template<typename axis1, typename axis2, typename axis3>
    struct _EulerAngleDelegate<RotationOrder<axis1, axis2, axis3>, IntrinsicRotation> {

        static inline Matrix derive_matrix(double alpha, double beta, double gamma) {
            return _SingleAxisDelegate<axis1>::derive_matrix(alpha)
                * _SingleAxisDelegate<axis2>::derive_matrix(beta)
                * _SingleAxisDelegate<axis3>::derive_matrix(gamma);
        }

    };

    template<typename axis1, typename axis2, typename axis3>
    struct _EulerAngleDelegate<RotationOrder<axis1, axis2, axis3>, ExtrinsicRotation> {

        static inline Matrix derive_matrix(double alpha, double beta, double gamma) {
            return _SingleAxisDelegate<axis3>::derive_matrix(gamma)
                * _SingleAxisDelegate<axis2>::derive_matrix(beta)
                * _SingleAxisDelegate<axis1>::derive_matrix(alpha);
        }

    };

    /**
     * ReferenceFrame implementations.
     */

    template<typename rotation_order, typename rotation_type>
    ReferenceFrame<rotation_order, rotation_type>::ReferenceFrame(const EulerAngles& angles, const Vector& offset)
        : m_angles(angles), m_offset(offset)
    {
        this->update_matrix();
    }

    template<typename rotation_order, typename rotation_type>
    const EulerAngles& ReferenceFrame<rotation_order, rotation_type>::get_angles() const {
        return this->m_angles;
    }

    template<typename rotation_order, typename rotation_type>
    const Vector& ReferenceFrame<rotation_order, rotation_type>::get_offset() const {
        return this->m_offset;
    }

    template<typename rotation_order, typename rotation_type>
    const Matrix& ReferenceFrame<rotation_order, rotation_type>::get_matrix() const {
        return this->m_matrix;
    }

    template<typename rotation_order, typename rotation_type>
    void ReferenceFrame<rotation_order, rotation_type>::set_angles(std::size_t index, double value) {
        this->m_angles[index] = value;
        this->update_matrix();
    }

    template<typename rotation_order, typename rotation_type>
    void ReferenceFrame<rotation_order, rotation_type>::set_angles(const EulerAngles& angles) {
        this->m_angles = angles;
        this->update_matrix();
    }

    template<typename rotation_order, typename rotation_type>
    void ReferenceFrame<rotation_order, rotation_type>::set_offset(const Vector& offset) {
        this->m_offset = offset;
        this->update_matrix();
    }

    template<typename rotation_order, typename rotation_type>
    void ReferenceFrame<rotation_order, rotation_type>::update_matrix() {
        this->m_matrix = _EulerAngleDelegate<rotation_order, rotation_type>::derive_matrix(
            this->m_angles[0],
            this->m_angles[1],
            this->m_angles[2]
        );
    }

    template<typename rotation_order, typename rotation_type>
    const double& ReferenceFrame<rotation_order, rotation_type>::operator[](std::size_t index) const {
        if (index > 2) {
            throw std::out_of_range("Index out of bounds.");
        }

        return this->m_angles[index];
    }

    template<typename rotation_order, typename rotation_type>
    Vector ReferenceFrame<rotation_order, rotation_type>::rotate_from(const Vector& vector) const {
        return _rotation_exec::_rotate_from_exec(this->m_matrix, vector, this->m_offset);
    }

    template<typename rotation_order, typename rotation_type>
    Vector ReferenceFrame<rotation_order, rotation_type>::rotate_to(const Vector& vector) const {
        return _rotation_exec::_rotate_to_exec(this->m_matrix, vector, this->m_offset);
    }

    template<typename rotation_order, typename rotation_type>
    template<typename _o, typename _t>
    Vector ReferenceFrame<rotation_order, rotation_type>::rotate_to(const ReferenceFrame<_o, _t>& frame, const Vector& vector) const {
        Vector inert_vector = _rotation_exec::_rotate_from_exec(this->m_matrix, vector, this->m_offset);

        return _rotation_exec::_rotate_to_exec(frame.get_matrix(), inert_vector, frame.get_offset());
    }

    template<typename rotation_order, typename rotation_type>
    template<typename _o, typename _t>
    Vector ReferenceFrame<rotation_order, rotation_type>::rotate_from(const ReferenceFrame<_o, _t>& frame, const Vector& vector) const {
        Vector inert_vector = _rotation_exec::_rotate_from_exec(frame.get_matrix(), vector, frame.get_offset());

        return _rotation_exec::_rotate_to_exec(this->m_matrix, inert_vector, this->m_offset);
    }

    /**
     * Implementation overloads of create_rotation_matrix functions.
     */

    template<typename axis>
    Matrix compute_rotation_matrix(double angle) {
        return _SingleAxisDelegate<axis>::derive_matrix(angle);
    }

    template<typename rotation_order, typename rotation_type>
    Matrix compute_rotation_matrix(const EulerAngles& angles) {
        return _EulerAngleDelegate<rotation_order, rotation_type>::derive_matrix(
            angles[0],
            angles[1],
            angles[2]
        );
    }

    /**
     * This resulting matrix should multiply a vector from the 'from' reference frame on the
     * left-hand side to rotate it to the 'to' frame.
     */

    template<typename rotation_from, typename rotation_to, typename from_type, typename to_type>
    Matrix compute_rotation_matrix(const EulerAngles& angles_from, const EulerAngles& angles_to) {
        /**
         * as of this writing (2024/01/02) this is wrong in pyevspace. the possible ways of doing
         * this are vector * (transpose(matrixFrom) * matrixTo)
         * or transpose(matrixTo) * matrixFrom * vector
         * since multiplying like vector * matrix usually sends a vector TO the reference frame,
         * we should want consistancy in that, so we should use the first form
         */
        return _EulerAngleDelegate<rotation_from, from_type>::derive_matrix(angles_from[0], angles_from[1], angles_from[2]).transpose()
            * _EulerAngleDelegate<rotation_to, to_type>::derive_matrix(angles_to[0], angles_to[1], angles_to[2]);
    }

    template<typename axis>
    Vector rotate_from(double angle, const Vector& vector) {
        Matrix rotation_matrix = compute_rotation_matrix<axis>(angle);

        return _rotation_exec::_rotate_from_exec(rotation_matrix, vector);
    }

    template<typename axis>
    Vector rotate_from(double angle, const Vector& vector, const Vector& offset) {
        Matrix rotation_matrix = compute_rotation_matrix<axis>(angle);

        return _rotation_exec::_rotate_from_exec(rotation_matrix, vector, offset);
    }

    template<typename axis>
    Vector rotate_to(double angle, const Vector& vector) {
        Matrix rotation_matrix = compute_rotation_matrix<axis>(angle);

        return _rotation_exec::_rotate_to_exec(rotation_matrix, vector);
    }

    template<typename axis>
    Vector rotate_to(double angle, const Vector& vector, const Vector& offset) {
        Matrix rotation_matrix = compute_rotation_matrix<axis>(angle);

        return _rotation_exec::_rotate_to_exec(rotation_matrix, vector, offset);
    }

    template<typename rotation_order, typename rotation_type>
    Vector rotate_from(const EulerAngles& angles, const Vector& vector) {
        Matrix rotation_matrix = compute_rotation_matrix<rotation_order, rotation_type>(angles);

        return _rotation_exec::_rotate_from_exec(rotation_matrix, vector);
    }

    template<typename rotation_order, typename rotation_type>
    Vector rotate_from(const EulerAngles& angles, const Vector& vector, const Vector& offset) {
        Matrix rotation_matrix = compute_rotation_matrix<rotation_order, rotation_type>(angles);

        return _rotation_exec::_rotate_from_exec(rotation_matrix, vector, offset);
    }

    template<typename rotation_order, typename rotation_type>
    Vector rotate_to(const EulerAngles& angles, const Vector& vector) {
        Matrix rotation_matrix = compute_rotation_matrix<rotation_order, rotation_type>(angles);

        return _rotation_exec::_rotate_to_exec(rotation_matrix, vector);
    }

    template<typename rotation_order, typename rotation_type>
    Vector rotate_to(const EulerAngles& angles, const Vector& vector, const Vector& offset) {
        Matrix rotation_matrix = compute_rotation_matrix<rotation_order, rotation_type>(angles);

        return _rotation_exec::_rotate_to_exec(rotation_matrix, vector, offset);
    }

    template<typename rotation_from, typename rotation_to,
             typename from_type, typename to_type>
    Vector rotate_between(const EulerAngles& angles_from, const EulerAngles& angles_to, const Vector& vector,
        const Vector& offset_from, const Vector& offset_to)
    {
        Matrix matrix_from = compute_rotation_matrix<rotation_from, from_type>(angles_from);
        Vector inert_vector = _rotation_exec::_rotate_from_exec(matrix_from, vector, offset_from);
        Matrix matrix_to = compute_rotation_matrix<rotation_to, to_type>(angles_to);

        return _rotation_exec::_rotate_to_exec(matrix_to, inert_vector, offset_to);
    }

} // namespace evspace

#endif // _EVSPACE_ROTATION_H_
