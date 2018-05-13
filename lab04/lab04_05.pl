%% Ερώτημα 1
male(petros).
male(ilias).
male(demos).
male(nikos).
female(sofia).
female(helen).
female(katerina).

%% Ερώτημα 2
follows(ilias, petros).
follows(petros,ilias).
follows(petros, demos).
follows(petros,sofia).
follows(nikos, petros).
follows(nikos, ilias).
follows(demos, sofia).
follows(demos,petros).
follows(ilias,katerina).
follows(katerina,petros).
follows(sofia,helen).
follows(helen,sofia).

%% Ερώτημα 3
friends(X,Y):-
        follows(X,Y),
        follows(Y,X).

%% Ερώτημα 4
male_friends(X,Y):-
        friends(X,Y),
        male(Y).

female_friends(X,Y):-
        friends(X,Y),
        female(Y).
        
%% Ερώτημα 5
friend_same_gender(X,Y):-
 female(X),
 friends(X,Y),
 female(Y).

friend_same_gender(X,Y):-
 male(X),
 friends(X,Y),
 male(Y).

%% Ερώτημα 6
recommend_common_friends(X,Y):-
 friends(X,Z),
 friends(Z,Y),
 X \= Y.
 