fib_mult(A-B, C-D, X-Y) :-
    X is A * (C + D) + B * C,
    Y is A * C + B * D.

:- use_module(power).

fib(N, F) :-
    (   N == 0
    ->  F = 0
    ;   power_semigroup(1-0, N, fib_mult, F-_)
    ).
