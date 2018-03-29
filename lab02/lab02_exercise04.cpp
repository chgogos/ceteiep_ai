/***
 *       ___   ___   _____   ___   ___   ___   ___     ___    __    _   ____
 *      / __| | __| |_   _| | __| |_ _| | __| | _ \   |_  )  /  \  / | |__  |
 *     | (__  | _|    | |   | _|   | |  | _|  |  _/    / /  | () | | |   / /
 *      \___| |___|   |_|   |___| |___| |___| |_|     /___|  \__/  |_|  /_/
 *
 * TEI of Epirus - Department of Computer Engineering
 * Gogos Christos - Arta 2017
 */

#include "lab02_search.hpp"
#include <stdlib.h>

void print_status_astar_without_closed_set(list<search_node> frontier,
		string current_state, list<string> successors) {
	cout << "frontier:[";
	for (search_node sn : frontier)
		cout << search_node_astar_as_string(sn);
	cout << "]";
	cout << " current node:" << current_state;
	cout << " successors:" << list_as_string(successors) << endl;
}

void alpha_star_search_without_closed_set(struct di_graph graph,
		string start_vertex, string goal_vertex) {
	cout << "A* no closed set" << endl;
	priority_queue<search_node> frontier { }; 
	frontier.push(
			to_search_node(start_vertex, get_heuristic(graph, start_vertex)));
	search_node current_state = frontier.top();
	string current_state_back = current_state.path.back();
	bool found { true };
	while (goal_vertex.compare(current_state_back) != 0) {
		print_status_astar_without_closed_set(priority_queue_to_list(frontier),
				current_state_back, get_successors(graph, current_state_back));
		frontier.pop();
		for (string v : get_successors(graph, current_state_back))
			frontier.push(
					to_search_node(graph, current_state, v,
							get_heuristic(graph, v)));
		if (frontier.empty()) {
			found = false;
			break;
		}
		current_state = frontier.top();
		current_state_back = current_state.path.back();
	}
	if (found) {
		print_status_astar_without_closed_set(priority_queue_to_list(frontier),
				current_state_back, get_successors(graph, current_state_back));
		cout << "Path to goal node found: "
				<< solution_path_cost(graph, current_state) << endl;
	} else
		cout << "Goal not found!" << endl;
}

int main(int argc, char **argv) { 
  struct di_graph graph { };
  string fn{};
  string start_vertex{}, search_method{};
  if (argc != 3) {
    printf("Wrong number of arguments\n");
    printf("Usage   : %s <problem_instance> <source>\n", argv[0]);
    printf("Example : %s tour_romania_h.txt A \n", argv[0]);
    exit(-1);
  }
  fn = argv[1];
  start_vertex = argv[2];
  graph = read_data(fn);
  cout << "Origin: " << start_vertex << " destination: " << graph.goal_vertex
       << endl;
  alpha_star_search(graph, start_vertex, graph.goal_vertex);
  alpha_star_search_without_closed_set(graph, start_vertex, graph.goal_vertex);
  free_memory(graph);
}