sum([],0).
sum([H|T],S) :-
    sum(T,S1),
    S is S1+H.

prod([],1).
prod([H|T],P):-
    prod(T,P1),
    P is P1*H.