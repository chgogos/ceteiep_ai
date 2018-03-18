CXX=g++
CFLAGS=-Wall -std=c++11
DATASET=data/tour_romania_h.txt

all: lab02_01 lab02_02

lab02_01: lab02_01.cpp lab02_graph.cpp
	$(CXX) $(CFLAGS) lab02_01.cpp lab02_graph.cpp -o lab02_01

lab02_02: lab02_02.cpp lab02_graph.cpp lab02_search.cpp
	$(CXX) $(CFLAGS) lab02_02.cpp lab02_graph.cpp lab02_search.cpp -o lab02_02

# target to run example1 for tour_romania (print graph info)
run1: lab02_01
	./lab02_01 $(DATASET)

# target to run example2 for tour_romania using Hill Climbing (Arad-->Bucharest)
run2: lab02_02
	./lab02_02 $(DATASET) A HC

# target to run example2 for tour_romania using BestFS (Arad-->Bucharest)
run3: lab02_02
	./lab02_02 $(DATASET) A BESTFS

# target to run example2 for tour_romania using A* (Arad-->Bucharest)
run4: lab02_02
	./lab02_02 $(DATASET) A ASTAR

clean:
	rm -f lab02_01 lab02_02
