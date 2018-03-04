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

list<search_node> priority_queue_to_list(priority_queue<search_node> frontier) {
  list<search_node> alist{};
  while (!frontier.empty()) {
    alist.push_back(frontier.top());
    frontier.pop();
  }
  return alist;
}

string search_node_bestfs_as_string(search_node sn) {
  string s{};
  s.append("(");
  for (string v : sn.path) {
    s.append(v);
    s.append("-");
  }
  if (s.length() > 1)
    s.pop_back();
  s.append(" ");
  s.append(to_string(sn.heuristic));
  s.append(")");
  return s;
}

string search_node_astar_as_string(search_node sn) {
  string s{};
  s.append("(");
  for (string v : sn.path) {
    s.append(v);
    s.append("-");
  }
  if (s.length() > 1)
    s.pop_back();
  s.append(" ");
  s.append(to_string(sn.cost));
  s.append("+");
  s.append(to_string(sn.heuristic));
  s.append("=");
  s.append(to_string(sn.cost + sn.heuristic));
  s.append(")");
  return s;
}

string solution_path_cost(di_graph graph, search_node sn) {
  string s{};
  s.append("(");
  for (string v : sn.path) {
    s.append(graph.vertices_full_names[get_vertex_index(graph, v)]);
    s.append("-");
  }
  if (s.length() > 1)
    s.pop_back();
  s.append(" ");
  s.append(to_string(sn.cost));
  s.append(")");
  return s;
}

string solution_path_compute_cost(di_graph graph, search_node sn) {
  string s{};
  s.append("(");
  string pv = "";
  sn.cost = 0;
  for (string v : sn.path) {
    s.append(graph.vertices_full_names[get_vertex_index(graph, v)]);
    s.append("-");
    if (pv.compare("") != 0)
      sn.cost += get_weight(graph, pv, v);
    pv = v;
  }
  if (s.length() > 1)
    s.pop_back();
  s.append(" ");
  s.append(to_string(sn.cost));
  s.append(")");
  return s;
}

string list_as_string(list<string> alist) {
  string s{};
  s.append("[");
  for (string v : alist) {
    s.append(v);
    s.append(" ");
  }
  if (s.length() > 1)
    s.pop_back();
  s.append("]");
  return s;
}

string set_as_string(set<string> aset) {
  string s{};
  s.append("[");
  for (string v : aset) {
    s.append(v);
    s.append(" ");
  }
  if (s.length() > 1)
    s.pop_back();
  s.append("]");
  return s;
}

void print_status_astar(set<string> closed, list<search_node> frontier,
                        string current_state, list<string> successors) {
  cout << "frontier:[";
  for (search_node sn : frontier)
    cout << search_node_astar_as_string(sn);
  cout << "]";
  cout << " closed set:" << set_as_string(closed);
  cout << " current node:" << current_state;
  bool is_in{closed.find(current_state) != closed.end()};
  if (is_in)
    cout << " successors:[loop]" << endl;
  else {
    cout << " successors:" << list_as_string(successors) << endl;
  }
}

void print_status_bestfs(set<string> closed, list<search_node> frontier,
                         string current_state, list<string> successors) {
  cout << "frontier:[";
  for (search_node sn : frontier)
    cout << search_node_bestfs_as_string(sn);
  cout << "]";
  cout << " closed set:" << set_as_string(closed);
  cout << " current node:" << current_state;
  bool is_in{closed.find(current_state) != closed.end()};
  if (is_in)
    cout << " successors:[loop]" << endl;
  else {
    cout << " successors:" << list_as_string(successors) << endl;
  }
}

void print_status_hc(di_graph graph, string current_state,
                     list<string> successors) {
  string s{};
  s.append("current node:(");
  s.append(current_state);
  s.append(" ");
  s.append(to_string(get_heuristic(graph, current_state)));
  s.append(") successors:");
  for (string v : successors) {
    s.append("(");
    s.append(v);
    s.append(" ");
    s.append(to_string(get_heuristic(graph, v)));
    s.append(")");
  }
  cout << s << endl;
}

search_node to_search_node(string node, int heuristic) {
  search_node sn{};
  sn.path.push_back(node);
  sn.cost = 0;
  sn.heuristic = heuristic;
  return sn;
}

search_node to_search_node(di_graph graph, search_node parent_sn, string node,
                           int heuristic) {
  search_node sn{};
  for (string v : parent_sn.path) {
    sn.path.push_back(v);
  }
  sn.path.push_back(node);
  sn.cost = parent_sn.cost + get_weight(graph, parent_sn.path.back(), node);
  sn.heuristic = heuristic;
  return sn;
}

