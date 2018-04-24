CXX=g++
CFLAGS=-Wall -std=c++11

all: lab03_exercise01 lab03_exercise02

lab03_exercise01: lab03_board.cpp lab03_exercise01.cpp
	$(CXX) $(CFLAGS) lab03_board.cpp lab03_exercise01.cpp -o lab03_exercise01

lab03_exercise02: lab03_board.cpp lab03_solvers.cpp lab03_exercise02.cpp
	$(CXX) $(CFLAGS) lab03_board.cpp lab03_solvers.cpp lab03_exercise02.cpp -o lab03_exercise02

exercise01: lab03_exercise01
	./lab03_exercise01

exercise02: lab03_exercise02
	./lab03_exercise02

clean:
	rm -f lab03_exercise01 lab03_exercise02
