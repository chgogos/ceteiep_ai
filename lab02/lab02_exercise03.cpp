/***
 *       ___   ___   _____   ___   ___   ___   ___     ___    __    _   ____
 *      / __| | __| |_   _| | __| |_ _| | __| | _ \   |_  )  /  \  / | |__  |
 *     | (__  | _|    | |   | _|   | |  | _|  |  _/    / /  | () | | |   / /
 *      \___| |___|   |_|   |___| |___| |___| |_|     /___|  \__/  |_|  /_/
 *
 * TEI of Epirus - Department of Computer Engineering
 * Gogos Christos - Arta 2017
 */

#include "lab02_graph.hpp"
#include <stdlib.h>

bool hill_climbing_base(struct di_graph graph, string start_vertex,
                        string goal_vertex) {
  string current_state = start_vertex;
  while (goal_vertex.compare(current_state) != 0) {
    list<string> children = get_successors(graph, current_state);
    if (children.empty())
      return false;
    string best_child = children.front();
    for (string v : children) {
      if (get_heuristic(graph, v) < get_heuristic(graph, best_child))
        best_child = v;
    }
    if (get_heuristic(graph, best_child) < get_heuristic(graph, current_state))
      current_state = best_child;
    else
      return false;
  }
  return true;
}

int main(int argc, char **argv) {
  struct di_graph graph = read_data("data/tour_romania_h.txt");
  for (int i = 0; i < graph.V; i++) {
    string source_vertex{get_vertex_label(graph, i)};
    bool flag = hill_climbing_base(graph, source_vertex, graph.goal_vertex);
    if (!flag)
      cout << "source: " << source_vertex << " destination: " << graph.goal_vertex <<  " DEADLOCK" << endl;
  }
  free_memory(graph);
}
