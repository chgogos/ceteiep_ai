member2(X,[X|_]).
member2(X,[_|T]) :- member2(X,T).