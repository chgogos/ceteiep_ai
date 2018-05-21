:- use_module(library(clpfd)).

test1(X,Y):-
           X in 0..10,
           Y in 4..8,
           X #> Y.
test1 :-
      test1(X,Y),
      label([X,Y]),
      write([X,Y]),nl,fail.

test2(X,Y):-
           X in 0..5,
           Y in 4..8,
           X #> Y.
           

% ?- test1(X,Y).
% X in 5..10,
% Y#=<X+ -1,
% Y in 4..8.

% ?- test2(X,Y).
% X = 5,
% Y = 4.