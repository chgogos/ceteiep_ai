%% triska_example2_1

:- use_module(library(clpfd)).

solve(Vs) :- Vs = [A,B,C,D],
Vs ins 0..711,
A*B*C*D #= 711*100^3,
A+B+C+D #= 711,
A#>=B, B#>=C, C#>=D,
labeling([ff],Vs).