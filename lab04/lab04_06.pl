friends(X,Y):-
        follows(X,Y),
        follows(Y,X).

male_friends(X,Y):-
        friends(X,Y),
        male(Y).

follows(ilias, petros).
follows(petros,ilias).
follows(petros, demos).
follows(demos,petros).
follows(petros,sofia).

male(ilias).
male(demos).

% trace.
% male_friends(petros,A).
