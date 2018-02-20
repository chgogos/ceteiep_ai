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
#include <sstream>
#include <fstream>

using namespace std;

string get_vertex_label(struct di_graph graph, int vertex_index) {
  return graph.vertices[vertex_index];
}

int get_vertex_index(struct di_graph graph, string vertex) {
  int vertex_index{-1};
  for (int i = 0; i < graph.V; i++)
    if (graph.vertices[i].compare(vertex) == 0) {
      vertex_index = i;
      break;
    }
  return vertex_index;
}

int get_weight(di_graph graph, string source_vertex,
               string destination_vertex) {
  return graph.adjacency_matrix[get_vertex_index(
      graph, source_vertex)][get_vertex_index(graph, destination_vertex)];
}

list<string> get_successors(struct di_graph graph, string node,
                            bool asc_order) {
  list<string> successors{};
  int node_index = get_vertex_index(graph, node);
  for (int j = 0; j < graph.V; j++)
    if (graph.adjacency_matrix[node_index][j] != 0)
      successors.push_back(get_vertex_label(graph, j));
  successors.sort();
  if (!asc_order)
    successors.reverse();
  return successors;
}

void print_graph_info(struct di_graph graph) {
  cout << "Vertices=" << graph.V << endl;
  for (int i = 0; i < graph.V; i++)
    cout << "Vertex " << graph.vertices_full_names[i] << "("
         << graph.vertices[i] << ")" << endl;
  cout << "Edges=" << graph.E << endl;
  for (int i = 0; i < graph.V; i++)
    for (int j = 0; j < graph.V; j++)
      if (graph.adjacency_matrix[i][j] != 0)
        cout << graph.vertices_full_names[i] << "(" << graph.vertices[i]
             << ")--" << graph.adjacency_matrix[i][j] << "-->"
             << graph.vertices_full_names[j] << "(" << graph.vertices[j] << ")"
             << endl;
}

struct di_graph read_data(string fn) {
  struct di_graph graph {};
  fstream filestr{};
  filestr.open(fn.c_str());
  if (filestr.is_open()) {
    string vertices_header{};
    getline(filestr, vertices_header);
    // αγνόησε τις αρχικές γραμμές που ξεκινάνε με τον χαρακτήρα #
    while (vertices_header.at(0) == '#')
      getline(filestr, vertices_header);
    graph.V = stoi(vertices_header.substr(vertices_header.find(":") + 1,
                                          vertices_header.length() - 1));
    graph.vertices = new string[graph.V]{};
    graph.vertices_full_names = new string[graph.V]{};
    for (int i = 0; i < graph.V; i++) {
      string vertex{};
      getline(filestr, vertex);
      // trim κενών χαρακτήρων δεξιά του λεκτικού vertex
      vertex.erase(vertex.find_last_not_of(" \n\r\t") + 1);
      int pos = vertex.find(",");
      if (pos == -1) {
        // αν δεν υπάρχει δεύτερο όνομα τότε χρησιμοποιείται η συντομογραφία
        graph.vertices[i] = vertex.substr(0, vertex.length());
        graph.vertices_full_names[i] = vertex.substr(0, vertex.length());
      } else {
        graph.vertices[i] = vertex.substr(0, pos);
        graph.vertices_full_names[i] =
            vertex.substr(pos + 1, vertex.length() - pos - 1);
      }
    }
    string edges_header{};
    getline(filestr, edges_header);
    graph.E = stoi(edges_header.substr(edges_header.find(":") + 1,
                                       edges_header.length() - 1));
    graph.adjacency_matrix = new int *[graph.V]{};
    for (int i = 0; i < graph.V; i++)
      graph.adjacency_matrix[i] = new int[graph.V]{};
    for (int i = 0; i < graph.E; i++) {
      string edge{};
      getline(filestr, edge);
      edge.erase(edge.find_last_not_of(" \n\r\t") + 1);
      int pos1 = edge.find(",");
      int pos2 = edge.find(",", pos1 + 1);
      string source_vertex = edge.substr(0, pos1);
      string destination_vertex = edge.substr(pos1 + 1, pos2 - pos1 - 1);
      int weight = stoi(edge.substr(pos2 + 1, edge.length() - pos2));
      int source_vertex_index = get_vertex_index(graph, source_vertex);
      int destination_vertex_index =
          get_vertex_index(graph, destination_vertex);
      if ((source_vertex_index >= 0) && (source_vertex_index < graph.V))
        graph.adjacency_matrix[source_vertex_index][destination_vertex_index] =
            weight;
      else {
        cerr << "Edge data problem" << endl;
        exit(-1);
      }
    }
  } else {
    cout << "Error opening file: " << fn << endl;
    exit(-1);
  }
  return graph;
}

void free_memory(struct di_graph graph) {
  delete[] graph.vertices;
  delete[] graph.vertices_full_names;
  for (int i = 0; i < graph.V; i++) {
    delete[] graph.adjacency_matrix[i];
  }
  delete[] graph.adjacency_matrix;
}