:- use_module(library(clpfd)).

find4(Vs) :-
    length(Vs,4),
    Vs ins 1..3 \/ 7..9,
    all_different(Vs),
    Vs = [X,_,_,Y],
    X #> Y,
    label(Vs),
    write(Vs),nl,
    fail.