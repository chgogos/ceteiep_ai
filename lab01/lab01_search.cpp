/***
 *       ___   ___   _____   ___   ___   ___   ___     ___    __    _   ____
 *      / __| | __| |_   _| | __| |_ _| | __| | _ \   |_  )  /  \  / | |__  |
 *     | (__  | _|    | |   | _|   | |  | _|  |  _/    / /  | () | | |   / /
 *      \___| |___|   |_|   |___| |___| |___| |_|     /___|  \__/  |_|  /_/
 *
 * TEI of Epirus - Department of Computer Engineering
 * Gogos Christos - Arta 2017
 */
#include "lab01_search.hpp"

using namespace std;

void depth_first_search(struct di_graph graph, string start_vertex,
                        string goal_vertex) {
  cout << "DEPTH FIRST SEARCH" << endl;
  set<string> closed{};
  stack<search_node> frontier{}; // LIFO
  frontier.push(to_search_node(start_vertex));
  search_node current_state = frontier.top();
  string current_state_back = current_state.path.back();
  bool found{true};
  while (goal_vertex.compare(current_state_back) != 0) {
    print_status(closed, stack_to_list(frontier), current_state_back,
                 get_successors(graph, current_state_back));
    frontier.pop();
    bool is_in{closed.find(current_state_back) != closed.end()};
    if (!is_in) {
      // Οι γειτονικοί κόμβοι λαμβάνονται σε φθίνουσα αλφαβητική σειρά έτσι ώστε
      // όταν τοποθετηθούν στη στοίβα η τιμή που βρίσκεται στη κορυφή να είναι η
      // μικρότερη αλφαβητικά από αυτές που εισήχθησαν τελευταίες
      for (string v : get_successors(graph, current_state_back, false))
        frontier.push(to_search_node(graph, current_state, v));
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
    print_status(closed, stack_to_list(frontier), current_state_back,
                 get_successors(graph, current_state_back));
    cout << "Path to goal node found: "
         << solution_path_cost(graph, current_state) << endl;
  } else
    cout << "Goal not found!" << endl;
}

void breadth_first_search(struct di_graph graph, string start_vertex,
                          string goal_vertex) {
  cout << "BREADTH FIRST SEARCH" << endl;
  set<string> closed{};
  queue<search_node> frontier{}; // FIFO
  frontier.push(to_search_node(start_vertex));
  search_node current_state = frontier.front();
  string current_state_back = current_state.path.back();
  bool found{true};
  while (goal_vertex.compare(current_state_back) != 0) {
    print_status(closed, queue_to_list(frontier), current_state_back,
                 get_successors(graph, current_state_back));
    frontier.pop();
    bool is_in{closed.find(current_state_back) != closed.end()};
    if (!is_in) {
      for (string v : get_successors(graph, current_state_back))
        frontier.push(to_search_node(graph, current_state, v));
      closed.insert(current_state_back);
    }
    if (frontier.empty()) {
      found = false;
      break;
    }
    current_state = frontier.front();
    current_state_back = current_state.path.back();
  }
  if (found) {
    print_status(closed, queue_to_list(frontier), current_state_back,
                 get_successors(graph, current_state_back));
    cout << "Path to goal node found: "
         << solution_path_cost(graph, current_state) << endl;
  } else
    cout << "Goal not found!" << endl;
}

void uniform_cost_search(struct di_graph graph, string start_vertex,
                         string goal_vertex) {
  cout << "UNIFORM COST SEARCH" << endl;
  set<string> closed{};
  priority_queue<search_node> frontier{}; // MIN HEAP
  frontier.push(to_search_node(start_vertex));
  search_node current_state = frontier.top();
  string current_state_back = current_state.path.back();
  bool found{true};
  while (goal_vertex.compare(current_state_back) != 0) {
    print_status(closed, priority_queue_to_list(frontier), current_state_back,
                 get_successors(graph, current_state_back), true);
    frontier.pop();
    bool is_in{closed.find(current_state_back) != closed.end()};
    if (!is_in) {
      for (string v : get_successors(graph, current_state_back))
        frontier.push(to_search_node(graph, current_state, v));
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
    print_status(closed, priority_queue_to_list(frontier), current_state_back,
                 get_successors(graph, current_state_back), true);
    cout << "Path to goal node found: "
         << solution_path_cost(graph, current_state) << endl;
  } else
    cout << "Goal not found!" << endl;
}

list<search_node> stack_to_list(stack<search_node> frontier) {
  list<search_node> alist{};
  while (!frontier.empty()) {
    alist.push_back(frontier.top());
    frontier.pop();
  }
  return alist;
}

list<search_node> queue_to_list(queue<search_node> frontier) {
  list<search_node> alist{};
  while (!frontier.empty()) {
    alist.push_back(frontier.front());
    frontier.pop();
  }
  return alist;
}

list<search_node> priority_queue_to_list(priority_queue<search_node> frontier) {
  list<search_node> alist{};
  while (!frontier.empty()) {
    alist.push_back(frontier.top());
    frontier.pop();
  }
  return alist;
}

string search_node_as_string(search_node sn, bool show_path_cost) {
  string s{};
  s.append("(");
  for (string v : sn.path) {
    s.append(v);
    s.append("-");
  }
  if (s.length() > 1)
    s.pop_back();
  if (show_path_cost) {
    s.append(" ");
    s.append(to_string(sn.cost));
  }
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

void print_status(set<string> closed, list<search_node> frontier,
                  string current_state, list<string> successors,
                  bool show_path_cost) {
  cout << "frontier:[";
  for (search_node sn : frontier)
    cout << search_node_as_string(sn, show_path_cost);
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

search_node to_search_node(string node) {
  search_node sn{};
  sn.path.push_back(node);
  sn.cost = 0;
  return sn;
}

search_node to_search_node(di_graph graph, search_node parent_sn, string node) {
  search_node sn{};
  for (string v : parent_sn.path) {
    sn.path.push_back(v);
  }
  sn.path.push_back(node);
  sn.cost = parent_sn.cost + get_weight(graph, parent_sn.path.back(), node);
  return sn;
}
