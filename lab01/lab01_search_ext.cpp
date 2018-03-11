/***
 *       ___   ___   _____   ___   ___   ___   ___     ___    __    _   ____
 *      / __| | __| |_   _| | __| |_ _| | __| | _ \   |_  )  /  \  / | |__  |
 *     | (__  | _|    | |   | _|   | |  | _|  |  _/    / /  | () | | |   / /
 *      \___| |___|   |_|   |___| |___| |___| |_|     /___|  \__/  |_|  /_/
 *
 * TEI of Epirus - Department of Computer Engineering
 * Gogos Christos - Arta 2017
 */
#include "lab01_search_ext.hpp"

using namespace std;

void breadth_first_search_alt(struct di_graph graph, string start_vertex,
                              string goal_vertex) {
  cout << "BREADTH FIRST SEARCH ALTERNATIVE IMPLEMENTATION" << endl;
  set<string> closed{};
  queue<search_node> frontier{}; // FIFO
  frontier.push(to_search_node(start_vertex));
  bool found{false};
  while (true) {
    if (frontier.empty())
      break;
    search_node current_state = frontier.front();
    string current_state_back = current_state.path.back();
    print_status(closed, queue_to_list(frontier), current_state_back,
                 get_successors(graph, current_state_back));
    frontier.pop();
    if (goal_vertex.compare(current_state_back) == 0) {
      cout << "Path to goal node found: "
           << solution_path_cost(graph, current_state) << endl;
      found = true;
      break;
    }
    bool is_in{closed.find(current_state_back) != closed.end()};
    if (!is_in) {
      closed.insert(current_state_back);
      for (string v : get_successors(graph, current_state_back))
        frontier.push(to_search_node(graph, current_state, v));
    }
  }
  if (!found)
    cout << "Goal not found!" << endl;
}

void breadth_first_search_recursive(struct di_graph graph, string start_vertex,
                                    string goal_vertex) {
  cout << "BREADTH FIRST SEARCH ALTERNATIVE IMPLEMENTATION (RECURSIVE)" << endl;
  list<search_node> new_nodes{to_search_node(start_vertex)};
  set<string> closed{};
  search_node sn = bfs_r(graph, closed, new_nodes, goal_vertex);
  if (!sn.is_goal)
    cout << "Goal not found!" << endl;
  else
    cout << "Path to goal node found: " << solution_path_cost(graph, sn)
         << endl;
}

search_node bfs_r(struct di_graph graph, set<string> closed,
                  list<search_node> node_list, string goal_vertex) {
  list<search_node> new_nodes{};
  for (search_node current_state : node_list) {
    string current_state_back = current_state.path.back();
    if (goal_vertex.compare(current_state_back) == 0) {
      current_state.is_goal = true;
      return current_state;
    } else if (closed.find(current_state_back) == closed.end()) {
      for (string v : get_successors(graph, current_state_back))
        new_nodes.push_back(to_search_node(graph, current_state, v));
      closed.insert(current_state_back);
    }
  }
  if (new_nodes.size() != 0)
    return bfs_r(graph, closed, new_nodes, goal_vertex);
  else
    return to_search_node("Goal not found");
}

void depth_first_search_alt(struct di_graph graph, string start_vertex,
                            string goal_vertex) {
  cout << "DEPTH FIRST SEARCH ALTERNATIVE IMPLEMENTATION" << endl;
  set<string> closed{};
  stack<search_node> frontier{};
  frontier.push(to_search_node(start_vertex));
  bool found{false};
  while (true) {
    if (frontier.empty())
      break;
    search_node current_state = frontier.top();
    string current_state_back = current_state.path.back();
    print_status(closed, stack_to_list(frontier), current_state_back,
                 get_successors(graph, current_state_back));
    frontier.pop();
    if (goal_vertex.compare(current_state_back) == 0) {
      cout << "Path to goal node found: "
           << solution_path_cost(graph, current_state) << endl;
      found = true;
      break;
    }
    bool is_in{closed.find(current_state_back) != closed.end()};
    if (!is_in) {
      closed.insert(current_state_back);
      for (string v : get_successors(graph, current_state_back, false))
        frontier.push(to_search_node(graph, current_state, v));
    }
  }
  if (!found)
    cout << "Goal not found!" << endl;
}

void depth_first_search_recursive(struct di_graph graph, string start_vertex,
                                  string goal_vertex) {
  cout << "DEPTH FIRST SEARCH ALTERNATIVE IMPLEMENTATION (RECURSIVE)" << endl;
  set<string> closed{};
  search_node sn =
      dfs_r(graph, closed, to_search_node(start_vertex), goal_vertex);
  if (!sn.is_goal)
    cout << "Goal not found!" << endl;
  else
    cout << "Path to goal node found: " << solution_path_cost(graph, sn)
         << endl;
}

search_node dfs_r(struct di_graph graph, set<string> closed,
                  search_node current_state, string goal_vertex) {
  string current_state_back = current_state.path.back();
  if (goal_vertex.compare(current_state_back) == 0) {
    current_state.is_goal = true;
    return current_state;
  }
  if (closed.find(current_state_back) != closed.end())
    return to_search_node("state in closed set");
  list<search_node> new_nodes{};
  for (string v : get_successors(graph, current_state_back))
    new_nodes.push_back(to_search_node(graph, current_state, v));
  closed.insert(current_state_back);
  while (!new_nodes.empty()) {
    search_node result = dfs_r(graph, closed, new_nodes.front(), goal_vertex);
    if (result.is_goal)
      return result;
    new_nodes.pop_front();
  }
  return to_search_node("Goal not found");
}

void uniform_cost_search_alt(struct di_graph graph, string start_vertex,
                             string goal_vertex) {
  cout << "UNIFORM COST SEARCH ALTERNATIVE IMPLEMENTATION" << endl;
  set<string> closed{};
  priority_queue<search_node> frontier{};
  frontier.push(to_search_node(start_vertex));
  bool found{false};
  while (true) {
    if (frontier.empty())
      break;
    search_node current_state = frontier.top();
    string current_state_back = current_state.path.back();
    print_status(closed, priority_queue_to_list(frontier), current_state_back,
                 get_successors(graph, current_state_back), true);
    frontier.pop();
    if (goal_vertex.compare(current_state_back) == 0) {
      cout << "Path to goal node found: "
           << solution_path_cost(graph, current_state) << endl;
      found = true;
      break;
    }
    bool is_in{closed.find(current_state_back) != closed.end()};
    if (!is_in) {
      closed.insert(current_state_back);
      for (string v : get_successors(graph, current_state_back))
        frontier.push(to_search_node(graph, current_state, v));
    }
  }
  if (!found)
    cout << "Goal not found!" << endl;
}