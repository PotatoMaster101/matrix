////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Simple mathematical matrix in C++17.
//
// Author: PotatoMaster101
// Date:   11/04/2019
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <utility>      // std::pair
#include <cstddef>      // std::size_t
#include <array>        // std::array
#include <functional>   // std::plus, std::minus

// Matrix type.
template <class T, std::size_t R, std::size_t C>
class matrix {
public:
    // Member types.
    using value_type = T;
    using size_type = std::size_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using iterator = typename std::array<T, C>::iterator;
    using const_iterator = typename std::array<T, C>::const_iterator;
    using index = std::pair<size_type, size_type>;

    // Constructors.
    constexpr matrix() : mtx_() { static_assert(R != 0 && C != 0, "size can not be 0"); }
    constexpr matrix(const_reference val) : matrix() { fill(val); }

    // Rule of five.
    constexpr matrix(const matrix& mtx) = default;
    constexpr matrix& operator=(const matrix& mtx) = default;
    constexpr matrix(matrix&& mtx) = default;
    constexpr matrix& operator=(matrix&& mtx) = default;
    ~matrix() = default;

    // Iterators.
    constexpr iterator begin() noexcept { return mtx_.begin(); }
    constexpr const_iterator cbegin() const noexcept { return mtx_.cbegin(); }
    constexpr iterator end() noexcept { return mtx_.end(); }
    constexpr const_iterator cend() const noexcept { return mtx_.cend(); }

    // Dimension access.
    constexpr size_type rows() const noexcept { return R; }
    constexpr size_type cols() const noexcept { return C; }

    // Element access.
    constexpr reference operator[](const index& i) noexcept { return mtx_[i.first][i.second]; }
    constexpr const_reference operator[](const index& i) const noexcept { return mtx_[i.first][i.second]; }

    // Row access.
    constexpr std::array<T, C>& operator[](size_type r) noexcept { return mtx_[r]; }
    constexpr const std::array<T, C>& operator[](size_type r) const noexcept { return mtx_[r]; }

    // Arithmetics.
    constexpr matrix& operator+=(const matrix& rhs) { operation(rhs, std::plus<T>{}); return *this; }
    constexpr matrix& operator-=(const matrix& rhs) { operation(rhs, std::minus<T>{}); return *this; }
    constexpr matrix& operator*=(const matrix& rhs) { /* TODO strassen */ return *this; }
    constexpr friend matrix operator+(matrix lhs, const matrix& rhs) { return lhs += rhs; }
    constexpr friend matrix operator-(matrix lhs, const matrix& rhs) { return lhs -= rhs; }
    constexpr friend matrix operator*(matrix lhs, const matrix& rhs) { return lhs *= rhs; }

    // Fills the current matrix with a value.
    constexpr void fill(const_reference val) noexcept {
        for (auto& row : mtx_)
            for (auto& col : row)
                col = val;
    }

private:
    // Internal matrix.
    std::array<std::array<T, C>, R> mtx_;

    // Performs operation on the current matrix.
    template <class O>
    constexpr void operation(const matrix& rhs, O opr) {
        for (size_type r = 0; r < R; r++)
            for (size_type c = 0; c < C; c++)
                mtx_[r][c] = opr(mtx_[r][c], rhs[r][c]);
    }
};

// Matrix types.
template <class T>
using matrix2 = matrix<T, 2, 2>;
template <class T>
using matrix3 = matrix<T, 3, 3>;
template <class T>
using matrix4 = matrix<T, 4, 4>;
template <class T>
using matrix5 = matrix<T, 5, 5>;

#endif
