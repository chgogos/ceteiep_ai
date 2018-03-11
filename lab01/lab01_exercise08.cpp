/***
 *       ___   ___   _____   ___   ___   ___   ___     ___    __    _   ____
 *      / __| | __| |_   _| | __| |_ _| | __| | _ \   |_  )  /  \  / | |__  |
 *     | (__  | _|    | |   | _|   | |  | _|  |  _/    / /  | () | | |   / /
 *      \___| |___|   |_|   |___| |___| |___| |_|     /___|  \__/  |_|  /_/
 *
 * TEI of Epirus - Department of Computer Engineering
 * Gogos Christos - Arta 2017
 */

/*
g++ lab01_graph.cpp lab01_search.cpp lab01_search_ext.cpp lab01_exercise08.cpp
-o lab01_exercise08 -Wall -std=c++11
./lab01_exercise08 data/tour_romania.txt A B bfs
*/
#include "lab01_search_ext.hpp"

int main(int argc, char **argv) { struct di_graph graph { };
  string fn{};
  string start_vertex{}, goal_vertex{}, search_method{};
  if (argc == 5) {
    fn = argv[1];
    start_vertex = argv[2];
    goal_vertex = argv[3];
    search_method = argv[4];
    graph = read_data(fn);
    if (search_method.compare("bfs") == 0) {
      breadth_first_search(graph, start_vertex, goal_vertex);
      breadth_first_search_recursive(graph, start_vertex, goal_vertex);
    } else if (search_method.compare("dfs") == 0) {
      depth_first_search_alt(graph, start_vertex, goal_vertex);
      depth_first_search_recursive(graph, start_vertex, goal_vertex);
    } else
      cerr << "Invalid choice" << endl;
    free_memory(graph);
  }
}