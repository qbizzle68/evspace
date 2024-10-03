#include <rotation.hpp>
#include <matrix.hpp>
#include <vector.hpp>

evspace::Matrix evspace::compute_rotation_matrix(double angle, const evspace::Vector& rotation_vector) {
    Vector vector_normal = rotation_vector.norm();
    Matrix w = Matrix(
        {
            { 0.0, -vector_normal[2], vector_normal[1] },
            { vector_normal[2], 0.0, -vector_normal[0] },
            { -vector_normal[1], vector_normal[0], 0.0 }
        }
    );

    return IDENTITY + (w * std::sin(angle)) + (w * w * (1 - std::cos(angle)));
}

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

inline evspace::Vector evspace::_rotation_exec::_rotate_from_exec(const Matrix& matrix, const Vector& vector) {
    return matrix * vector;
}

inline evspace::Vector evspace::_rotation_exec::_rotate_from_exec(const Matrix& matrix, const Vector& vector, const Vector& offset) {
    return (matrix * vector) + offset;
}

inline evspace::Vector evspace::_rotation_exec::_rotate_to_exec(const Matrix& matrix, const Vector& vector) {
    return vector * matrix;
}

inline evspace::Vector evspace::_rotation_exec::_rotate_to_exec(const Matrix& matrix, const Vector& vector, const Vector& offset) {
    return (vector - offset) * matrix;
}

evspace::Vector evspace::rotate_from(const Matrix& rotation_matrix, const Vector& vector) {
    return _rotation_exec::_rotate_from_exec(rotation_matrix, vector);
}

evspace::Vector evspace::rotate_from(const Matrix& rotation_matrix, const Vector& vector, const Vector& offset) {
    return _rotation_exec::_rotate_from_exec(rotation_matrix, vector, offset);
}

evspace::Vector evspace::rotate_to(const Matrix& rotation_matrix, const Vector& vector) {
    return _rotation_exec::_rotate_to_exec(rotation_matrix, vector);
}

evspace::Vector evspace::rotate_to(const Matrix& rotation_matrix, const Vector& vector, const Vector& offset) {
    return _rotation_exec::_rotate_to_exec(rotation_matrix, vector, offset);
}
