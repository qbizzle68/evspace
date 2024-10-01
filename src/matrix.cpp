#include <matrix.hpp>
#include <vector.hpp>
#include <_dot_product.hpp>
#include <cstddef>      // std::size_t
#include <stdexcept>    // std::out_of_range
#include <cstring>      // std::memcpy
#include <algorithm>    // std::swap, std::transform
#include <functional>   // std::plus,

evspace::MatrixRow::MatrixRow(double* data) noexcept : m_data(data) { }

evspace::MatrixRow::MatrixRow(const MatrixRow& row) noexcept : m_data(row.m_data) { }

evspace::MatrixRow::MatrixRow(MatrixRow&& row) noexcept {
    this->m_data = row.m_data;
    row.m_data = NULL;
}

evspace::MatrixRow& evspace::MatrixRow::operator=(const MatrixRow& cpy) noexcept {
    // no need to free the current data since it is only a reference and isn't owned by this
    this->m_data = cpy.m_data;

    return *this;
}

evspace::MatrixRow& evspace::MatrixRow::operator=(MatrixRow&& move) noexcept {
    // no need to free the current data since it is only a reference
    this->m_data = move.m_data;

    return *this;
}

double& evspace::MatrixRow::operator[](std::size_t index) {
    if (index > 2) {
        throw std::out_of_range("MatrixRow column index out of range");
    }

    return this->m_data[index];
}


const double& evspace::MatrixRow::operator[](std::size_t index) const {
    if (index > 2) {
        throw std::out_of_range("MatrixRow column index out of range");
    }

    return this->m_data[index];
}

/******************** MATRIX IMPLEMENTATION **********************/

#define MATRIX_ARRAY_LENGTH     9
#define MATRIX_SIZE             MATRIX_ARRAY_LENGTH * sizeof(double)
#define MATRIX_ITEM(m, r, c)    m.m_data[(r*3) + c]

// matrix iterator proxies
#define MATRIX_BEGIN(m)         m.m_data
#define MATRIX_END(m)           m.m_data + MATRIX_ARRAY_LENGTH

// matrix row access proxies
#define MATRIX_FIRST_ROW(m)     m.m_data
#define MATRIX_SECOND_ROW(m)    (m.m_data + 3)
#define MATRIX_THIRD_ROW(m)     (m.m_data + 6)

evspace::Matrix::Matrix() {
    this->m_data = new double[9] {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    this->m_rows = new MatrixRow[3]{
        MATRIX_FIRST_ROW((*this)),
        MATRIX_SECOND_ROW((*this)),
        MATRIX_THIRD_ROW((*this)),
    };
}

evspace::Matrix::Matrix(const Matrix& cpy) {
    this->m_data = new double[9];
    std::memcpy(this->m_data, cpy.m_data, MATRIX_SIZE);
    this->m_rows = new MatrixRow[3]{
        MATRIX_FIRST_ROW((*this)),
        MATRIX_SECOND_ROW((*this)),
        MATRIX_THIRD_ROW((*this))
    };
}

evspace::Matrix::Matrix(Matrix&& move) noexcept {
    this->m_data = move.m_data;
    move.m_data = NULL;
    this->m_rows = move.m_rows;
    move.m_rows = NULL;
}

evspace::Matrix::~Matrix() {
    delete[] this->m_rows;
    delete[] this->m_data;
}

evspace::Matrix& evspace::Matrix::operator=(const Matrix& rhs) {
    std::memcpy(this->m_data, rhs.m_data, MATRIX_SIZE);
    this->m_rows[0] = MatrixRow(MATRIX_FIRST_ROW((*this)));
    this->m_rows[1] = MatrixRow(MATRIX_SECOND_ROW((*this)));
    this->m_rows[2] = MatrixRow(MATRIX_THIRD_ROW((*this)));

    return *this;
}

evspace::Matrix& evspace::Matrix::operator=(Matrix&& rhs) noexcept {
    std::swap(this->m_data, rhs.m_data);
    std::swap(this->m_rows, rhs.m_rows);

    return *this;
}

evspace::MatrixRow& evspace::Matrix::operator[](std::size_t index) {
    if (index > 2) {
        throw std::out_of_range("Matrix row index out of range");
    }

    return this->m_rows[index];
}

const evspace::MatrixRow& evspace::Matrix::operator[](std::size_t index) const {
    if (index > 2) {
        throw std::out_of_range("Matrix row index out of range");
    }

    return this->m_rows[index];
}

std::ostream& evspace::operator<<(std::ostream& out, const Matrix& matrix) {
    out << "[ [ " << matrix[0][0] << ", " << matrix[0][1] << ", " << matrix[0][2] << " ], [ "
        << matrix[1][0] << ", " << matrix[1][1] << ", " << matrix[1][2] << " ], [ "
        << matrix[2][0] << ", " << matrix[2][1] << ", " << matrix[2][2] << " ] ]";
    return out;
}

evspace::Matrix evspace::Matrix::operator+(const Matrix& rhs) const {
    Matrix result = Matrix();

    for (int i = 0; i < MATRIX_ARRAY_LENGTH; i++) {
        result.m_data[i] = this->m_data[i] + rhs.m_data[i];
    }

    return result;
}

evspace::Matrix& evspace::Matrix::operator+=(const Matrix& rhs) {
    for (int i = 0; i < MATRIX_ARRAY_LENGTH; i++) {
        this->m_data[i] += rhs.m_data[i];
    }

    return *this;
}

evspace::Matrix evspace::Matrix::operator-() const {
    Matrix result = Matrix();

    for (int i = 0; i < MATRIX_ARRAY_LENGTH; i++) {
        result.m_data[i] = -this->m_data[i];
    }

    return result;
}

#include <iostream>
evspace::Matrix evspace::Matrix::operator-(const Matrix& rhs) const {
    Matrix result = Matrix();

    for (int i = 0; i < MATRIX_ARRAY_LENGTH; i++) {
        result.m_data[i] = this->m_data[i] - rhs.m_data[i];
        std::cout << "subtracting index " << i << "; this at index: " << this->m_data[i]
            << "; rhs at index: " << rhs.m_data[i] << "; result at index: " << result.m_data[i] << '\n';
    }

    return result;
}

evspace::Matrix& evspace::Matrix::operator-=(const Matrix& rhs) {
    for (int i = 0; i < MATRIX_ARRAY_LENGTH; i++) {
        this->m_data[i] -= rhs.m_data[i];
    }

    return *this;
}

evspace::Matrix evspace::Matrix::operator*(double scalar) const {
    Matrix result = Matrix();

    for (int i = 0; i < MATRIX_ARRAY_LENGTH; i++) {
        result.m_data[i] = this->m_data[i] * scalar;
    }

    return result;
}

evspace::Matrix& evspace::Matrix::operator*=(double scalar) {
    for (int i = 0; i < MATRIX_ARRAY_LENGTH; i++) {
        this->m_data[i] *= scalar;
    }
    
    return *this;
}

evspace::Vector evspace::Matrix::operator*(const Vector& vec) const {
    return Vector(
        _compute_dot_product<Vector>(this->m_data, vec.m_data),
        _compute_dot_product<Vector>(this->m_data + 3, vec.m_data),
        _compute_dot_product<Vector>(this->m_data + 6, vec.m_data)
    );
}

evspace::Matrix evspace::Matrix::operator*(const Matrix& rhs) const {
    Matrix result = Matrix();

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            MATRIX_ITEM(result, i, j) = _compute_dot_product<Matrix>(this->m_data + (i * 3), rhs.m_data + j);
        }
    }

    return result;
}

