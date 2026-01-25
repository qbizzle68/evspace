#ifndef _EVSPACE_MATRIX_H_
#define _EVSPACE_MATRIX_H_

#include <evspace_common.hpp>
#include <comma_operator.hpp>
#include <initializer_list>
#include <cstddef>      // std::size_t
#include <cstring>      // std::memcpy
#include <stdexcept>    // std::out_of_range
#include <iterator>     // std::data
#include <algorithm>    // std::copy
#include <ostream>      // std::ostream
#include <type_traits>

#define MATRIX_ARRAY_LENGTH     9
#define MATRIX_ROW_LENGTH       3
#define MATRIX_BYTE_SIZE        MATRIX_ARRAY_LENGTH * sizeof(double)
#define MATRIX_ROW_BYTE_SIZE    MATRIX_ROW_LENGTH * sizeof(double)
#define MATRIX_ITEM(m, r, c)    (m).m_data[evspace::Matrix::matrix_index(r, c)]
#define MATRIX_ITEM_THIS(r, c)  MATRIX_ITEM(*this, r, c)

// forward declaration for use in global function declaration signature
namespace evspace { class Matrix; }
// non-local declaration for friend function
std::ostream& operator<<(std::ostream&, const evspace::Matrix&);

namespace evspace {

    class Vector;

    class Matrix {
    protected:
        double* m_data;
        
        [[nodiscard]]
        constexpr inline static std::size_t
        matrix_index(std::size_t r, std::size_t c) noexcept;

        public:

        // Helper class that provides support for comma operator
        // initialization. This type is returned by operator<<
        // overload and chained to support initialization via
        // comma separated values.
        class CommaInitializerM : public CommaInitializer<Matrix> {
        private:
            double& get_component(const std::size_t index) {
                if (index >= 9) {
                    throw std::out_of_range("Too many values provided "
                                            "in comma initialization");
                }
                return this->ref(index / 3, index % 3);
            }
        public:
            CommaInitializerM(Matrix& m, double first)
                : CommaInitializer(m, first) {
                this->initialize(first);
            }
        };

        // Supports static compiler check for a nested or flat container.
        template<typename T, typename = void>
        struct _has_value_type : std::false_type {};
        template<typename T>
        struct _has_value_type<T,
            std::void_t<typename T::value_type>> : std::true_type {};

        // Supports static compiler check if containers have static size.
        template<typename T, typename = void>
        struct _has_static_size : std::false_type {};
        template<typename T>
        struct _has_static_size<T,
            std::integral_constant<std::size_t, std::tuple_size<T>::value>>
            : std::true_type {};

        // Compute the static size of a container. If a container doesn't
        // have a static size (e.g. std::vector) return 0.
        template<typename T>
        static constexpr std::size_t _get_static_size() {
            if constexpr (Matrix::_has_static_size<T>::value) {
                return std::tuple_size<T>::value;
            }
            return 0;
        }

        Matrix();

        // Constructs a Matrix from a flat container type with
        // underlying arithmetic type.
        template<typename Container,
                 typename ValueType = typename Container::value_type,
                 typename = std::enable_if_t<
                    !std::is_same_v<std::decay_t<Container>, Matrix> &&
                    std::is_arithmetic_v<ValueType>>>
        Matrix(const Container& c);

        // Constructs a Matrix from a 2-dimensional container type
        // with underlying arithmetic type.
        template<typename Container2D,
                 typename InnerContainer = typename Container2D::value_type,
                 typename ValueType = typename InnerContainer::value_type,
                 typename = std::enable_if_t<
                    !std::is_same_v<std::decay_t<Container2D>, Matrix> &&
                    Matrix::_has_value_type<InnerContainer>::value &&
                    std::is_arithmetic_v<ValueType>>>
        Matrix(const Container2D& c);

        // Constructs a Matrix from a 1-dimensional flat array of
        // arithmetic type. If T is not double then each value is
        // cast to a double type.
        template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
        Matrix(const T(&)[9]);

