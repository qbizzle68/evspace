#include <vector.hpp>
#include <matrix.hpp>
#include<_dot_product.hpp>
#include <cstddef>          // std::size_t
#include <stdexcept>        // std::out_of_range
#include <cmath>            // std::sqrt, std::acos
#include <ostream>          // std::ostream
#include <cstdio>           // std::sprintf

#define VECTOR_LENGTH 3
#define NEW_ARRAY   new double[VECTOR_LENGTH]
#define VECTOR_X(v) v.m_data[0]
#define VECTOR_Y(v) v.m_data[1]
#define VECTOR_Z(v) v.m_data[2]

static inline void set_array(double* vector, double x, double y, double z) {
    vector[0] = x;
    vector[1] = y;
    vector[2] = z;
}

evspace::Vector::Vector() {
    this->m_data = NEW_ARRAY;
    set_array(this->m_data, 0.0, 0.0, 0.0);
}

evspace::Vector::Vector(double x, double y, double z) {
    this->m_data = NEW_ARRAY;
    set_array(this->m_data, x, y, z);
}

evspace::Vector::Vector(const Vector& cpy) {
    this->m_data = NEW_ARRAY;
    set_array(this->m_data, cpy.m_data[0], cpy.m_data[1], cpy.m_data[2]);
}

evspace::Vector::Vector(Vector&& move) noexcept {
    this->m_data = move.m_data;
    move.m_data = NULL;
}

evspace::Vector::~Vector() {
    delete[] this->m_data;
}

evspace::Vector& evspace::Vector::operator=(const Vector& cpy) {
    set_array(this->m_data, VECTOR_X(cpy), VECTOR_Y(cpy), VECTOR_Z(cpy));
    return* this;
}

evspace::Vector& evspace::Vector::operator=(Vector&& move) noexcept {
    double* tmp = this->m_data;

    this->m_data = move.m_data;
    move.m_data = NULL;

    delete[] tmp;

    return *this;
}

double& evspace::Vector::operator[](std::size_t index) {
    if (index > 2) {
        throw std::out_of_range("Vector index out of range");
    }
    return this->m_data[index];
}

const double& evspace::Vector::operator[](std::size_t index) const {
    if (index > 2) {
        throw std::out_of_range("Vector index out of range");
    }
    return this->m_data[index];
}

std::ostream& ::operator<<(std::ostream& out, const evspace::Vector& vector) {
    out << "[ " << vector.m_data[0] << ", " << vector.m_data[1] << ", " << vector.m_data[2] << " ]";
    return out;
}

evspace::Vector evspace::Vector::operator+(const Vector& rhs) const {
    return Vector(
        VECTOR_X((*this)) + VECTOR_X(rhs),
        VECTOR_Y((*this)) + VECTOR_Y(rhs),
        VECTOR_Z((*this)) + VECTOR_Z(rhs)
    );
}

evspace::Vector& evspace::Vector::operator+=(const Vector& rhs) {
    VECTOR_X((*this)) += VECTOR_X(rhs);
    VECTOR_Y((*this)) += VECTOR_Y(rhs);
    VECTOR_Z((*this)) += VECTOR_Z(rhs);

    return *this;
}

evspace::Vector evspace::Vector::operator-() const {
    return Vector(
        -VECTOR_X((*this)),
        -VECTOR_Y((*this)),
        -VECTOR_Z((*this))
    );
}

evspace::Vector evspace::Vector::operator-(const Vector& rhs) const {
    return Vector(
        VECTOR_X((*this)) - VECTOR_X(rhs),
        VECTOR_Y((*this)) - VECTOR_Y(rhs),
        VECTOR_Z((*this)) - VECTOR_Z(rhs)
    );
}

evspace::Vector& evspace::Vector::operator-=(const Vector& rhs) {
    VECTOR_X((*this)) -= VECTOR_X(rhs);
    VECTOR_Y((*this)) -= VECTOR_Y(rhs);
    VECTOR_Z((*this)) -= VECTOR_Z(rhs);

    return *this;
}

evspace::Vector evspace::Vector::operator*(double scalar) const {
    return Vector(
        VECTOR_X((*this)) * scalar,
        VECTOR_Y((*this)) * scalar,
        VECTOR_Z((*this)) * scalar
    );
}

evspace::Vector& evspace::Vector::operator*=(double scalar) {
    VECTOR_X((*this)) *= scalar;
    VECTOR_Y((*this)) *= scalar;
    VECTOR_Z((*this)) *= scalar;

    return *this;
}