evspace::Matrix& evspace::Matrix::operator*=(const Matrix& rhs) {
    double tmp[9];
    memcpy(tmp, this->m_data, MATRIX_SIZE);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            MATRIX_ITEM((*this), i, j) = _compute_dot_product<Matrix>(tmp + (i * 3), rhs.m_data + j);
        }
    }

    return *this;
}

evspace::Matrix evspace::Matrix::operator/(double scalar) const {
    Matrix matrix = Matrix();

    for (int i = 0; i < MATRIX_ARRAY_LENGTH; i++) {
        matrix.m_data[i] = this->m_data[i] / scalar;
    }

    return matrix;
}

evspace::Matrix& evspace::Matrix::operator/=(double scalar) {
    for (int i = 0; i < MATRIX_ARRAY_LENGTH; i++) {
        this->m_data[i] /= scalar;
    }

    return *this;
}

bool evspace::Matrix::operator==(const Matrix& rhs) const {
    for (int i = 0; i < MATRIX_ARRAY_LENGTH; i++) {
        if (this->m_data[i] != rhs.m_data[i]) {
            return false;
        }
    }

    return true;
}

bool evspace::Matrix::operator!=(const Matrix& rhs) const {
    return !(*this == rhs);
}

double evspace::Matrix::determinate() const {
    double result = 0;

    result += MATRIX_ITEM((*this), 0, 0) * (MATRIX_ITEM((*this), 1, 1) * MATRIX_ITEM((*this), 2, 2) - MATRIX_ITEM((*this), 1, 2) * MATRIX_ITEM((*this), 2, 1));
    result -= MATRIX_ITEM((*this), 0, 1) * (MATRIX_ITEM((*this), 1, 0) * MATRIX_ITEM((*this), 2, 2) - MATRIX_ITEM((*this), 1, 2) * MATRIX_ITEM((*this), 2, 0));
    result += MATRIX_ITEM((*this), 0, 2) * (MATRIX_ITEM((*this), 1, 0) * MATRIX_ITEM((*this), 2, 1) - MATRIX_ITEM((*this), 1, 1) * MATRIX_ITEM((*this), 2, 0));

    return result;
}

evspace::Matrix evspace::Matrix::transpose() const {
    return Matrix({
        { MATRIX_ITEM((*this), 0, 0), MATRIX_ITEM((*this), 1, 0), MATRIX_ITEM((*this), 2, 0) },
        { MATRIX_ITEM((*this), 0, 1), MATRIX_ITEM((*this), 1, 1), MATRIX_ITEM((*this), 2, 1) },
        { MATRIX_ITEM((*this), 0, 2), MATRIX_ITEM((*this), 1, 2), MATRIX_ITEM((*this), 2, 2) },
    });
}

evspace::Matrix& evspace::Matrix::transpose_inplace() {
    std::swap(MATRIX_ITEM((*this), 0, 1), MATRIX_ITEM((*this), 1, 0));
    std::swap(MATRIX_ITEM((*this), 0, 2), MATRIX_ITEM((*this), 2, 0));
    std::swap(MATRIX_ITEM((*this), 1, 2), MATRIX_ITEM((*this), 2, 1));

    return *this;
}

evspace::Matrix evspace::IDENTITY = evspace::Matrix({ {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0} });
