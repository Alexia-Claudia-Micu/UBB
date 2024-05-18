sub([],[]).
sub([H|T],[H|R]):-
    sub(T,R).
sub([_|T],R):-
	sub(T,R).

insert(E,L,[E|L]).
insert(E,[H|T],[H|R]):-
    insert(E,T,R).

arr([H|_],1,[H]).
arr([H|T],K,R):-
    K > 1,
    K1 is K-1,
    arr(T,K1,RR),
    insert(H,RR,R).
arr([_|T],K,R):-
    arr(T,K,R).

perm([],[]).
perm([H|T],R):-
    perm(T,RR),
    insert(H,RR,R).

comb([H|_],1,[H]).
comb([_|T], K, R):-
    comb(T,K,R).
comb([H|T], K,[H|R]):-
    K > 1,
    K1 is K-1,
    comb(T,K1,R).