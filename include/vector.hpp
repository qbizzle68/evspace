#ifndef _EVSPACE_VECTOR_H_
#define _EVSPACE_VECTOR_H_

#include <cstddef>
#include <matrix.hpp>
#include <evspace_common.hpp>
#include <ostream>      // std::ostream

// forward declaration for global friend function signature (below function)
namespace evspace { class Vector; }

// friend declaration must first be non-local to evspace::Vector (i.e. global namespace)
EVSPACE_API std::ostream& operator<<(std::ostream& out, const evspace::Vector& vector);

namespace evspace {

    class EVSPACE_API Vector {
    protected:
        double* m_data;

    private:
        inline static double scalar_projection(const Vector&, const Vector&) noexcept;

    public:
        Vector() EVSPACE_NOEXCEPT;
        Vector(double, double, double) EVSPACE_NOEXCEPT;
        Vector(const Vector&) EVSPACE_NOEXCEPT;
        Vector(Vector&&) noexcept;
        ~Vector();

        Vector& operator=(const Vector&);
        Vector& operator=(Vector&&) noexcept;

        double& operator[](std::size_t);
        const double& operator[](std::size_t) const;

        friend std::ostream& ::operator<<(std::ostream&, const Vector&);

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

        bool is_valid() const;

        double magnitude() const noexcept;
        double magnitude_squared() const noexcept;
        Vector& normalize() noexcept;
        Vector norm() const;

        EVSPACE_API friend double vector_dot(const Vector&, const Vector&) noexcept;
        EVSPACE_API friend Vector vector_cross(const Vector&, const Vector&);
        EVSPACE_API friend double vector_angle(const Vector&, const Vector&);
        EVSPACE_API friend Vector vector_exclude(const Vector&, const Vector&);
        EVSPACE_API friend Vector vector_projection(const Vector&, const Vector&);

        friend class Matrix;

        static const Vector e1;
        static const Vector e2;
        static const Vector e3;
    };

    EVSPACE_API double vector_dot(const Vector&, const Vector&) noexcept;
    EVSPACE_API Vector vector_cross(const Vector&, const Vector&);
    EVSPACE_API double vector_angle(const Vector&, const Vector&);
    EVSPACE_API Vector vector_exclude(const Vector&, const Vector&);
    EVSPACE_API Vector vector_projection(const Vector&, const Vector&);

    //EVSPACE_API extern const Vector e1, e2, e3;

}   // namespace evspace

EVSPACE_API evspace::Vector operator*(double scalar, const evspace::Vector& vector);

#endif // _EVSPACE_VECTOR_H_