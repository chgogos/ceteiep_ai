/***
 *       ___   ___   _____   ___   ___   ___   ___     ___    __    _   ____
 *      / __| | __| |_   _| | __| |_ _| | __| | _ \   |_  )  /  \  / | |__  |
 *     | (__  | _|    | |   | _|   | |  | _|  |  _/    / /  | () | | |   / /
 *      \___| |___|   |_|   |___| |___| |___| |_|     /___|  \__/  |_|  /_/
 *
 * TEI of Epirus - Department of Computer Engineering
 * Gogos Christos - Arta 2017
 */
#include "lab01_search_simple_exercise04.hpp"
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>


using namespace std;

int breadth_first_search_base(struct di_graph graph, string start_vertex,
                              string goal_vertex) {
  cout << "BREADTH FIRST SEARCH" << endl;
  unordered_map<string, int> hm;
  set<string> closed{};
  queue<string> frontier{}; // FIFO
  frontier.push(start_vertex);
  string current_state = frontier.front();
  hm[current_state] = 0;
  bool found{true};
  cout << "Starting from node " << start_vertex << endl;
  int c = 0;
  while (goal_vertex.compare(current_state) != 0) {
    frontier.pop();
    bool is_in{closed.find(current_state) != closed.end()};
    if (!is_in) {
      for (string v : get_successors(graph, current_state)) {
        frontier.push(v);
        hm[v] = hm[current_state] + get_weight(graph, current_state, v);
      }
      closed.insert(current_state);
    } else
      c++;
    if (frontier.empty()) {
      found = false;
      break;
    }
    current_state = frontier.front();
    cout << "current state: " << current_state << endl;
  }
  if (found)
    cout << "Path from " << start_vertex << " to " << goal_vertex
         << " found having length " << hm[goal_vertex] << endl;
  else
    cout << "Path from " << start_vertex << " to " << goal_vertex
         << " was not found!" << endl;
  return c;
}

int depth_first_search_base(struct di_graph graph, string start_vertex,
                            string goal_vertex) {
  cout << "DEPTH FIRST SEARCH" << endl;
  unordered_map<string, int> hm;
  set<string> closed{};
  stack<string> frontier{}; // LIFO
  frontier.push(start_vertex);
  string current_state = frontier.top();
  hm[current_state] = 0;
  bool found{true};
  cout << "Starting from node " << start_vertex << endl;
  int c = 0;
  while (goal_vertex.compare(current_state) != 0) {
    frontier.pop();
    bool is_in{closed.find(current_state) != closed.end()};
    if (!is_in) {
      for (string v : get_successors(graph, current_state, false)) {
        frontier.push(v);
        hm[v] = hm[current_state] + get_weight(graph, current_state, v);
      }
      closed.insert(current_state);
    } else
      c++;
    if (frontier.empty()) {
      found = false;
      break;
    }
    current_state = frontier.top();
    cout << "current state: " << current_state << endl;
  }
  if (found)
    cout << "Path from " << start_vertex << " to " << goal_vertex
         << " found having length " << hm[goal_vertex] << endl;
  else
    cout << "Path from " << start_vertex << " to " << goal_vertex
         << " was not found!" << endl;
  return c;
}