evspace::Vector evspace::Vector::operator*(const Matrix& matrix) const {
    return Vector(
        evspace::_compute_dot_product<Matrix>(this->m_data, matrix.m_data),
        evspace::_compute_dot_product<Matrix>(this->m_data, matrix.m_data + 1),
        evspace::_compute_dot_product<Matrix>(this->m_data, matrix.m_data + 2)
    );
}

evspace::Vector& evspace::Vector::operator*=(const Matrix& matrix) {
    Vector result = *this * matrix;

    double* tmp = this->m_data;
    this->m_data = result.m_data;
    result.m_data = tmp;

    return *this;
}

evspace::Vector evspace::Vector::operator/(double scalar) const {
    return Vector(
        VECTOR_X((*this)) / scalar,
        VECTOR_Y((*this)) / scalar,
        VECTOR_Z((*this)) / scalar
    );
}

evspace::Vector& evspace::Vector::operator/=(double scalar) {
    VECTOR_X((*this)) /= scalar;
    VECTOR_Y((*this)) /= scalar;
    VECTOR_Z((*this)) /= scalar;

    return *this;
}

bool evspace::Vector::operator==(const Vector& rhs) const {
    return (
        VECTOR_X((*this)) == VECTOR_X(rhs) &&
        VECTOR_Y((*this)) == VECTOR_Y(rhs) &&
        VECTOR_Z((*this)) == VECTOR_Z(rhs)
    );
}

bool evspace::Vector::operator!=(const Vector& rhs) const {
    return !(*this == rhs);
}

double evspace::Vector::magnitude() const noexcept {
    return std::sqrt(_compute_dot_product<Vector>(this->m_data, this->m_data));
}

double evspace::Vector::magnitude_squared() const noexcept {
    return _compute_dot_product<Vector>(this->m_data, this->m_data);
}

evspace::Vector& evspace::Vector::normalize() noexcept {
    double mag = this->magnitude();
    return *this /= mag;
}

evspace::Vector evspace::Vector::norm() const {
    double mag = this->magnitude();
    return Vector(
        VECTOR_X((*this)) / mag,
        VECTOR_Y((*this)) / mag,
        VECTOR_Z((*this)) / mag
    );
}

double evspace::vector_dot(const Vector& lhs, const Vector& rhs) noexcept {
    return _compute_dot_product<Vector>(lhs.m_data, rhs.m_data);
}

evspace::Vector evspace::vector_cross(const Vector& lhs, const Vector& rhs) {
    return evspace::Vector(
        VECTOR_Y(lhs) * VECTOR_Z(rhs) - VECTOR_Z(lhs) * VECTOR_Y(rhs),
        VECTOR_Z(lhs) * VECTOR_X(rhs) - VECTOR_X(lhs) * VECTOR_Z(rhs),
        VECTOR_X(lhs) * VECTOR_Y(rhs) - VECTOR_Y(lhs) * VECTOR_X(rhs)
    );
}

double evspace::vector_angle(const Vector& from, const Vector& to) {
    double dot_product = _compute_dot_product<Vector>(from.m_data, to.m_data);
    double magnitude_product = std::sqrt(
        _compute_dot_product<Vector>(from.m_data, from.m_data)
        * _compute_dot_product<Vector>(to.m_data, to.m_data)
    );

    return std::acos(dot_product / magnitude_product);
}

inline double evspace::Vector::scalar_projection(const Vector& project, const Vector& onto) noexcept {
    double dot_product = _compute_dot_product<Vector>(project.m_data, onto.m_data);
    double onto_mag_squared = _compute_dot_product<Vector>(onto.m_data, onto.m_data);

    return dot_product / onto_mag_squared;
}

evspace::Vector evspace::vector_exclude(const Vector& vector, const Vector& exclude) {
    double scale = Vector::scalar_projection(vector, exclude);
    
    return Vector(
        VECTOR_X(vector) - VECTOR_X(exclude) * scale,
        VECTOR_Y(vector) - VECTOR_Y(exclude) * scale,
        VECTOR_Z(vector) - VECTOR_Z(exclude) * scale
    );
}

evspace::Vector evspace::vector_projection(const Vector& project, const Vector& onto) {
    double scale = Vector::scalar_projection(project, onto);
    return onto * scale;
}

evspace::Vector operator*(double scalar, const evspace::Vector& vector) {
    return vector * scalar;
}

const evspace::Vector evspace::Vector::e1 = evspace::Vector(1, 0, 0);
const evspace::Vector evspace::Vector::e2 = evspace::Vector(0, 1, 0);
const evspace::Vector evspace::Vector::e3 = evspace::Vector(0, 0, 1);
