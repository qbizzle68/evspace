#ifndef _EVSPACE_VECTOR_H_
#define _EVSPACE_VECTOR_H_

#include <cstddef>      // std::size_t
#include <ostream>      // std::ostream
#include <stdexcept>    // std::out_of_range
#include <cmath>        // std::sqrt, std::acos
#include <evspace_common.hpp>
#include <matrix.hpp>

// forward declaration for global friend function signature (below function)
namespace evspace { class Vector; }

// friend declaration must first be non-local to evspace::Vector (i.e. global namespace)
EVSPACE_API std::ostream& operator<<(std::ostream& out, const evspace::Vector& vector);

namespace evspace {

    // Represent vector from a three dimensional vector space. The dimension
    // is strictly three, making the class highly optimizable for computational
    // efficiency. 
    class EVSPACE_API Vector {
    protected:
        double* m_data;

    private:
        // Computes the scalar projection of v1 onto the v2 which makes
        // other vector computations easier to handle. This is
        // equal to the fraction of v1's projection relative to v2's
        // magnitude. This is equal to |v1| * cos(theta) / |v2| where
        // theta is the angle between v1 and v2.
        inline constexpr static double
        scalar_projection(const Vector& v1, const Vector& v2) noexcept;

    public:
        EVSPACE_CONSTEXPR Vector() EVSPACE_NOEXCEPT;
        EVSPACE_CONSTEXPR Vector(double, double, double) EVSPACE_NOEXCEPT;
        EVSPACE_CONSTEXPR Vector(const Vector&) EVSPACE_NOEXCEPT;
        EVSPACE_CONSTEXPR Vector(Vector&&) noexcept;
        EVSPACE_CONSTEXPR ~Vector();

        constexpr Vector& operator=(const Vector&);
        constexpr Vector& operator=(Vector&&) noexcept;

        EVSPACE_CONSTEXPR26 double& operator[](std::size_t);
        EVSPACE_CONSTEXPR26 const double& operator[](std::size_t) const;

        // Prints the Vector as a string similar to Python lists. A
        // Vector whose components are a, b, and c would print the string
        // "[ a, b, c ]".
        friend std::ostream& ::operator<<(std::ostream&, const Vector&);

        EVSPACE_CONSTEXPR Vector operator+(const Vector&) const EVSPACE_NOEXCEPT;
        constexpr Vector& operator+=(const Vector&) noexcept;
        EVSPACE_CONSTEXPR Vector operator-() const EVSPACE_NOEXCEPT;
        EVSPACE_CONSTEXPR Vector operator-(const Vector&) const EVSPACE_NOEXCEPT;
        constexpr Vector& operator-=(const Vector&) noexcept;
        EVSPACE_CONSTEXPR Vector operator*(double) const EVSPACE_NOEXCEPT;
        EVSPACE_CONSTEXPR Vector operator*(const Matrix&) const EVSPACE_NOEXCEPT;
        constexpr Vector& operator*=(double) noexcept;
        constexpr Vector& operator*=(const Matrix&);
        EVSPACE_CONSTEXPR Vector operator/(double) const;
        constexpr Vector& operator/=(double);

        constexpr bool operator==(const Vector&) const;
        constexpr bool operator!=(const Vector&) const;

        // Checks if the underlying data array is in a valid state. If
        // EVSPACE_CONSTRUCTOR_NOTHROW is defined constructors are
        // guaranteed not to throw even on an allocation exception, which
        // leaves the internal data array unallocated. The constructed
        // Vector in this case is in an invalid state and should not be
        // used.
        constexpr bool is_valid() const;

        // Computes the length of the Vector. This is roughly equivalent to
        // std::sqrt(vector.magnitude_squared());
        // If your goal is the magnitude squared, using this return value
        // will induce rounding errors and magnitude_squared() should be
        // preferred.
        EVSPACE_CONSTEXPR26 double magnitude() const noexcept;

        // Computes the square of the magnitude of the Vector. This should
        // be preferred to squaring the result of the magnitude() method as
        // the latter will contain rounding errors.
        constexpr double magnitude_squared() const noexcept;

