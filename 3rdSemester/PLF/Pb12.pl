insert(E,L,[E|L]).
insert(E,[H|T], [H|R]):-
    insert(E,T,R).

arr([H|_],1,[H]).
arr([_|T],K,R):-
    arr(T,K,R).
arr([H|T],K,R):-
    K > 1,
    K1 is K-1,
    arr(T,K1,RR),
    insert(H,RR,R).
   
prod([],1).
prod([H|T],R):-
    prod(T,RR),
    R is RR*H.

check_prod(L,P):-
    prod(L,R),
    R =:= P.

sol(L,K,P,R):-
    arr(L,K,R),
    check_prod(R,P).

all_sol(L,K,P,R):-
    findall(RR,sol(L,K,P,RR),R).