search_node to_bestfs_search_node(di_graph graph, search_node parent_sn,
                                  string node) {
  search_node sn{};
  for (string v : parent_sn.path) {
    sn.path.push_back(v);
  }
  sn.path.push_back(node);
  sn.cost = 0;
  sn.heuristic = get_heuristic(graph, node);
  return sn;
}

void hill_climbing(struct di_graph graph, string start_vertex,
                   string goal_vertex) {
  cout << "Hill Climbing" << endl;
  int best_cost = get_heuristic(graph, start_vertex);
  search_node current_state =
      to_search_node(start_vertex, get_heuristic(graph, start_vertex));
  string current_state_back = start_vertex;
  bool deadlock{false};
  while (goal_vertex.compare(current_state_back) != 0) {
    print_status_hc(graph, current_state_back,
                    get_successors(graph, current_state_back));
    deadlock = true;
    string best_v{};
    for (string v : get_successors(graph, current_state_back)) {
      if (get_heuristic(graph, v) < best_cost) {
        best_cost = get_heuristic(graph, v);
        best_v = v;
        deadlock = false;
      }
    }
    if (deadlock)
      break;
    else {
      current_state = to_search_node(graph, current_state, best_v);
      current_state_back = current_state.path.back();
    }
  }
  if (!deadlock) {
    print_status_hc(graph, current_state_back,
                    get_successors(graph, current_state_back));
    cout << "Path to goal node found: "
         << solution_path_cost(graph, current_state) << endl;
  } else
    cout << "Goal not found!" << endl;
}

void best_first_search(struct di_graph graph, string start_vertex,
                       string goal_vertex) {
  cout << "BestFS" << endl;
  set<string> closed{};
  priority_queue<search_node> frontier{}; // MIN HEAP
  frontier.push(
      to_search_node(start_vertex, get_heuristic(graph, start_vertex)));
  search_node current_state = frontier.top();
  string current_state_back = current_state.path.back();
  bool found{true};
  while (goal_vertex.compare(current_state_back) != 0) {
    print_status_bestfs(closed, priority_queue_to_list(frontier),
                        current_state_back,
                        get_successors(graph, current_state_back));
    frontier.pop();
    bool is_in{closed.find(current_state_back) != closed.end()};
    if (!is_in) {
      for (string v : get_successors(graph, current_state_back))
        frontier.push(to_bestfs_search_node(graph, current_state, v));
      closed.insert(current_state_back);
    }
    if (frontier.empty()) {
      found = false;
      break;
    }
    current_state = frontier.top();
    current_state_back = current_state.path.back();
  }
  if (found) {
    print_status_bestfs(closed, priority_queue_to_list(frontier),
                        current_state_back,
                        get_successors(graph, current_state_back));
    cout << "Path to goal node found: "
         << solution_path_compute_cost(graph, current_state) << endl;
  } else
    cout << "Goal not found!" << endl;
}

void alpha_star_search(struct di_graph graph, string start_vertex,
                       string goal_vertex) {
  cout << "A*" << endl;
  set<string> closed{};
  priority_queue<search_node> frontier{}; // MIN HEAP
  frontier.push(
      to_search_node(start_vertex, get_heuristic(graph, start_vertex)));
  search_node current_state = frontier.top();
  string current_state_back = current_state.path.back();
  bool found{true};
  while (goal_vertex.compare(current_state_back) != 0) {
    print_status_astar(closed, priority_queue_to_list(frontier),
                       current_state_back,
                       get_successors(graph, current_state_back));
    frontier.pop();
    bool is_in{closed.find(current_state_back) != closed.end()};
    if (!is_in) {
      for (string v : get_successors(graph, current_state_back))
        frontier.push(
            to_search_node(graph, current_state, v, get_heuristic(graph, v)));
      closed.insert(current_state_back);
    }
    if (frontier.empty()) {
      found = false;
      break;
    }
    current_state = frontier.top();
    current_state_back = current_state.path.back();
  }
  if (found) {
    print_status_astar(closed, priority_queue_to_list(frontier),
                       current_state_back,
                       get_successors(graph, current_state_back));
    cout << "Path to goal node found: "
         << solution_path_cost(graph, current_state) << endl;
  } else
    cout << "Goal not found!" << endl;
}