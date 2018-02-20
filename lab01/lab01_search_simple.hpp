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

// Ο αλγόριθμος αναζήτησης κατά πλάτος χωρίς αποθήκευση της διαδρομής 
void breadth_first_search_base(struct di_graph graph, string start_vertex,
                               string goal_vertex);

// Ο αλγόριθμος αναζήτησης κατά βάθος χωρίς αποθήκευση της διαδρομής 
void depth_first_search_base(struct di_graph graph, string start_vertex,
                             string goal_vertex);
