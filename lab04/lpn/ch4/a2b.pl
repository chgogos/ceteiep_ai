%% το κατηγόρημα a2b λαμβάνει δύο λίστες ως ορίσματα και επιτυγχάνει αν
%% το πρώτο όρισμα είναι μια λίστα με a και 
%% το δεύτερο όρισμα είναι μια λίστα με b με το ίδιο μήκος

a2b([],[]).
a2b([a|L1],[b|L2]) :- a2b(L1,L2).

%% ?- a2b([a,a,a,a],[b,b,b,b]).
%% true.

%% ?- a2b([a,a,a,a],[b,b,b]).
%% false.

%% ?- a2b([a,a,a,a],X).
%% X = [b,b,b,b].

%% ?- a2b(X,[b,b,b,b,b,b,b]).
%% X = [a,a,a,a,a,a,a].