/***
 *       ___   ___   _____   ___   ___   ___   ___     ___    __    _   ____
 *      / __| | __| |_   _| | __| |_ _| | __| | _ \   |_  )  /  \  / | |__  |
 *     | (__  | _|    | |   | _|   | |  | _|  |  _/    / /  | () | | |   / /
 *      \___| |___|   |_|   |___| |___| |___| |_|     /___|  \__/  |_|  /_/
 *
 * TEI of Epirus - Department of Computer Engineering
 * Gogos Christos - Arta 2017
 */
#include <iostream>
#include <list>
#include <cstring>

using namespace std;

// δομή γραφήματος
struct di_graph {
  int V;            // αριθμός κορυφών γραφήματος
  int E;            // αριθμός ακμών γραφήματος
  string *vertices; // συντομογραφίες ονομάτων κορυφών
  string *vertices_full_names; // πλήρη ονόματα κορυφών
  int **adjacency_matrix;      // πίνακας γειτνίασης
};

//  επιστροφή του ονόματος της κορυφής με δεδομένη τη θέση της κορυφής
string get_vertex_label(struct di_graph graph, int vertex_index);

//  επιστροφή της θέσης της κορυφής με δεδομένο το όνομα της κορυφής
int get_vertex_index(struct di_graph graph, string vertex);

// επιστροφή του μήκους της ακμής ανάμεσα σε 2 κορυφές
int get_weight(di_graph graph, string source_vertex, string destination_vertex);

//  επισστροφή λίστας με τις γειτονικές κορυφές μιας κορυφής του γραφήματος
//  ταξινομημένες σε αύξουσα ή σε φθίνουσα αλφαβητική σειρά
list<string> get_successors(struct di_graph graph, string node, bool asc_order=true);

// Εκτύπωση της πληροφορίας του γραφήματος
void print_graph_info(struct di_graph graph);

// ανάγνωση γραφήματος από αρχείο κειμένου
struct di_graph read_data(string fn);

//  απελευθέρωση της μνήμης που καταλαμβάνει το γράφημα
void free_memory(struct di_graph graph);