        // Constructs a Matrix from a 2-dimensional array of
        // arithmetic type. If T is not double then each value is
        // cast to a double type.
        template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
        Matrix(const T(&)[3][3]);

        Matrix(const std::initializer_list<double>&);
        Matrix(const std::initializer_list<std::initializer_list<double>>&);
        Matrix(const Matrix&);
        Matrix(Matrix&&) noexcept;
        ~Matrix();

        Matrix& operator=(const Matrix&);
        Matrix& operator=(Matrix&&) noexcept;

        double& operator()(std::size_t, std::size_t);
        const double& operator()(std::size_t, std::size_t) const;

        span_t<double> data() noexcept;
        span_t<const double> data() const noexcept;

        friend std::ostream& ::operator<<(std::ostream&, const Matrix&);
        CommaInitializerM operator<<(double);

        Matrix operator+(const Matrix&) const;
        Matrix& operator+=(const Matrix&) noexcept;
        Matrix operator-() const;
        Matrix operator-(const Matrix&) const;
        Matrix& operator-=(const Matrix&) noexcept;
        Matrix operator*(double) const;
        Matrix& operator*=(double) noexcept;
        Matrix operator*(const Matrix&) const;
        Matrix& operator*=(const Matrix&) noexcept;
        Vector operator*(const Vector&) const;
        Matrix operator/(double) const;
        Matrix& operator/=(double) noexcept;

        bool operator==(const Matrix&) const noexcept;
        bool operator!=(const Matrix&) const noexcept;
        bool compare_to(const Matrix&, std::size_t) const;

        double determinate() const noexcept;
        Matrix transpose() const;
        Matrix& transpose_inplace() noexcept;
        Matrix inverse() const;

        friend class Vector;

        static const Matrix IDENTITY;
    };

}   // namespace evspace

#include <vector.hpp>

namespace evspace {
    
    // std::decay is used here to ensure this isn't prefered for non-const
    // Matrix (i.e. this would be preferred to copy constructor for Matrix&).
    template<typename Container, typename ValueType, typename>
    inline Matrix::Matrix(const Container& c) {
        constexpr std::size_t static_size = Matrix::_get_static_size<Container>();

        // Allow 0 to pass through for dynamic size checking
        static_assert(static_size == 0 || static_size == MATRIX_ARRAY_LENGTH,
                      "Container must have exactly 9 elements");

        // Validate dynamic size types
        if constexpr (static_size == 0) {
            if (c.size() != MATRIX_ARRAY_LENGTH) {
                throw std::out_of_range("Container must have exactly 9 elements");
            }
        }

        this->m_data = new double[MATRIX_ARRAY_LENGTH];
        if constexpr (std::is_same_v<ValueType, double>) {
            std::memcpy(this->m_data, std::data(c), MATRIX_BYTE_SIZE);
        }
        else {
            for (int i = 0; i < 9; i++) {
                this->m_data[i] = static_cast<double>(c[i]);
            }
        }
    }

    template<typename Container2D, typename InnerContainer,
             typename ValueType, typename>
    inline Matrix::Matrix(const Container2D& c) {
        constexpr std::size_t outer_size = Matrix::_get_static_size<Container2D>();
        constexpr std::size_t inner_size = Matrix::_get_static_size<InnerContainer>();

        static_assert(outer_size == 0 || outer_size == MATRIX_ROW_LENGTH,
                      "Outer container must have exactly 3 rows");
        static_assert(inner_size == 0 || inner_size == MATRIX_ROW_LENGTH,
                      "Inner container must have exactly 3 columns");

        if (outer_size == 0) {
            if (c.size() != MATRIX_ROW_LENGTH) {
                throw std::out_of_range("outer container must have 3 rows");
            }
        }

        this->m_data = new double[MATRIX_ARRAY_LENGTH];
        for (int i = 0; i < MATRIX_ROW_LENGTH; i++) {
            if constexpr (inner_size == 0) {
                if (c[i].size() != MATRIX_ROW_LENGTH) {
                    throw std::out_of_range("Each row must have 3 elements");
                }
            }
            if constexpr (std::is_same_v<ValueType, double>) {
                std::memcpy(this->m_data + MATRIX_ROW_LENGTH * i, std::data(c[i]), MATRIX_ROW_BYTE_SIZE);
            }
            else {
                for (int j = 0; j < MATRIX_ROW_LENGTH; j++) {
                    MATRIX_ITEM_THIS(i, j) = static_cast<double>(c[i][j]);
                }
            }
        }
    }
    
