is_set([],1).
is_set([H|T],Result):-
    is_in_list(T,H),
    Result is 0.
is_set([_|T],Result):-
    is_set(T,Result).
    
is_in_list([H|_],X):- 
    H =:= X.
is_in_list([_|T],X):- is_in_list(T,X).