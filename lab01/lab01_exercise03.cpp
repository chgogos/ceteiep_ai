/***
 *       ___   ___   _____   ___   ___   ___   ___     ___    __    _   ____
 *      / __| | __| |_   _| | __| |_ _| | __| | _ \   |_  )  /  \  / | |__  |
 *     | (__  | _|    | |   | _|   | |  | _|  |  _/    / /  | () | | |   / /
 *      \___| |___|   |_|   |___| |___| |___| |_|     /___|  \__/  |_|  /_/
 *
 * TEI of Epirus - Department of Computer Engineering
 * Gogos Christos - Arta 2017
 */

#include "lab01_search_exercise03.hpp"

using namespace std;

int main(int argc, char **argv) {
  if (argc != 2) {
    cout << "Wrong number of arguments" << endl;
    exit(-1);
  }
  string fn = argv[1];
  struct di_graph graph = read_data(fn);

  int c1, c2, c3, c4, c5;
  c1 = c2 = c3 = c4 = c5 = 0;
  for (int v1 = 0; v1 < graph.V; v1++)
    for (int v2 = v1 + 1; v2 < graph.V; v2++) {
      int dfs_cost, bfs_cost, ucs_cost;
      string vertex1 = get_vertex_label(graph, v1);
      string vertex2 = get_vertex_label(graph, v2);
      bfs_cost = breadth_first_search(graph, vertex1, vertex2);
      dfs_cost = depth_first_search(graph, vertex1, vertex2);
      ucs_cost = uniform_cost_search(graph, vertex1, vertex2);
      if (bfs_cost < dfs_cost)
        c1++;
      else if (bfs_cost > dfs_cost)
        c2++;
      else
        c3++;
      if (bfs_cost == ucs_cost)
        c4++;
      if (dfs_cost == ucs_cost)
        c5++;
    }
  cout << "Q1. " << c1 << endl;
  cout << "Q2. " << c2 << endl;
  cout << "Q3. " << c3 << endl;
  cout << "Q4. " << c4 << endl;
  cout << "Q5. " << c5 << endl;
}