    template<typename T, typename>
    inline
    Matrix::Matrix(const T (&arr)[9]) {
        this->m_data = new double[MATRIX_ARRAY_LENGTH];

        if constexpr (std::is_same_v<T, double>) {
            std::memcpy(this->m_data, arr, MATRIX_BYTE_SIZE);
        }
        else {
            for (int i = 0; i < MATRIX_ARRAY_LENGTH; i++) {
                this->m_data[i] = static_cast<double>(arr[i]);
            }
        }
    }

    template<typename T, typename>
    inline
    Matrix::Matrix(const T (&arr)[3][3]) {
        this->m_data = new double[MATRIX_ARRAY_LENGTH];

        if constexpr (std::is_same_v<T, double>) {
            std::memcpy(this->m_data, arr[0], MATRIX_ROW_BYTE_SIZE);
            std::memcpy(this->m_data + 3, arr[1], MATRIX_ROW_BYTE_SIZE);
            std::memcpy(this->m_data + 6, arr[2], MATRIX_ROW_BYTE_SIZE);
        }
        else {
            for (int i = 0; i < MATRIX_ROW_LENGTH; i++) {
                for (int j = 0; j < MATRIX_ROW_LENGTH; j++) {
                    MATRIX_ITEM_THIS(i, j) = static_cast<double>(arr[i][j]);
                }
            }
        }
    }

    inline Matrix::Matrix(const std::initializer_list<double>& list) {
        if (list.size() != MATRIX_ARRAY_LENGTH) {
            throw std::out_of_range("Initializer list must have exactly 9 elements");
        }

        this->m_data = new double[MATRIX_ARRAY_LENGTH];
        const double* data = std::data(list);
        for (int i = 0; i < MATRIX_ROW_LENGTH; i++) {
            std::memcpy(this->m_data + MATRIX_ROW_LENGTH * i, data + MATRIX_ROW_LENGTH * i, MATRIX_ROW_BYTE_SIZE);
        }
    }

    inline Matrix::Matrix(const std::initializer_list<std::initializer_list<double>>& list) {
        if (list.size() != MATRIX_ROW_LENGTH) {
            throw std::out_of_range("Initializer list must have exactly 3 rows");
        }

        this->m_data = new double[MATRIX_ARRAY_LENGTH];
        int i = 0;
        for (auto& row : list) {
            if (row.size() != MATRIX_ROW_LENGTH) {
                throw std::out_of_range("Each row must have exactly 3 columns");
            }
            std::memcpy(this->m_data + i, std::data(row), MATRIX_ROW_BYTE_SIZE);
            i += 3;
        }
    }

    inline Matrix::CommaInitializerM Matrix::operator<<(double value) {
        return Matrix::CommaInitializerM(*this, value);
    }
    
    inline Matrix::Matrix() {
        this->m_data = new double[MATRIX_ARRAY_LENGTH] {0.0};
    }

    inline Matrix::Matrix(const Matrix& cpy) {
        this->m_data = new double[MATRIX_ARRAY_LENGTH];
        std::memcpy(this->m_data, cpy.m_data, MATRIX_BYTE_SIZE);
    }

    inline Matrix::Matrix(Matrix&& move) noexcept {
        this->m_data = move.m_data;
        move.m_data = NULL;
    }

    inline Matrix::~Matrix() {
        delete[] this->m_data;
    }
    
