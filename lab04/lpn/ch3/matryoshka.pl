directlyIn(irina,natasha).
directlyIn(natasha, olga).
directlyIn(olga, katarina).

in(X,Y):- directlyIn(X,Y).
in(X,Y):- directlyIn(X,Z), in(Z,Y).

% in(X, katarina). 