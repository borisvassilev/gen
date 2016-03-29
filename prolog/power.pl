:- module(power, [power_semigroup/4,
                  power_monoid/4,
                  power_group/4]).

odd(N) :-
    N /\ 0x1 =:= 1.

half(N, Half) :-
    Half is N >> 1.

power_accumulate_semigroup(R, A, N, Op, P) :-
    (   N == 0
    ->  P = R
    ;   power_accumulate_semigroup_1(R, A, N, Op, P)
    ).

power_accumulate_semigroup_1(R, A, N, Op, P) :-
    (   odd(N)
    ->  power_accumulate_semigroup_oddn(R, A, N, Op, P)
    ;   power_accumulate_semigroup_anyn(R, A, N, Op, P)
    ).

power_accumulate_semigroup_oddn(R, A, N, Op, P) :-
    call(Op, R, A, R1),
    (   N == 1
    ->  P = R1
    ;   power_accumulate_semigroup_anyn(R1, A, N, Op, P)
    ).

power_accumulate_semigroup_anyn(R, A, N, Op, P) :-
    half(N, N1),
    call(Op, A, A, A1),
    power_accumulate_semigroup_1(R, A1, N1, Op, P).

power_semigroup(A, N, Op, P) :-
    must_be(positive_integer, N),
    power_semigroup_(A, N, Op, P).

power_semigroup_(A, N, Op, P) :-
    power_semigroup_evenn(A, N, Op, A0, N0),
    (   N0 == 1
    ->  P = A0
    ;   call(Op, A0, A0, A1),
        half(N0 - 1, N1),
        power_accumulate_semigroup(A0, A1, N1, Op, P)
    ).

power_semigroup_evenn(A, N, Op, A1, N1) :-
    (   odd(N)
    ->  A = A1,
        N = N1
    ;   call(Op, A, A, A0),
        half(N, N0),
        power_semigroup_evenn(A0, N0, Op, A1, N1)
    ).

power_monoid(A, N, Op, P) :-
    must_be(nonneg, N),
    power_monoid_(A, N, Op, P).

power_monoid_(A, N, Op, P) :-
    (   N == 0
    ->  identity_element(Op, P)
    ;   power_semigroup_(A, N, Op, P)
    ).

power_group(A, N, Op, P) :-
    must_be(integer, N),
    power_group_(A, N, Op, P).

power_group_(A, N, Op, P) :-
    (   N < 0
    ->  N1 is -N,
        inverse_operation(Op, Op1),
        call(Op1, A, A1)
    ;   N1 = N,
        A1 = A
    ),
    power_monoid_(A1, N1, Op, P).

identity_element(add, 0).
identity_element(mult, 1).

inverse_operation(add, negate).
inverse_operation(mult, reciprocal).

add(X, Y, R) :- R is X + Y.
mult(X, Y, R) :- R is X * Y.

negate(X, R) :- R is -X.
reciprocal(X, R) :- R is 1/X.
