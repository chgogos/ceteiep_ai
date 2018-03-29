CXX=g++
CFLAGS=-Wall -std=c++11

all: lab02_exercise03 lab02_exercise04

lab02_exercise03: lab02_graph.cpp lab02_exercise03.cpp
	$(CXX) $(CFLAGS) lab02_graph.cpp lab02_exercise03.cpp -o lab02_exercise03

lab02_exercise04: lab02_graph.cpp lab02_exercise04.cpp lab02_exercise04.cpp
	$(CXX) $(CFLAGS) lab02_graph.cpp lab02_search.cpp lab02_exercise04.cpp -o lab02_exercise04

exercise03: lab02_exercise03
	./lab02_exercise03

exercise04: lab02_exercise04
	./lab02_exercise04 data/toy2_h.txt A 

clean:
	rm -f lab02_exercise03 lab02_exercise04
