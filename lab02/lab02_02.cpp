/***
 *       ___   ___   _____   ___   ___   ___   ___     ___    __    _   ____
 *      / __| | __| |_   _| | __| |_ _| | __| | _ \   |_  )  /  \  / | |__  |
 *     | (__  | _|    | |   | _|   | |  | _|  |  _/    / /  | () | | |   / /
 *      \___| |___|   |_|   |___| |___| |___| |_|     /___|  \__/  |_|  /_/
 *
 * TEI of Epirus - Department of Computer Engineering
 * Gogos Christos - Arta 2017
 */

#include "lab02_search.hpp"
#include <stdlib.h>

int main(int argc, char **argv) {
  struct di_graph graph { };
  string fn{};
  string start_vertex{}, search_method{};
  if (argc != 4) {
    printf("Wrong number of arguments\n");
    printf("Usage   : %s <problem_instance> <source> <algorithm> \n", argv[0]);
    printf("Example : %s tour_romania_h.txt A ASTAR \n", argv[0]);
    exit(-1);
  }
  fn = argv[1];
  start_vertex = argv[2];
  search_method = argv[3];
  graph = read_data(fn);
  cout << "Origin: " << start_vertex << " destination: " << graph.goal_vertex << endl;
  if (search_method.compare("HC") == 0)
    hill_climbing(graph, start_vertex, graph.goal_vertex);
  else if (search_method.compare("BESTFS") == 0)
    best_first_search(graph, start_vertex, graph.goal_vertex);
  else if (search_method.compare("ASTAR") == 0)
    alpha_star_search(graph, start_vertex, graph.goal_vertex);
  else
    cerr << "invalid option" << endl;
  free_memory(graph);
}