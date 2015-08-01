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
