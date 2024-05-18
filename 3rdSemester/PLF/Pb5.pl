sumDistinct(0,_,[]).
sumDistinct(N,C,[C|R]):-
    C =< N,
    N1 is N-C,
    C1 is C+1,
    sumDistinct(N1,C!,R).
sumDistinct(N,C,R):-
    C<N,
    C1 is C +1,
    summDistinct(N,C1,R).