        // Modifies this Vector by dividing each element by it's vector norm
        // so the calling vector will be a unit vector, preserving direction.
        // Roughly equivalent to
        // vector = vector / vector.mag();
        EVSPACE_CONSTEXPR26 Vector& normalize() noexcept;

        // Creates a new Vector instance equal to a unit vector pointing in
        // the direction of the calling Vector.
        EVSPACE_CONSTEXPR26 Vector norm() const;

        EVSPACE_API friend constexpr double vector_dot(const Vector&, const Vector&) noexcept;
        EVSPACE_API friend EVSPACE_CONSTEXPR Vector vector_cross(const Vector&, const Vector&);
        EVSPACE_API friend EVSPACE_CONSTEXPR26 double vector_angle(const Vector&, const Vector&);
        EVSPACE_API friend EVSPACE_CONSTEXPR Vector vector_exclude(const Vector&, const Vector&);
        EVSPACE_API friend EVSPACE_CONSTEXPR Vector vector_projection(const Vector&, const Vector&);

        friend class Matrix;

        static const Vector e1;
        static const Vector e2;
        static const Vector e3;
    };

    EVSPACE_API constexpr double vector_dot(const Vector&, const Vector&) noexcept;
    EVSPACE_API EVSPACE_CONSTEXPR Vector vector_cross(const Vector&, const Vector&);
    EVSPACE_API EVSPACE_CONSTEXPR26 double vector_angle(const Vector&, const Vector&);
    EVSPACE_API EVSPACE_CONSTEXPR Vector vector_exclude(const Vector&, const Vector&);
    EVSPACE_API EVSPACE_CONSTEXPR Vector vector_projection(const Vector&, const Vector&);

    EVSPACE_API EVSPACE_CONSTEXPR Vector operator*(double scalar, const Vector& vector);

    #define VECTOR_X(v) (v).m_data[0]
    #define VECTOR_Y(v) (v).m_data[1]
    #define VECTOR_Z(v) (v).m_data[2]

    constexpr static inline void
    set_array(double* vector, double x, double y, double z) {
        vector[0] = x;
        vector[1] = y;
        vector[2] = z;
    }

    inline EVSPACE_CONSTEXPR Vector::Vector() EVSPACE_NOEXCEPT {
        this->m_data = new EVSPACE_NOTHROW double[3];
        set_array(this->m_data, 0.0, 0.0, 0.0);
    }

    inline EVSPACE_CONSTEXPR Vector::Vector(double x, double y, double z) EVSPACE_NOEXCEPT {
        this->m_data = new EVSPACE_NOTHROW double[3];
        set_array(this->m_data, x, y, z);
    }

    inline EVSPACE_CONSTEXPR Vector::Vector(const Vector& cpy) EVSPACE_NOEXCEPT {
        this->m_data = new EVSPACE_NOTHROW double[3];
        set_array(this->m_data, cpy.m_data[0], cpy.m_data[1], cpy.m_data[2]);
    }

    inline EVSPACE_CONSTEXPR Vector::Vector(Vector&& move) noexcept {
        this->m_data = move.m_data;
        move.m_data = NULL;
    }

    inline EVSPACE_CONSTEXPR Vector::~Vector() {
        delete[] this->m_data;
    }

    inline constexpr Vector& Vector::operator=(const Vector& cpy) {
        set_array(this->m_data, VECTOR_X(cpy), VECTOR_Y(cpy), VECTOR_Z(cpy));
        return* this;
    }

    inline constexpr Vector& Vector::operator=(Vector&& move) noexcept {
        // not using std::swap because primitive type will generate identical
        // assembly and std::swap requires c++20 to be constexpr
        double* tmp = this->m_data;
        this->m_data = move.m_data;
        move.m_data = tmp;

        return *this;
    }

    inline EVSPACE_CONSTEXPR26 double& Vector::operator[](std::size_t index) {
        if (index > 2) {
            throw std::out_of_range("Vector index out of range");
        }
        return this->m_data[index];
    }

