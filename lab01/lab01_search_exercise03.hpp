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
#include <queue>
#include <set>
#include <stack>

using namespace std;

struct search_node {
  list<string> path;
  int cost = 0;
  bool is_goal = false;
  bool operator<(search_node other) const { return cost > other.cost; }
};

// αναζήτηση πρώτα κατά βάθος
int depth_first_search(struct di_graph graph, string start_vertex,
                       string goal_vertex);

// αναζήτηση πρώτα κατά πλάτος
int breadth_first_search(struct di_graph graph, string start_vertex,
                         string goal_vertex);

// αναζήτηση ομοιόμορφου κόστους
int uniform_cost_search(struct di_graph graph, string start_vertex,
                        string goal_vertex);

// convenience function για μεταφορά περιεχομένων στοίβας σε λίστα
list<search_node> stack_to_list(stack<search_node> frontier);

// convenience function για μεταφορά περιεχομένων ουράς σε λίστα
list<search_node> queue_to_list(queue<search_node> frontier);

// convenience function για μεταφορά περιεχομένων ουράς προτεραιότητας σε λίστα
list<search_node> priority_queue_to_list(priority_queue<search_node> frontier);

// convenience function για pretty print ενός search_node
string search_node_as_string(search_node sn, bool show_path_cost = true);

//  επιστρέφει τη λύση μαζί με το κόστος της χρησιμοποιώντας τα πλήρη ονόματα
//  των κόμβων του γράφου
string solution_path_cost(di_graph graph, search_node sn);

// convenience function για pretty print λίστας με λεκτικά
string list_as_string(list<string> alist);

// convenience function για pretty print συνόλου με λεκτικά
string set_as_string(set<string> aset);

/**
 * χρησιμοποιείται για να εμφανίζει κατά τη διάρκεια της αναζήτησης
 * το μέτωπο αναζήτησης, το κλειστό σύνολο, τον τρέχοντα κόμβο και τους
 * γειτονικούς κόμβους του τρέχοντα κόμβου
 */
void print_status(set<string> closed, list<search_node> frontier,
                  string current_state, list<string> successors,
                  bool show_path_cost = false);

//  χρησιμοποιείται μόνο για τον κόμβο αφετηρία (start_node) έτσι ώστε να
//  αρχικοποιήσει τη διαδρομή
search_node to_search_node(string node);

// προσθήκη ενός επιπλέον κόμβου στη διαδρομή που έχει ήδη δημιουργηθεί,
// ενημέρωση κόστους
search_node to_search_node(di_graph graph, search_node parent_sn, string node);