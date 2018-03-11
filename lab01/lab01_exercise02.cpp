/***
 *       ___   ___   _____   ___   ___   ___   ___     ___    __    _   ____
 *      / __| | __| |_   _| | __| |_ _| | __| | _ \   |_  )  /  \  / | |__  |
 *     | (__  | _|    | |   | _|   | |  | _|  |  _/    / /  | () | | |   / /
 *      \___| |___|   |_|   |___| |___| |___| |_|     /___|  \__/  |_|  /_/
 *
 * TEI of Epirus - Department of Computer Engineering
 * Gogos Christos - Arta 2017
 */
#include "lab01_graph.hpp"

using namespace std;

int main(int argc, char **argv) {
  if (argc != 2) {
    cout << "Wrong number of arguments" << endl;
    exit(-1);
  }
  string fn = argv[1];
  struct di_graph graph = read_data(fn);

  // Q1. μέσος όρος βάρους ακμών για όλο το γράφημα
  double sum = 0.0;
  int c = 0;
  for (int v1 = 0; v1 < graph.V; v1++)
    for (int v2 = 0; v2 < graph.V; v2++) {
      if (v1 != v2) {
        int weight = graph.adjacency_matrix[v1][v2];
        if (weight != 0) {
          c++;
          sum += weight;
        }
      }
    }
  cout << "Q1. Average weight of all edges " << sum / c << endl;

  // Q2. Βαθμοί κορυφών και μέσος όρος βαθμού κορυφών για όλο το γράφημα
  int max = 0;
  sum = 0.0;
  for (int i = 0; i < graph.V; i++) {
    string vertex = get_vertex_label(graph, i);
    list<string> edges = get_successors(graph, vertex);
    int degree = edges.size();
    cout << "Q2. Degree of vertex " << vertex << " is " << degree << endl;
    sum += degree;
    if (degree > max)
      max = degree;
  }
  cout << "Q2. Average degree of all vertices " << sum / graph.V << endl;

  // Q3. Ονόματα κορυφών με το μεγαλύτερο βαθμό
  for (int i = 0; i < graph.V; i++) {
    string vertex = get_vertex_label(graph, i);
    list<string> edges = get_successors(graph, vertex);
    int degree = edges.size();
    if (degree == max)
      cout << "Q3. Vertex " << vertex << " has maximum degree " << max << endl;
  }

  // Q4. Όνομα κορυφής που βρίσκεται στη μεγαλύτερη απόσταση από όλες τις
  // γειτονικές της
  max = 0;
  int pmax = -1;
  for (int i = 0; i < graph.V; i++) {
    string vertex1 = get_vertex_label(graph, i);
    int min = INT_MAX;
    for (string vertex2 : get_successors(graph, vertex1)) {
      int distance = get_weight(graph, vertex1, vertex2);
      if (distance < min)
        min = distance;
    }
    if (min > max) {
      max = min;
      pmax = i;
    }
  }
  cout << "Q4. Vertex " << get_vertex_label(graph, pmax)
       << " is furthest away from all other vertices having distance to "
          "closest vertex="
       << max << endl;

  free_memory(graph);
  return 0;
}