    inline EVSPACE_CONSTEXPR26 const double& Vector::operator[](std::size_t index) const {
        if (index > 2) {
            throw std::out_of_range("Vector index out of range");
        }
        return this->m_data[index];
    }

    inline EVSPACE_CONSTEXPR Vector
    Vector::operator+(const Vector& rhs) const EVSPACE_NOEXCEPT {
        return Vector(
            VECTOR_X(*this) + VECTOR_X(rhs),
            VECTOR_Y(*this) + VECTOR_Y(rhs),
            VECTOR_Z(*this) + VECTOR_Z(rhs)
        );
    }

    inline constexpr Vector&
    Vector::operator+=(const Vector& rhs) noexcept {
        VECTOR_X(*this) += VECTOR_X(rhs);
        VECTOR_Y(*this) += VECTOR_Y(rhs);
        VECTOR_Z(*this) += VECTOR_Z(rhs);

        return *this;
    }

    inline EVSPACE_CONSTEXPR Vector
    Vector::operator-() const EVSPACE_NOEXCEPT {
        return Vector(
            -VECTOR_X(*this),
            -VECTOR_Y(*this),
            -VECTOR_Z(*this)
        );
    }

    inline EVSPACE_CONSTEXPR Vector
    Vector::operator-(const Vector& rhs) const EVSPACE_NOEXCEPT {
        return Vector(
            VECTOR_X(*this) - VECTOR_X(rhs),
            VECTOR_Y(*this) - VECTOR_Y(rhs),
            VECTOR_Z(*this) - VECTOR_Z(rhs)
        );
    }

    inline constexpr Vector&
    Vector::operator-=(const Vector& rhs) noexcept {
        VECTOR_X(*this) -= VECTOR_X(rhs);
        VECTOR_Y(*this) -= VECTOR_Y(rhs);
        VECTOR_Z(*this) -= VECTOR_Z(rhs);

        return *this;
    }

    inline EVSPACE_CONSTEXPR Vector
    Vector::operator*(double scalar) const EVSPACE_NOEXCEPT {
        return Vector(
            VECTOR_X(*this) * scalar,
            VECTOR_Y(*this) * scalar,
            VECTOR_Z(*this) * scalar
        );
    }

    inline EVSPACE_CONSTEXPR Vector
    Vector::operator*(const Matrix& matrix) const EVSPACE_NOEXCEPT {
        Vector result;
        for (int i = 0; i < 3; i++) {
            double sum = 0;
            for(int j = 0; j < 3; j++) {
                sum = std::fma(this->m_data[j], matrix.m_data[j * 3 + i], sum);
            }
            result[i] = sum;
        }
        return result;
    }

    inline constexpr Vector&
    Vector::operator*=(double scalar) noexcept {
        VECTOR_X(*this) *= scalar;
        VECTOR_Y(*this) *= scalar;
        VECTOR_Z(*this) *= scalar;

        return *this;
    }

    inline constexpr Vector&
    Vector::operator*=(const Matrix& matrix) {
        double buffer[3]{this->m_data[0], this->m_data[1], this->m_data[2]};
        
        for (int i = 0; i < 3; i++) {
            double sum = 0;
            for (int j = 0; j < 3; j++) {
                sum = std::fma(buffer[j], matrix.m_data[j * 3 + i], sum);
            }
            this->m_data[i] = sum;
        }

        return *this;
    }

    inline EVSPACE_CONSTEXPR Vector
    Vector::operator/(double scalar) const {
        return Vector(
            VECTOR_X(*this) / scalar,
            VECTOR_Y(*this) / scalar,
            VECTOR_Z(*this) / scalar
        );
    }

    inline constexpr Vector&
    Vector::operator/=(double scalar) {
        VECTOR_X(*this) /= scalar;
        VECTOR_Y(*this) /= scalar;
        VECTOR_Z(*this) /= scalar;

        return *this;
    }

    inline constexpr bool Vector::operator==(const Vector& rhs) const {
        return (
            VECTOR_X(*this) == VECTOR_X(rhs) &&
            VECTOR_Y(*this) == VECTOR_Y(rhs) &&
            VECTOR_Z(*this) == VECTOR_Z(rhs)
        );
    }

