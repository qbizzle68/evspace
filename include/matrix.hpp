#ifndef _EVSPACE_MATRIX_H_
#define _EVSPACE_MATRIX_H_

#include <evspace_common.hpp>
#include <initializer_list>
#include <cstddef>  // std::size_t
#include <cstring>  // memcpy
#include <iterator> // std::data

namespace evspace {

    EVSPACE_EXPORT class Vector;

    //  MatrixRow just wraps around a block of memory from a Matrix array row.
    //  MatrixRow is not responsible for deleting any memory.
    EVSPACE_EXPORT class MatrixRow {
    private:
        double* m_data;
    public:
        MatrixRow() = delete;
        MatrixRow(double*) noexcept;
        MatrixRow(const MatrixRow&) noexcept;
        MatrixRow(MatrixRow&&) noexcept;
        
        MatrixRow& operator=(const MatrixRow&) noexcept;
        MatrixRow& operator=(MatrixRow&&) noexcept;

        double& operator[](std::size_t);
        const double& operator[](std::size_t) const;
    };

    EVSPACE_EXPORT class Matrix {
    private:
        double* m_data;
        MatrixRow* m_rows;
    public:
        Matrix();
        template<typename T, std::size_t N>
        Matrix(const T(&)[N][N]);
        Matrix(const Matrix&);
        Matrix(Matrix&&) noexcept;
        ~Matrix();

        Matrix& operator=(const Matrix&);
        Matrix& operator=(Matrix&&) noexcept;

        MatrixRow& operator[](std::size_t);
        const MatrixRow& operator[](std::size_t) const;

        Matrix operator+(const Matrix&) const;
        Matrix& operator+=(const Matrix&);
        Matrix operator-() const;
        Matrix operator-(const Matrix&) const;
        Matrix& operator-=(const Matrix&);
        Matrix operator*(double) const;
        Matrix& operator*=(double);
        Matrix operator*(const Matrix&) const;
        Matrix& operator*=(const Matrix&);
        Vector operator*(const Vector&) const;
        Matrix operator/(double) const;
        Matrix& operator/=(double);

        bool operator==(const Matrix&) const;
        bool operator!=(const Matrix&) const;

        double determinate() const;
        Matrix transpose() const;
        Matrix& transpose_inplace();

        friend class Vector;
        friend Matrix _matrix_from_array(double*);
    };

    extern Matrix IDENTITY;

    //Matrix _matrix_from_array(double*);

    // todo: why can't we do (const T(&list)[3][3])
    template<typename T, std::size_t N>
    Matrix::Matrix(const T(&list)[N][N]) {
        static_assert(N == 3, "Initializer arrays must have length exactly 3");

        this->m_data = new double[9];
        std::memcpy(this->m_data, std::data(list[0]), 3 * sizeof(double));
        std::memcpy(this->m_data + 3, std::data(list[1]), 3 * sizeof(double));
        std::memcpy(this->m_data + 6, std::data(list[2]), 3 * sizeof(double));

        this->m_rows = new MatrixRow[3]{ this->m_data, this->m_data + 3, this->m_data + 6 };
    }

} // namespace evspace

#endif // _EVSPACE_MATRIX_H_
