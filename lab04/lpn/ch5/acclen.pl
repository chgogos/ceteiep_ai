acclen([],Acc,Length):-
    Length = Acc.

acclen([_|L],OldAcc,Length):-
    NewAcc is OldAcc + 1,
    acclen(L,NewAcc,Length).

len2(List,Length):-
    acclen(List,0,Length).

%% ?-acclen([a,b,c],0,Len).
%% Len=3.

%% ?-len2([a,b,c],Len).
%% Len=3.