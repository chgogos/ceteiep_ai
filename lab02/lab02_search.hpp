/***
 *       ___   ___   _____   ___   ___   ___   ___     ___    __    _   ____
 *      / __| | __| |_   _| | __| |_ _| | __| | _ \   |_  )  /  \  / | |__  |
 *     | (__  | _|    | |   | _|   | |  | _|  |  _/    / /  | () | | |   / /
 *      \___| |___|   |_|   |___| |___| |___| |_|     /___|  \__/  |_|  /_/
 *
 * TEI of Epirus - Department of Computer Engineering
 * Gogos Christos - Arta 2017
 */
#ifndef __LAB02_SEARCH_HPP__
#define __LAB02_SEARCH_HPP__

#include "lab02_graph.hpp"
#include <set>
#include <stack>
#include <queue>

struct search_node {
  list<string> path;
  int cost = 0;
  int heuristic = 0;
  // για την ταξινόμηση των κόμβων σε φθίνουσα σειρά κόστους
  bool operator<(search_node other) const {
    return cost + heuristic > other.cost + other.heuristic;
  }
};

// επιστροφή περιεχομένων ουράς προτεραιότητας ως λίστα
list<search_node> priority_queue_to_list(priority_queue<search_node> frontier);

//  pretty print ενός search_node (bestfs)
string search_node_bestfs_as_string(search_node sn);

//  pretty print ενός search_node (A*)
string search_node_astar_as_string(search_node sn);

//  διαδρομή με πλήρη ονόματα κορυφών και κόστος διαδρομής
string solution_path_cost(di_graph graph, search_node sn);

//  διαδρομή με πλήρη ονόματα κορυφών και υπολογισμός κόστους διαδρομής
string solution_path_compute_cost(di_graph graph, search_node sn);

//  pretty print λίστας
string list_as_string(list<string> alist);

// pretty print συνόλου
string set_as_string(set<string> aset);

void print_status_astar(set<string> closed, list<search_node> frontier,
                        string current_state, list<string> successors);

void print_status_bestfs(set<string> closed, list<search_node> frontier,
                         string current_state, list<string> successors);

void print_status_hc(di_graph graph, string current_state,
                     list<string> successors);

// χρησιμοποιείται μόνο για τον κόμβο αφετηρία (start_node)
// έτσι ώστε να αρχικοποιήσει τη διαδρομή
search_node to_search_node(string node, int heuristic = 0);

// προσθήκη ενός επιπλέον κόμβου στη διαδρομή και ενημέρωση κόστους διαδρομής
search_node to_search_node(di_graph graph, search_node parent_sn, string node,
                           int heuristic = 0);

// προσθήκη ενός επιπλέον κόμβου στη διαδρομή 
search_node to_bestfs_search_node(di_graph graph, search_node parent_sn,
                                  string node);

// αναρρίχηση λόφου
void hill_climbing(struct di_graph graph, string start_vertex,
                   string goal_vertex);

// αναζήτηση πρώτα στο καλύτερο
void best_first_search(struct di_graph graph, string start_vertex,
                       string goal_vertex);
//  A* (Άλφα Άστρο)
void alpha_star_search(struct di_graph graph, string start_vertex,
                       string goal_vertex);

#endif