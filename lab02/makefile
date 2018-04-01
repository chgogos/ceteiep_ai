CXX=g++
CFLAGS=-Wall -std=c++11
DATASET=data/tour_romania_h.txt
ORIGIN=A

all: lab02_01 lab02_02

lab02_01: lab02_01.cpp lab02_graph.cpp
	$(CXX) $(CFLAGS) lab02_01.cpp lab02_graph.cpp -o lab02_01

lab02_02: lab02_02.cpp lab02_graph.cpp lab02_search.cpp
	$(CXX) $(CFLAGS) lab02_02.cpp lab02_graph.cpp lab02_search.cpp -o lab02_02

# target to run example1 for DATASET (print graph info)
run1: lab02_01
	./lab02_01 $(DATASET)

# target to run example2 for DATASET using Hill Climbing (ORIGIN-->destination defined in graph data)
run2: lab02_02
	./lab02_02 $(DATASET) $(ORIGIN) HC

# target to run example2 for DATASET using BestFS (ORIGIN-->destination defined in graph data)
run3: lab02_02
	./lab02_02 $(DATASET) $(ORIGIN) BESTFS

# target to run example2 for DATASET using A* (ORIGIN-->destination defined in graph data)
run4: lab02_02
	./lab02_02 $(DATASET) $(ORIGIN) ASTAR

clean:
	rm -f lab02_01 lab02_02
