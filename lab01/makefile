CC=g++
CFLAGS=-Wall -std=c++11

all: lab01_01 lab01_02 lab01_03

lab01_01: lab01_01.cpp lab01_graph.cpp
	$(CC) $(CFLAGS) lab01_01.cpp lab01_graph.cpp -o lab01_01

lab01_02:lab01_02.cpp lab01_graph.cpp lab01_search_simple.cpp
	$(CC) $(CFLAGS) lab01_02.cpp lab01_graph.cpp lab01_search_simple.cpp -o lab01_02

lab01_03:lab01_03.cpp lab01_graph.cpp lab01_search.cpp
	$(CC) $(CFLAGS) lab01_03.cpp lab01_graph.cpp lab01_search.cpp -o lab01_03

# target to run example1 for tour_romania (print graph info)
run1: lab01_01
	./lab01_01 data/tour_romania.txt

# target to run example2 for tour_romania, breadth first search A-->B
run2: lab01_02
	./lab01_02 data/tour_romania.txt A B bfs

# target to run example3 for tour_romania, breadth first search A-->B
run3: lab01_03
	./lab01_03 data/tour_romania.txt A B bfs

clean:
	rm lab01_01 lab01_02 lab01_03
