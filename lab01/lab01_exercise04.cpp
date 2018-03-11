/***
 *       ___   ___   _____   ___   ___   ___   ___     ___    __    _   ____
 *      / __| | __| |_   _| | __| |_ _| | __| | _ \   |_  )  /  \  / | |__  |
 *     | (__  | _|    | |   | _|   | |  | _|  |  _/    / /  | () | | |   / /
 *      \___| |___|   |_|   |___| |___| |___| |_|     /___|  \__/  |_|  /_/
 *
 * TEI of Epirus - Department of Computer Engineering
 * Gogos Christos - Arta 2017
 */

#include "lab01_search_simple_exercise04.hpp"

int main() {
  string fn{"data/tour_romania.txt"};
  struct di_graph graph = read_data(fn);
  int loops_bfs = 0;
  int loops_dfs = 0;
  string destination = "B";
  for (int v = 0; v < graph.V; v++) {
    string vertex = get_vertex_label(graph, v);
    if (vertex != destination) {
      loops_bfs += breadth_first_search_base(graph, vertex, destination);
      loops_dfs += depth_first_search_base(graph, vertex, destination);
    }
  }
  cout << "Loops for BFS " << loops_bfs << endl;
  cout << "Loops for DFS " << loops_dfs << endl;
  free_memory(graph);
  return 0;
}