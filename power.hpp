#ifndef POWER_HPP

#include <functional>

#define Integer typename
#define Regular typename

#define NoncommutativeAdditiveMonoid typename
#define MultiplicativeMonoid typename
#define AdditiveGroup typename
#define MultiplicativeGroup typename

#define SemigroupOperation typename
#define MonoidOperation typename
#define GroupOperation typename

template <Integer N>
bool odd(N n)
{ return bool(n & 0x1); }

template <Integer N>
N half(N n)
{ return n >> 1; }

template <Regular A, Integer N, SemigroupOperation Op>
// requires (Domain<Op, A>)
A power_accumulate_semigroup(A r, A a, N n, Op op)
{
    // precondition(n >= 0);
    if (n == 0) return r;
    while (true) {
        if (odd(n)) {
            r = op(r, a);
            if (n == 1) return r;
        }
        n = half(n);
        a = op(a, a);
    }
}

template <Regular A, Integer N, SemigroupOperation Op>
// requires (Domain<Op, A>)
A power_semigroup(A a, N n, Op op)
{
    // precondition(n > 0);
    while (!odd(n)) {
        a = op(a, a);
        n = half(n);
    }
    if (n == 1) return a;
    return power_accumulate_semigroup(a, op(a, a), half(n - 1), op);
}

template <NoncommutativeAdditiveMonoid T>
T identity_element(std::plus<T>)
{ return T(0); }

template <MultiplicativeMonoid T>
T identity_element(std::multiplies<T>)
{ return T(1); }

template <Regular A, Integer N, MonoidOperation Op>
// requires (Domain<Op, A>)
A power_monoid(A a, N n, Op op)
{
    // precondition(n >= 0);
    if (n == 0) return identity_element(op);
    return power_semigroup(a, n, op);
}

template <AdditiveGroup T>
std::negate<T> inverse_operation(std::plus<T>)
{ return std::negate<T>(); }

template <MultiplicativeGroup T>
struct reciprocal {
    T operator()(const T& x) const
    { return T(1) / x; }
};

template <MultiplicativeGroup T>
reciprocal<T> inverse_operation(std::multiplies<T>)
{ return reciprocal<T>(); }

template <Regular A, Integer N, GroupOperation Op>
// requires (Domain<Op, A>)
A power_group(A a, N n, Op op)
{
    if (n < 0) {
        n = -n;
        a = inverse_operation(op)(a);
    }
    return power_monoid(a, n, op);
}

#endif // POWER_HPP
