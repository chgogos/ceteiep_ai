:- use_module(library(clpfd)).

find4(Vs) :-
    length(Vs,4),
    Vs ins 1..3 \/ 7..9,
    all_different(Vs),
    chain(Vs, #>),
    label(Vs),
    write(Vs),nl,
    fail.