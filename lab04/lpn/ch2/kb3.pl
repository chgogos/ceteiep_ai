loves(vincent,mia).
loves(marsellus,mia).
jealous(A,B):-
loves(A,C),
loves(B,C).

% jealous(X,Y).