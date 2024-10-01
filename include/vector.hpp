#ifndef _EVSPACE_VECTOR_H_
#define _EVSPACE_VECTOR_H_

#include <cstddef>
#include <matrix.hpp>
#include <evspace_common.hpp>
#include <ostream>      // std::ostream

namespace evspace {

    EVSPACE_EXPORT class Vector {
    private:
        double* m_data;

        inline static double scalar_projection(const Vector&, const Vector&) noexcept;

    public:
        Vector();
        Vector(double, double, double);
        Vector(const Vector&);
        Vector(Vector&&) noexcept;
        ~Vector();

        Vector& operator=(const Vector&);
        Vector& operator=(Vector&&) noexcept;

        double& operator[](std::size_t);
        const double& operator[](std::size_t) const;

        friend std::ostream& operator<<(std::ostream&, const Vector&);

        Vector operator+(const Vector&) const;
        Vector& operator+=(const Vector&);
        Vector operator-() const;
        Vector operator-(const Vector&) const;
        Vector& operator-=(const Vector&);
        Vector operator*(double) const;
        Vector operator*(const Matrix&) const;
        Vector& operator*=(double);
        Vector& operator*=(const Matrix&);
        Vector operator/(double) const;
        Vector& operator/=(double);

        bool operator==(const Vector&) const;
        bool operator!=(const Vector&) const;

        double magnitude() const noexcept;
        double magnitude_squared() const noexcept;
        Vector& normalize() noexcept;
        Vector norm() const;

        friend double vector_dot(const Vector&, const Vector&) noexcept;
        friend Vector vector_cross(const Vector&, const Vector&);
        friend double vector_angle(const Vector&, const Vector&);
        friend Vector vector_exclude(const Vector&, const Vector&);
        friend Vector vector_projection(const Vector&, const Vector&);

        friend class Matrix;
    };

    double vector_dot(const Vector&, const Vector&) noexcept;
    Vector vector_cross(const Vector&, const Vector&);
    double vector_angle(const Vector&, const Vector&);
    Vector vector_exclude(const Vector&, const Vector&);
    Vector vector_projection(const Vector&, const Vector&);

    EVSPACE_EXPORT Vector operator*(double scalar, const Vector& vector);
    EVSPACE_EXPORT std::ostream& operator<<(std::ostream&, const Vector&);

    EVSPACE_EXPORT extern const Vector e1, e2, e3;

}

#endif // _EVSPACE_VECTOR_H_