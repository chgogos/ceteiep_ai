/***
 *       ___   ___   _____   ___   ___   ___   ___     ___    __    _   ____
 *      / __| | __| |_   _| | __| |_ _| | __| | _ \   |_  )  /  \  / | |__  |
 *     | (__  | _|    | |   | _|   | |  | _|  |  _/    / /  | () | | |   / /
 *      \___| |___|   |_|   |___| |___| |___| |_|     /___|  \__/  |_|  /_/
 *
 * TEI of Epirus - Department of Computer Engineering
 * Gogos Christos - Arta 2017
 */

#ifndef __LAB01_SEARCH_SIMPLE_EXERCISE04_HPP__
#define __LAB01_SEARCH_SIMPLE_EXERCISE04_HPP__

#include "lab01_graph.hpp"

// Ο αλγόριθμος αναζήτησης κατά πλάτος χωρίς αποθήκευση της διαδρομής
int breadth_first_search_base(struct di_graph graph, string start_vertex,
                              string goal_vertex);

// Ο αλγόριθμος αναζήτησης κατά βάθος χωρίς αποθήκευση της διαδρομής
int depth_first_search_base(struct di_graph graph, string start_vertex,
                            string goal_vertex);

#endif