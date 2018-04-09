CXX=g++
CFLAGS=-Wall -std=c++11

all: lab03_01 lab03_02 lab03_03 lab03_04

lab03_01: lab03_01.cpp lab03_board.cpp
	$(CXX) $(CFLAGS) lab03_01.cpp lab03_board.cpp -o lab03_01

lab03_02: lab03_02.cpp lab03_board.cpp lab03_human.cpp
	$(CXX) $(CFLAGS) lab03_02.cpp lab03_board.cpp lab03_human.cpp -o lab03_02

lab03_03: lab03_03.cpp lab03_board.cpp lab03_human.cpp lab03_solvers.cpp
	$(CXX) $(CFLAGS) lab03_03.cpp lab03_board.cpp lab03_human.cpp lab03_solvers.cpp -o lab03_03

lab03_04: lab03_04.cpp lab03_board.cpp lab03_human.cpp lab03_solvers.cpp
	$(CXX) $(CFLAGS) lab03_04.cpp lab03_board.cpp lab03_human.cpp lab03_solvers.cpp -o lab03_04

# target to run example1 (choose random move for X and show all possible boards for O)
run1: lab03_01
	./lab03_01

# target to run example2 (two human players)
run2: lab03_02
	./lab03_02 

# target to run example3 (human player vs heuristic solver)
run3: lab03_03
	./lab03_03 

# target to run example4 (human player vs alpha-beta solver using 5 plies)
run4: lab03_04 
	./lab03_04 ALPHABETA 5

clean:
	rm -f lab03_01 lab03_02 lab03_03 lab03_04
