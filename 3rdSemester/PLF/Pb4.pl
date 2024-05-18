sumDiv(N,D,Sum):-D > N div 2, Sum is 0.
sumDiv(N,D,Sum):-D =< N div 2, N mod D =:= 0, D1 is D+1, sumDiv(N, D1, Sum1), Sum is D + Sum1.
sumDiv(N,D,Sum):-D =< N div 2, N mod D =\= 0, D1 is D+1, sumDiv(N, D1, Sum).