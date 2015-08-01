#include <iostream>
#include <algorithm>
#include <vector>

#define Integer typename
#define RandomAccessIterator typename

template <RandomAccessIterator I, Integer N>
void mark_sieve(I first, I last, N factor)
{
    // assert(first != last)
    *first = false;
    while (last > factor + first) {
        first += factor;
        *first = false;
    }
}

template <RandomAccessIterator I, Integer N>
void sift(I first, N n)
{
    I last = first + n;
    std::fill(first, last, true);
    N i(0);
    N index_square(3);
    N factor(3);
    while (index_square < n) {
        // invariant: index_square = 2i^3 + 6i + 3,
        //            factor = 2i + 3
        if (first[i]) mark_sieve(first + index_square, last, factor);
        ++i;
        index_square += factor;
        factor += N(2);
        index_square += factor;
    }
}

template <RandomAccessIterator I>
int prime(I first, I pos) { return 2 * (pos - first) + 3; }

int main(int argc, char* argv[])
{
    std::vector<bool> sieve(50);
    sift(sieve.begin(), sieve.size());
    // all primes
    for (auto i = sieve.begin(); i != sieve.end(); ++i) {
        if(*i) std::cout << prime(sieve.begin(), i) << std::endl;
    }
    return 0;
}
