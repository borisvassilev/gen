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

#include <iostream>
#include <sstream>
#include <gmpxx.h>
#include "power.hpp"

#define Integer typename
template <Integer I>
std::pair<I, I>
fib_mul(const std::pair<I, I> a, const std::pair<I, I> b)
{
    return std::pair<I, I>(
        a.first * (b.first + b.second) + a.second * b.first,
        a.first * b.first + a.second * b.second);
}

typedef mpz_class I;
I fib(int n)
{
    if (n == 0) return I(0);
    std::pair<I, I> a(1, 0);
    return power_semigroup(a, n, fib_mul<I>).first;
}

int main(int argc, char* argv[])
{
    for (int i = 1; i < argc; ++i) {
        std::istringstream a(argv[i]);
        int n;
        if (a >> n && n >= 0) {
            std::cout << n << ':' << fib(n) << std::endl;
        }
    }
}