    inline constexpr bool Vector::operator!=(const Vector& rhs) const {
        return !(*this == rhs);
    }

    inline constexpr bool Vector::is_valid() const {
        return (this->m_data != NULL);
    }

    inline EVSPACE_CONSTEXPR26 double
    Vector::magnitude() const noexcept{
        return std::sqrt(vector_dot(*this, *this));
    }

    inline constexpr double
    Vector::magnitude_squared() const noexcept {
        return vector_dot(*this, *this);
    }

    inline EVSPACE_CONSTEXPR26 Vector&
    Vector::normalize() noexcept {
        double mag = this->magnitude();
        return *this /= mag;
    }

    inline EVSPACE_CONSTEXPR26 Vector
    Vector::norm() const {
        double mag = this->magnitude();
        return Vector(
            VECTOR_X(*this) / mag,
            VECTOR_Y(*this) / mag,
            VECTOR_Z(*this) / mag
        );
    }

    inline constexpr double
    vector_dot(const Vector& lhs, const Vector& rhs) noexcept {
        return std::fma(lhs.m_data[0], rhs.m_data[0],
            std::fma(lhs.m_data[1], rhs.m_data[1],
                        lhs.m_data[2] * rhs.m_data[2]));
    }

    inline EVSPACE_CONSTEXPR Vector
    vector_cross(const Vector& lhs, const Vector& rhs) {
        return Vector(
            VECTOR_Y(lhs) * VECTOR_Z(rhs) - VECTOR_Z(lhs) * VECTOR_Y(rhs),
            VECTOR_Z(lhs) * VECTOR_X(rhs) - VECTOR_X(lhs) * VECTOR_Z(rhs),
            VECTOR_X(lhs) * VECTOR_Y(rhs) - VECTOR_Y(lhs) * VECTOR_X(rhs)
        );
    }

    inline EVSPACE_CONSTEXPR26 double
    vector_angle(const Vector& from, const Vector& to) {
        double dot_product = vector_dot(from, to);
        double magnitude_product = std::sqrt(
            vector_dot(from, from) *
            vector_dot(to, to)
        );

        return std::acos(dot_product / magnitude_product);
    }

    inline constexpr double
    Vector::scalar_projection(const Vector& project, const Vector& onto) noexcept {
        // This is equal to |project| * cos(theta) / |onto|, equal to the
        // fraction of project's projection onto onto relative to the magnitude
        // of onto.

        double dot_product = vector_dot(project, onto);
        double onto_mag_squared = vector_dot(onto, onto);

        return dot_product / onto_mag_squared;
    }

    inline EVSPACE_CONSTEXPR Vector
    vector_exclude(const Vector& vector, const Vector& exclude) {
        double scale = Vector::scalar_projection(vector, exclude);
        
        return Vector(
            VECTOR_X(vector) - VECTOR_X(exclude) * scale,
            VECTOR_Y(vector) - VECTOR_Y(exclude) * scale,
            VECTOR_Z(vector) - VECTOR_Z(exclude) * scale
        );
    }

    inline EVSPACE_CONSTEXPR Vector
    vector_projection(const Vector& project, const Vector& onto) {
        double scale = Vector::scalar_projection(project, onto);
        return onto * scale;
    }

    inline EVSPACE_CONSTEXPR Vector
    operator*(double scalar, const Vector& vector) {
        return vector * scalar;
    }

    inline const Vector Vector::e1{1, 0, 0};
    inline const Vector Vector::e2{0, 1, 0};
    inline const Vector Vector::e3{0, 0, 1};

}   // namespace evspace

inline std::ostream& operator<<(std::ostream& out, const evspace::Vector& vector) {
    out << "[ " << vector.m_data[0] << ", " << vector.m_data[1] << ", " << vector.m_data[2] << " ]";
    return out;
}

#undef VECTOR_X
#undef VECTOR_Y
#undef VECTOR_Z

#endif // _EVSPACE_VECTOR_H_