/***
 *       ___   ___   _____   ___   ___   ___   ___     ___    __    _   ____
 *      / __| | __| |_   _| | __| |_ _| | __| | _ \   |_  )  /  \  / | |__  |
 *     | (__  | _|    | |   | _|   | |  | _|  |  _/    / /  | () | | |   / /
 *      \___| |___|   |_|   |___| |___| |___| |_|     /___|  \__/  |_|  /_/
 *
 * TEI of Epirus - Department of Computer Engineering
 * Gogos Christos - Arta 2017
 */
#include "lab01_search.hpp"

int main(int argc, char **argv) {
  struct di_graph graph;
  if (argc == 5) {
    graph = read_data(argv[1]);
    string start_vertex = argv[2];
    string goal_vertex = argv[3];
    string search_method = argv[4];
    if (search_method.compare("bfs") == 0)
      breadth_first_search(graph, start_vertex, goal_vertex);
    else if (search_method.compare("dfs") == 0)
      depth_first_search(graph, start_vertex, goal_vertex);
    else if (search_method.compare("ucs") == 0)
      uniform_cost_search(graph, start_vertex, goal_vertex);
    else
      cerr << "invalid option" << endl;
  } else {
    cerr << "wrong number of arguments" << endl;
  }
  free_memory(graph);
}