    inline Matrix& Matrix::operator=(const Matrix& rhs) {
        std::memcpy(this->m_data, rhs.m_data, MATRIX_BYTE_SIZE);

        return *this;
    }

    inline Matrix& Matrix::operator=(Matrix&& rhs) noexcept {
        std::swap(this->m_data, rhs.m_data);

        return *this;
    }
    
    inline double&
    Matrix::operator()(std::size_t row, std::size_t col) {
        if (row > 2) {
            throw std::out_of_range("Matrix row index out of range");
        }
        if (col > 2) {
            throw std::out_of_range("Matrix column index out of range");
        }

        return MATRIX_ITEM_THIS(row, col);
    }

    inline const double&
    Matrix::operator()(std::size_t row, std::size_t col) const {
        if (row > 2) {
            throw std::out_of_range("Matrix row index out of range");
        }
        if (col > 2) {
            throw std::out_of_range("Matrix column index out of range");
        }

        return MATRIX_ITEM_THIS(row, col);
    }

    inline span_t<double> Matrix::data() noexcept {
        return span_t<double>(this->m_data, 9); 
    }

    inline span_t<const double> Matrix::data() const noexcept {
        return span_t<const double>(this->m_data, 9);
    }
    
    inline Matrix Matrix::operator+(const Matrix& rhs) const {
        Matrix result = Matrix();

        for (int i = 0; i < MATRIX_ARRAY_LENGTH; i++) {
            result.m_data[i] = this->m_data[i] + rhs.m_data[i];
        }

        return result;
    }

    inline Matrix& Matrix::operator+=(const Matrix& rhs) noexcept {
        for (int i = 0; i < MATRIX_ARRAY_LENGTH; i++) {
            this->m_data[i] += rhs.m_data[i];
        }

        return *this;
    }

    inline Matrix Matrix::operator-() const {
        Matrix result = Matrix();

        for (int i = 0; i < MATRIX_ARRAY_LENGTH; i++) {
            result.m_data[i] = -this->m_data[i];
        }

        return result;
    }

    inline Matrix Matrix::operator-(const Matrix& rhs) const {
        Matrix result = Matrix();

        for (int i = 0; i < MATRIX_ARRAY_LENGTH; i++) {
            result.m_data[i] = this->m_data[i] - rhs.m_data[i];
        }

        return result;
    }

    inline Matrix& Matrix::operator-=(const Matrix& rhs) noexcept {
        for (int i = 0; i < MATRIX_ARRAY_LENGTH; i++) {
            this->m_data[i] -= rhs.m_data[i];
        }

        return *this;
    }

    inline Matrix Matrix::operator*(double scalar) const {
        Matrix result = Matrix();

        for (int i = 0; i < MATRIX_ARRAY_LENGTH; i++) {
            result.m_data[i] = this->m_data[i] * scalar;
        }

        return result;
    }

    inline Matrix& Matrix::operator*=(double scalar) noexcept {
        for (int i = 0; i < MATRIX_ARRAY_LENGTH; i++) {
            this->m_data[i] *= scalar;
        }
        
        return *this;
    }

    inline Vector Matrix::operator*(const Vector& vec) const {
        Vector result;

        for (int i = 0; i < MATRIX_ROW_LENGTH; i++) {
            double sum = 0;
            for (int j = 0; j < MATRIX_ROW_LENGTH; j++) {
                sum = std::fma(MATRIX_ITEM_THIS(i, j), vec.m_data[j], sum);
            }
            result.m_data[i] = sum;
        }

        return result;
    }

    inline Matrix Matrix::operator*(const Matrix& rhs) const {
        Matrix result;

        for (int i = 0; i < MATRIX_ROW_LENGTH; i++) {
            for (int j = 0; j < MATRIX_ROW_LENGTH; j++) {
                double sum = 0;
                for (int k = 0; k < MATRIX_ROW_LENGTH; k++) {
                    sum = std::fma(MATRIX_ITEM_THIS(i, k), MATRIX_ITEM(rhs, k, j), sum);
                }
                MATRIX_ITEM(result, i, j) = sum;
            }
        }

        return result;
    }

