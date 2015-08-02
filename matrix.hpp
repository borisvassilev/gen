// Copyright 2015 Boris Vassilev
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
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

template <typename T>
bool str_to_val(const std::string& s, T& v)
{
    std::istringstream is(s);
    if (is >> v) return true;
    return false;
}
template <> bool str_to_val<std::string>(const std::string& s,
                                         std::string& v)
{
    v = s;
    return true;
}

template <typename T>
Matrix<T> from_input(std::istream& is, const char fs, const char rs)
{
    std::vector<size_t> ll(0);
    std::vector<T> vals(0);

    std::string line;
    while (std::getline(is, line, rs)) {
        std::istringstream linestream(line);
        std::string val_str;
        size_t fn(0);
        while (std::getline(linestream, val_str, fs)) {
            T v;
            if (str_to_val<T>(val_str, v)) {
                vals.push_back(v);
                ++fn;
            }
        }
        ll.push_back(fn);
    }

    size_t nc = ll.front();
    if (all_of(std::next(cbegin(ll)), cend(ll),
               std::bind(std::equal_to<size_t>(),
                         std::placeholders::_1,
                         nc)))
        return Matrix<T>(ll.size(), nc, vals);
    else
        return Matrix<T>(0, 0);
}


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
