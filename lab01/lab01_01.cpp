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
  struct di_graph graph = read_data(argv[1]);
  print_graph_info(graph);
  free_memory(graph);
}
