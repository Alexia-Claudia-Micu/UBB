insert(X,L,[X|L]).
insert(X,[H|T],[H|R]):-
    insert(X,T,R).

perm([],[]).
perm([H|T],R):-
    perm(T, RR),
    insert(H,RR,R).

diff(X,Y, R):-
   X > Y,
   !,
   R is X - Y.
diff(X,Y,R):-
   R is Y-X.

check_diff([H1,H2]):-
    diff(H1,H2,R),
    R >= 2.
check_diff([H1,H2|T]):-
    diff(H1,H2,R),
    R >= 2,
    check_diff([H2|T]).

sol(L,R):-
    perm(L,R),
    check_diff(R).

create_list(N,I,[]):-
    I >= N,
    !.
create_list(N,I,[I1|R]):-
    I1 is I+1,
    create_list(N,I1,R).

solve(N,R):-
    create_list(N,0,L),
    findall(RR, sol(L,RR), R).