#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <string>

#define ForwardIterator typename
template <ForwardIterator I>
size_t max_str_len(I first, I last)
{
    size_t max(0);
    while (first < last) {
        std::ostringstream oss;
        oss << *first;
        size_t l(oss.str().length());
        if (l > max) max = l;
        ++first;
    }
    return max;
}

template <typename T> struct Matrix;

// Maximum width of element
template <typename T>
size_t max_element_width(const Matrix<T>& m)
{ return max_str_len(cbegin(m.vals), cend(m.vals)); }

template <>
size_t max_element_width<bool>(const Matrix<bool>& m)
{ return 1; }


template <typename T>
struct Matrix {
    size_t nrow;
    size_t ncol;
    std::vector<T> vals;

    Matrix(size_t r, size_t c) : nrow(r), ncol(c), vals(nrow * ncol) {}
    Matrix(size_t r, size_t c, std::vector<T> v) :
        nrow(r), ncol(c), vals(v) {}

    const size_t size() const { return vals.size(); }

    friend std::ostream&
    operator<< (std::ostream& os, const Matrix& m)
    {
        const size_t w = 1 + max_element_width<T>(m);
        size_t r = m.print_row(os, 0, w);
        while (r < m.size()) {
            os << '\n';
            r = m.print_row(os, r, w);
        }
        return os;
    }

private:
    size_t print_row(std::ostream& os, size_t first, const size_t w) const
    {
        size_t last = first + ncol;
        while (first < last) os << std::setw(w) << vals[first++];
        return first;
    }
};

#define AdditiveOperation typename
#define MultiplicativeOperation typename

template <typename T,
          AdditiveOperation AddOp,
          MultiplicativeOperation MultOp>
Matrix<T> multiply(Matrix<T> const& a,
                   Matrix<T> const& b,
                   AddOp addop,
                   MultOp multop)
{
    Matrix<T> m(a.nrow, b.ncol);

    for (size_t mi = 0; mi < m.size(); ++mi) {
        size_t row = mi / m.ncol;
        size_t bi = mi % m.ncol;
        size_t ai_first = row * a.ncol;
        const size_t ai_last = ai_first + a.ncol;

        m.vals[mi] = multop(a.vals[ai_first],
                            b.vals[bi]);
        ++ai_first;
        bi += b.ncol;

        while (ai_first < ai_last) {
            m.vals[mi] = addop(m.vals[mi],
                               multop(a.vals[ai_first],
                                      b.vals[bi]));
            ++ai_first;
            bi += b.ncol;
        }
    }

    return m;
}

template <typename T>
Matrix<T> multiply(Matrix<T> const& a, Matrix<T> const& b)
{ return multiply(a, b, std::plus<T>(), std::multiplies<T>()); }


#endif // MATRIX_HPP
