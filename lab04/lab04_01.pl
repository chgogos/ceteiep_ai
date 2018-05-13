likes(john,mary).
likes(john,trains).
likes(peter,fast_cars).
likes(Person1,Person2):-
    hobby(Person1,Hobby),
    hobby(Person2,Hobby).

hobby(john,trainspotting).
hobby(tim,sailing).
hobby(helen,trainspotting).
hobby(simon,sailing).

% Ερώτημα Α
% ?- likes(trains,john).
% false

% ?- likes(helen,john).
% true

% ?- likes(tim,helen).
% false

% ?- likes(john,X).
% X = mary ;
% X = trains ;
% X = john ;
% X = helen.

% Ερώτημα B
% ?- trace.
% ?- likes(john, X).

% Ερώτημα Γ
% likes(X,trains) :- hobby(X,trainspotting)