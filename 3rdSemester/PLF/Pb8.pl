%permutations - the absolute value of difference <=3
% [2,7,5] = [[2,5,7],[7,5,2]]

insert(E,L,[E|L]).
insert(E,[H|T],[H|R]):-
    insert(E,T,R).

perm([],[]).
perm([H|T], R):-
	perm(T,RR),
	insert(H,RR,R).

abs(A,B,R):-
    A >= B,
    !,
    R is A - B.
abs(A,B,R):-
    R is B-A.

check_abs([H1,H2]):-
    abs(H1,H2,R),
    R < 4.
check_abs([H1,H2|T]):-
    check_abs([H2|T]),
    abs(H1,H2,R),
    R < 4.

sol(L,R):-
    perm(L,R),
    check_abs(R).

make_list(N,I,[]):-
    I >= N,!.
make_list(N, I,[I1|R]):-
    I1 is I +1,
    make_list(N, I1, R).

all_sol(N,R):-
    make_list(N,0,L),
    findall(RR, sol(L,RR),R).