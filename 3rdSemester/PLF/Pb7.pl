solve_p3(N,[0|R]):-
    generate(N, 0, 1, R).
solve_p3(N,[-1|R]):-
    generate(N, -1, 1, R).
solve_p3(N,[1|R]):-
    generate(N, 1, 1, R).

generate( N, _, I, [0]):-
    I =:= 2*N, !.

generate(N,Prev, I, [1|R]):-
    Prev =:= 0,
    I1 = I + 1, 
    generate(N, 1, I1, R).
generate(N,Prev, I, [-1|R]):-
    Prev =:= 0,
    I1 = I + 1, 
    generate(N, -1, I1, R).


generate(N,Prev, I, [0|R]):-
    I =\= 2*N-1,
    Prev =:= 1,
    I1 = I + 1, 
    generate(N, 0, I1, R).
generate(N,Prev, I, [-1|R]):-
    Prev =:= 1,
    I1 = I + 1, 
    generate(N, -1, I1, R).


generate(N,Prev, I, [0|R]):-
        I =\= 2*N-1,

    Prev =:= -1,
    I1 = I + 1, 
    generate(N, 0, I1, R).
generate(N,Prev, I, [1|R]):-
    Prev =:= -1,
    I1 = I + 1, 
    generate(N, 1, I1, R).