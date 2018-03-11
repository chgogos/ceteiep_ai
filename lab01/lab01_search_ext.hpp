/***
 *       ___   ___   _____   ___   ___   ___   ___     ___    __    _   ____
 *      / __| | __| |_   _| | __| |_ _| | __| | _ \   |_  )  /  \  / | |__  |
 *     | (__  | _|    | |   | _|   | |  | _|  |  _/    / /  | () | | |   / /
 *      \___| |___|   |_|   |___| |___| |___| |_|     /___|  \__/  |_|  /_/
 *
 * TEI of Epirus - Department of Computer Engineering
 * Gogos Christos - Arta 2017
 */

#ifndef __LAB01_SEARCH_EXT_HPP__
#define __LAB01_SEARCH_EXT_HPP__

#include "lab01_search.hpp"

using namespace std;

void breadth_first_search_alt(struct di_graph graph, string start_vertex,
                              string goal_vertex);

void breadth_first_search_recursive(struct di_graph graph, string start_vertex,
                                    string goal_vertex);

search_node bfs_r(struct di_graph graph, set<string> closed,
                  list<search_node> node_list, string goal_vertex);

void depth_first_search_alt(struct di_graph graph, string start_vertex,
                            string goal_vertex);

void depth_first_search_recursive(struct di_graph graph, string start_vertex,
                                  string goal_vertex);

search_node dfs_r(struct di_graph graph, set<string> closed,
                  search_node current_state, string goal_vertex);

void uniform_cost_search_alt(struct di_graph graph, string start_vertex,
                             string goal_vertex);

#endif