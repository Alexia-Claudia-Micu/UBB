% B. Să se scrie un program PROLOG care generează lista aranjamentelor de k elemente
%    dintr-o listă de numere întregi, pentru care produsul elementelor e mai mic decât
%    o valoare V dată. Se vor scrie modelele matematice și modelele de flux pentru predicatele folosite.
%    
% Exemplu- pentru lista [1, 2, 3], k=2 și V=7 ⇒ [[1,2],[2,1],[1,3],[3,1],[2,3],[3,2]] (nu neapărat în această ordine)

insert(E,L,[E|L]).
insert(E,[H|T],[H|R]):-
    insert(E,T,R).

arr([H|_], 1, [H]).
arr([_|T], K, R):-
    arr(T,K,R).
arr([H|T], K, R):-
    K > 1,
    K1 is K -1,
    arr(T,K1,RR),
    insert(H,RR,R).

prod([],1).
prod([H|T], R):-
    prod(T,RR),
    R is RR*H.

check_prod(L,V):-
    prod(L,R),
    V1 is V + 1,
    R < V1.

sol(L,K,V,R):-
    arr(L,K,R),
    check_prod(R,V).

all_sol(L,K,V,R):-
   findall(RR, sol(L,K,V,RR), R).
