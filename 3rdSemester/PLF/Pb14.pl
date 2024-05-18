rev([],R,R).
rev([H|T],R,RR):-
    rev(T,[H|R],RR).

append([],L2,L2).
append([H1|T1],L2,[H1|R]):-
    append(T1,L2,R).

lin([],[]).
lin([H|T], R):-
    is_list(H),
    !,
    lin(H,R1),
    lin(T,R2),
    append(R1,R2,R).
lin([H|T], [H|R]):-
    lin(T,R).