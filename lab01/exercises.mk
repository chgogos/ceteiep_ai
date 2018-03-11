CXX=g++
CFLAGS=-Wall -std=c++11

all: lab01_exercise02 lab01_exercise03 lab01_exercise04 lab01_exercise06 lab01_exercise08

lab01_exercise02: lab01_graph.cpp lab01_exercise02.cpp
	$(CXX) $(CFLAGS) lab01_graph.cpp lab01_exercise02.cpp -o lab01_exercise02

lab01_exercise03: lab01_graph.cpp lab01_search_exercise03.cpp lab01_exercise03.cpp
	$(CXX) $(CFLAGS) lab01_graph.cpp lab01_search_exercise03.cpp lab01_exercise03.cpp -o lab01_exercise03

lab01_exercise04: lab01_graph.cpp lab01_search_simple_exercise04.cpp lab01_exercise04.cpp
	$(CXX) $(CFLAGS) lab01_graph.cpp lab01_search_simple_exercise04.cpp lab01_exercise04.cpp -o lab01_exercise04

lab01_exercise06: lab01_graph.cpp lab01_search.cpp lab01_search_ext.cpp lab01_exercise06.cpp
	$(CXX) $(CFLAGS) lab01_graph.cpp lab01_search.cpp lab01_search_ext.cpp lab01_exercise06.cpp -o lab01_exercise06

lab01_exercise06: lab01_graph.cpp lab01_search.cpp lab01_search_ext.cpp lab01_exercise08.cpp
	$(CXX) $(CFLAGS) lab01_graph.cpp lab01_search.cpp lab01_search_ext.cpp lab01_exercise08.cpp -o lab01_exercise06

exercise02: lab01_exercise02
	./lab01_exercise02 data/tour_romania.txt

exercise03: lab01_exercise03
	./lab01_exercise03 data/tour_romania.txt

exercise04: lab01_exercise04
	./lab01_exercise04

exercise06: lab01_exercise06
	./lab01_exercise06 data/tour_romania.txt A B bfs

exercise08: lab01_exercise08
	./lab01_exercise08 data/tour_romania.txt A B bfs

clean:
	rm lab01_exercise02 lab01_exercise03 lab01_exercise04 lab01_exercise06 lab01_exercise08
