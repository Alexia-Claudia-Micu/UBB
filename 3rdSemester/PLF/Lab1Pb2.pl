remove_occ([],_,_,[]).
remove_occ([H|T],E,N,TR):-
    E =:= H,
    N > 0,
    N1 is N-1,
    remove_occ(T,E,N1,TR).
remove_occ([H|T],E,N,[H|TR]):-
    E =:= H,
    N =:= 0,
	remove_occ(T,E,N,TR).
remove_occ([H|T],E,N,[H|TR]):-
    E =\= H,
	remove_occ(T,E,N,TR).