
return_prime([], []).
return_prime([H|T], [H|R]):-
    is_prime(H, 3, Result),
    Result =:= 1,
    return_prime(T, R).
return_prime([H|T], R):-
    is_prime(H, 3, Result),
    Result =:= 0,
    return_prime(T, R).

is_prime(X, _,  Result):- 
    X mod 2 =:= 0,
    X =\= 2,
    Result is 0, !.
is_prime(X, _, Result):-
    X =:= 1,
    Result is 0, !.
is_prime(X, D, Result):-
    D1 is D*D,
    D1 > X,
    Result is 1, !.
is_prime(X, D, Result):-
    X mod D =:= 0,
    Result is 0, !.
is_prime(X, D, Result1):-
    X mod D =\= 0,
    D1 is D + 2,
    is_prime(X, D1, Result1).

