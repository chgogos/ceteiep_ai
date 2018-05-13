hold_party(X):-
        birthday(X),
        happy(X).
birthday(tom).
birthday(fred).
birthday(helen).
happy(mary).
happy(jane).
happy(helen).

% Ερώτημα Α
% ?- birthday(jane).
% false

% ?- hold_party(X).
X = helen

% Ερώτημα Β
% trace.
% ?- hold_party(X).

% Ερώτημα Γ
happy(X) :- birthday(X).