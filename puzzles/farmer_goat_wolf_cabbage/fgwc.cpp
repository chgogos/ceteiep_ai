/***
 * TEI of Epirus - Department of Computer Engineering
 * Gogos Christos - Arta 2018
 */

#include <iostream>
#include <queue>
#include <set>
#include <vector>

using namespace std;

// η αναπαράσταση της κατάστασης γίνεται με ένα λεκτικό 4 χαρακτήρων με κάθε
// χαρακτήρα να μπορεί να είναι 'w' (west=δύση) ή 'e' (east=ανατολή)
//
// ο πρώτος χαρακτήρας αφορά τη θέση του αγρότη, ο δεύτερος χαρακτήρας αφορά τη
// θέση της κατσίκας, o τρίτος τη θέση του λύκου και ο τέταρτος τη θέση του
// λάχανου. Έτσι το λεκτικό "wwee" σημαίνει ότι ο αγρότης και η κατσίκα είναι
// στη δυτική όχθη ενώ ο λύκος και το λάχανο είναι στην ανατολική όχθη

char farmer_loc(string state) { return state[0]; }

char goat_loc(string state) { return state[1]; }

char wolf_loc(string state) { return state[2]; }

char cabbage_loc(string state) { return state[3]; }

char opposite_shore(char shore) {
  if (shore == 'w')
    return 'e';
  else
    return 'w';
}

bool is_valid(string state) {
  if ((wolf_loc(state) == goat_loc(state)) &&
      (farmer_loc(state) != goat_loc(state)))
    return false;
  if ((goat_loc(state) == cabbage_loc(state)) &&
      (farmer_loc(state) != goat_loc(state)))
    return false;
  return true;
}

vector<string> expand(string state) {
  vector<string> next_state_list;
  string new_state;

  // farmer goes to the opposite shore alone
  new_state = state;
  new_state[0] = opposite_shore(farmer_loc(state));
  if (is_valid(new_state))
    next_state_list.push_back(new_state);

  // farmer goes to the opposite shore with goat
  if (farmer_loc(state) == goat_loc(state)) {
    new_state = state;
    new_state[0] = opposite_shore(farmer_loc(state));
    new_state[1] = opposite_shore(goat_loc(state));
    if (is_valid(new_state))
      next_state_list.push_back(new_state);
  }

  // farmer goes to the opposite shore with wolf
  if (farmer_loc(state) == wolf_loc(state)) {
    new_state = state;
    new_state[0] = opposite_shore(farmer_loc(state));
    new_state[2] = opposite_shore(wolf_loc(state));
    if (is_valid(new_state))
      next_state_list.push_back(new_state);
  }

  // farmer goes to the opposite shore with cabbage
  if (farmer_loc(state) == cabbage_loc(state)) {
    new_state = state;
    new_state[0] = opposite_shore(farmer_loc(state));
    new_state[3] = opposite_shore(cabbage_loc(state));
    if (is_valid(new_state))
      next_state_list.push_back(new_state);
  }
  return next_state_list;
}

struct state_with_path {
  string state;
  vector<string> path;
};

void breadth_first_search(string start_state, string goal_state) {
  set<string> closed;
  queue<state_with_path> frontier;
  frontier.push({start_state, {start_state}});
  state_with_path current = frontier.front();
  while (current.state != goal_state) {
    frontier.pop();
    if (closed.find(current.state) == closed.end()) {
      for (string s : expand(current.state)) {
        state_with_path sp = {s, current.path};
        sp.path.push_back(s);
        frontier.push(sp);
      }
      closed.insert(current.state);
    }
    if (frontier.empty()) {
      cout << "goal not found";
      return;
    }
    current = frontier.front();
  }
  cout << "Path: ";
  for (string state : current.path)
    cout << state << " --> ";
  cout << "GOAL" << endl;
}

int main() { breadth_first_search("eeee", "wwww"); }
