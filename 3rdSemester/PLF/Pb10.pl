sort_all([],[]).
sort_all([H|T], [HR|TR]):- 
    bubble_sort(H,0, HR),
    sort_all(T, TR).


bubble_sort(L,N,Result):- get_length(L,NR),
    						N = NR,
    						sorty(L, Result).
bubble_sort(L,N,Result):- get_length(L,NR),
    						N < NR,
    						sorty(L, R),
    						N1 is N+1,
    						bubble_sort(R, N1, Result).
bubble_sort(X,_,X).

sorty([],[]).
sorty([H|T],[H]):- T = [].
sorty([H|T],[HR|TRR]):- T \= [],
    					comparey(H,T,[HR|TR]),
    					sorty(TR, TRR).
    			

comparey(X,[H|T], [H|TR]):- X > H,
					attach(X,T,TR).
comparey(X,[H|T], [X|TR]):- X =< H,
					attach(H,T,TR).

attach(X,T,[X|T]).

get_length([], 0).
get_length([_|T],R):- get_length(T,R1), R is R1+1.