    inline Matrix& Matrix::operator*=(const Matrix& rhs) noexcept {
        if (&rhs == this) {
            Matrix tmp(rhs);
            return (*this *= tmp);
        }
        
        double tmp[9];
        std::memcpy(tmp, this->m_data, MATRIX_BYTE_SIZE);

        for (int i = 0; i < MATRIX_ROW_LENGTH; i++) {
            for (int j = 0; j < MATRIX_ROW_LENGTH; j++) {
                double sum = 0;
                for (int k = 0; k < MATRIX_ROW_LENGTH; k++) {
                    sum = std::fma(tmp[i * MATRIX_ROW_LENGTH + k],
                                   MATRIX_ITEM(rhs, k, j), sum);
                }
                MATRIX_ITEM_THIS(i, j) = sum;
            }
        }

        return *this;
    }

    inline Matrix Matrix::operator/(double scalar) const {
        Matrix matrix = Matrix();

        for (int i = 0; i < MATRIX_ARRAY_LENGTH; i++) {
            matrix.m_data[i] = this->m_data[i] / scalar;
        }

        return matrix;
    }

    inline Matrix& Matrix::operator/=(double scalar) noexcept {
        for (int i = 0; i < MATRIX_ARRAY_LENGTH; i++) {
            this->m_data[i] /= scalar;
        }

        return *this;
    }

    inline bool Matrix::compare_to(const Matrix& rhs, std::size_t max_ulps) const
    {
        for (int i = 0; i < MATRIX_ARRAY_LENGTH; i++)
        {
            if (!_double_almost_equal(this->m_data[i], rhs.m_data[i], max_ulps))
            {
                return false;
            }
        }

        return true;
    }

    inline bool Matrix::operator==(const Matrix& rhs) const noexcept {
        return this->compare_to(rhs, _EVSPACE_DEFAULT_ULP_MAXIMUM);
    }

    inline bool Matrix::operator!=(const Matrix& rhs) const noexcept {
        return !(*this == rhs);
    }

    inline double Matrix::determinate() const noexcept {
        double result = 0;

        result += MATRIX_ITEM_THIS(0, 0) * (MATRIX_ITEM_THIS(1, 1) * MATRIX_ITEM_THIS(2, 2) -
                  MATRIX_ITEM_THIS(1, 2) * MATRIX_ITEM_THIS(2, 1));
        result -= MATRIX_ITEM_THIS(0, 1) * (MATRIX_ITEM_THIS(1, 0) * MATRIX_ITEM_THIS(2, 2) -
                  MATRIX_ITEM_THIS(1, 2) * MATRIX_ITEM_THIS(2, 0));
        result += MATRIX_ITEM_THIS(0, 2) * (MATRIX_ITEM_THIS(1, 0) * MATRIX_ITEM_THIS(2, 1) -
                  MATRIX_ITEM_THIS(1, 1) * MATRIX_ITEM_THIS(2, 0));

        return result;
    }

    inline Matrix Matrix::transpose() const {
        return Matrix({
            { MATRIX_ITEM_THIS(0, 0), MATRIX_ITEM_THIS(1, 0), MATRIX_ITEM_THIS(2, 0) },
            { MATRIX_ITEM_THIS(0, 1), MATRIX_ITEM_THIS(1, 1), MATRIX_ITEM_THIS(2, 1) },
            { MATRIX_ITEM_THIS(0, 2), MATRIX_ITEM_THIS(1, 2), MATRIX_ITEM_THIS(2, 2) },
        });
    }

    inline Matrix& Matrix::transpose_inplace() noexcept {
        double tmp{};

        tmp = this->m_data[1];
        this->m_data[1] = this->m_data[3];
        this->m_data[3] = tmp;

        tmp = this->m_data[2];
        this->m_data[2] = this->m_data[6];
        this->m_data[6] = tmp;

        tmp = this->m_data[5];
        this->m_data[5] = this->m_data[7];
        this->m_data[7] = tmp;

        return *this;
    }

    inline Matrix Matrix::inverse() const {
        double det = this->determinate();
        if (det == 0) {
            throw std::runtime_error("Unable to invert singular matrix");
        }

        Matrix result = Matrix();

        result.m_data[0] = (MATRIX_ITEM_THIS(1, 1) * MATRIX_ITEM_THIS(2, 2) -
                            MATRIX_ITEM_THIS(1, 2) * MATRIX_ITEM_THIS(2, 1)) / det;
        result.m_data[1] = -(MATRIX_ITEM_THIS(1, 0) * MATRIX_ITEM_THIS(2, 2) -
                             MATRIX_ITEM_THIS(1, 2) * MATRIX_ITEM_THIS(2, 0)) / det;
        result.m_data[2] = (MATRIX_ITEM_THIS(1, 0) * MATRIX_ITEM_THIS(2, 1) -
                            MATRIX_ITEM_THIS(1, 2) * MATRIX_ITEM_THIS(2, 0)) / det;
        result.m_data[3] = -(MATRIX_ITEM_THIS(0, 1) * MATRIX_ITEM_THIS(2, 2) -
                             MATRIX_ITEM_THIS(0, 2) * MATRIX_ITEM_THIS(2, 1)) / det;
        result.m_data[4] = (MATRIX_ITEM_THIS(0, 0) * MATRIX_ITEM_THIS(2, 2) -
                            MATRIX_ITEM_THIS(0, 2) * MATRIX_ITEM_THIS(2, 0)) / det;
        result.m_data[5] = -(MATRIX_ITEM_THIS(0, 0) * MATRIX_ITEM_THIS(2, 1) -
                             MATRIX_ITEM_THIS(0, 1) * MATRIX_ITEM_THIS(2, 0)) / det;
        result.m_data[6] = (MATRIX_ITEM_THIS(0, 1) * MATRIX_ITEM_THIS(1, 2) -
                            MATRIX_ITEM_THIS(0, 2) * MATRIX_ITEM_THIS(1, 1)) / det;
        result.m_data[7] = -(MATRIX_ITEM_THIS(0, 0) * MATRIX_ITEM_THIS(1, 2) -
                             MATRIX_ITEM_THIS(0, 2) * MATRIX_ITEM_THIS(1, 0)) / det;
        result.m_data[8] = (MATRIX_ITEM_THIS(0, 0) * MATRIX_ITEM_THIS(1, 1) -
                            MATRIX_ITEM_THIS(0, 1) * MATRIX_ITEM_THIS(1, 0)) / det;
        
        result.transpose_inplace();
        return result;
    }

    inline constexpr std::size_t
    Matrix::matrix_index(std::size_t r, std::size_t c) noexcept {
        return r * 3 + c;
    }

    inline const Matrix Matrix::IDENTITY = Matrix({ {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0} });

} // namespace evspace

inline std::ostream& operator<<(std::ostream& out, const evspace::Matrix& matrix) {
    out << "[ [ "
        << MATRIX_ITEM(matrix, 0, 0) << ", " << MATRIX_ITEM(matrix, 0, 1) << ", "
        << MATRIX_ITEM(matrix, 0, 2) << " ], [ "
        << MATRIX_ITEM(matrix, 1, 0) << ", " << MATRIX_ITEM(matrix, 1, 1) << ", "
        << MATRIX_ITEM(matrix, 1, 2) << " ], [ "
        << MATRIX_ITEM(matrix, 2, 0) << ", " << MATRIX_ITEM(matrix, 2, 1) << ", "
        << MATRIX_ITEM(matrix, 2, 2) << " ] ]";
    return out;
}

#undef MATRIX_ARRAY_LENGTH
#undef MATRIX_ROW_LENGTH
#undef MATRIX_BYTE_SIZE
#undef MATRIX_ROW_BYTE_SIZE

#endif // _EVSPACE_MATRIX_H_
