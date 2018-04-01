#include <iostream>
#include <vector>
#include <set>
#include <queue>

using namespace std;

// XYZWC means
// X missionaries at the left side of the river
// Y cannibals at the left side of the river
// Z = 0 ==> boat at the left side, 1==> boat at the right side of the river
// W missionaries at the right side of the river
// C cannibals at the right side of the river
// example: 22111   ==> MMCC |   <__>| MC

int missionaries_left(string state) {
    return state[0] - '0';
}

int cannibals_left(string state) {
    return state[1] - '0';
}

int missionaries_right(string state) {
    return state[3] - '0';
}

int cannibals_right(string state) {
    return state[4] - '0';
}

bool is_boat_left(string state) {
    return (state[2] == '0');
}

bool is_valid(string state) {
    if (missionaries_left(state) > 0 && missionaries_left(state) < cannibals_left(state))
        return false;
    else if (missionaries_right(state) > 0 && missionaries_right(state) < cannibals_right(state))
        return false;
    else
        return true;
}

vector<string> expand(string state) {
    vector<string> next_state_list;
    string new_state;
    cout << state << endl;
    if (is_boat_left(state)) {
        // 2M left to right
        if (missionaries_left(state) >= 2) {
            new_state = state;
            new_state[0] = missionaries_left(state) - 2 + '0';
            new_state[3] = missionaries_right(state) + 2 + '0';
            new_state[2] = '1';
            cout << "test " << new_state << " " << is_valid(new_state) << endl;
            if (is_valid(new_state))
                next_state_list.push_back(new_state);
        }

        // 2C left to right
        if (cannibals_left(state) >= 2) {
            new_state = state;
            new_state[1] = cannibals_left(state) - 2 + '0';
            new_state[4] = cannibals_right(state) + 2 + '0';
            new_state[2] = '1';
            cout << "test " << new_state << " " << is_valid(new_state) << endl;
            if (is_valid(new_state))
                next_state_list.push_back(new_state);
        }

        // 1M 1C left to right
        if ((missionaries_left(state) >= 1) && (cannibals_left(state) >= 1)) {
            new_state = state;
            new_state[0] = missionaries_left(state) - 1 + '0';
            new_state[3] = missionaries_right(state) + 1 + '0';
            new_state[1] = cannibals_left(state) - 1 + '0';
            new_state[4] = cannibals_right(state) + 1 + '0';
            new_state[2] = '1';
            cout << "test " << new_state << " " << is_valid(new_state) << endl;
            if (is_valid(new_state))
                next_state_list.push_back(new_state);
        }

        // 1M left to right
        if (missionaries_left(state) >= 1) {
            new_state = state;
            new_state[0] = missionaries_left(state) - 1 + '0';
            new_state[3] = missionaries_right(state) + 1 + '0';
            new_state[2] = '1';
            cout << "test " << new_state << " " << is_valid(new_state) << endl;
            if (is_valid(new_state))
                next_state_list.push_back(new_state);
        }

        // 1C left to right
        if (cannibals_left(state) >= 1) {
            new_state = state;
            new_state[1] = cannibals_left(state) - 1 + '0';
            new_state[4] = cannibals_right(state) + 1 + '0';
            new_state[2] = '1';
            cout << "test " << new_state << " " << is_valid(new_state) << endl;
            if (is_valid(new_state))
                next_state_list.push_back(new_state);
        }
    } else {
        // 2M right to left
        if (missionaries_right(state) >= 2) {
            new_state = state;
            new_state[0] = missionaries_left(state) + 2 + '0';
            new_state[3] = missionaries_right(state) - 2 + '0';
            new_state[2] = '0';
            cout << "test " << new_state << " " << is_valid(new_state) << endl;
            if (is_valid(new_state))
                next_state_list.push_back(new_state);
        }

        // 2C right to left
        if (cannibals_right(state) >= 2) {
            new_state = state;
            new_state[1] = cannibals_left(state) + 2 + '0';
            new_state[4] = cannibals_right(state) - 2 + '0';
            new_state[2] = '0';
            cout << "test " << new_state << " " << is_valid(new_state) << endl;
            if (is_valid(new_state))
                next_state_list.push_back(new_state);

        }

        // 1M 1C right to left
        if (missionaries_right(state) >= 1 && cannibals_right(state) >= 1) {
            new_state = state;
            new_state[0] = missionaries_left(state) + 1 + '0';
            new_state[3] = missionaries_right(state) - 1 + '0';
            new_state[1] = cannibals_left(state) + 1 + '0';
            new_state[4] = cannibals_right(state) - 1 + '0';
            new_state[2] = '0';
            cout << "test " << new_state << " " << is_valid(new_state) << endl;
            if (is_valid(new_state))
                next_state_list.push_back(new_state);
        }

        // 1M right to left
        if (missionaries_right(state) >= 1) {
            new_state = state;
            new_state[0] = missionaries_left(state) + 1 + '0';
            new_state[3] = missionaries_right(state) - 1 + '0';
            new_state[2] = '0';
            cout << "test " << new_state << " " << is_valid(new_state) << endl;
            if (is_valid(new_state))
                next_state_list.push_back(new_state);

        }

        // 1C right to left
        if (cannibals_right(state) >= 1) {
            new_state = state;
            new_state[1] = cannibals_left(state) + 1 + '0';
            new_state[4] = cannibals_right(state) - 1 + '0';
            new_state[2] = '0';
            cout << "test " << new_state << " " << is_valid(new_state) << endl;
            if (is_valid(new_state))
                next_state_list.push_back(new_state);
        }
        return next_state_list;
    }

}

bool goal(string state) {
    return state == "00133";
}

struct state_with_path {
    string state;
    vector<string> path;
};

string pretty_print(string state) {
    string s = "";
    for (int i = 0; i < missionaries_left(state); i++)
        s.append("M");
    for (int i = 0; i < cannibals_left(state); i++)
        s.append("C");
    for (int i = missionaries_left(state) + cannibals_left(state); i < 6; i++)
        s.append(" ");
    if (state[2] == '0')
        s.append(" |<__>     | ");
    else
        s.append(" |     <__>| ");
    for (int i = 0; i < missionaries_right(state); i++)
        s.append("M");
    for (int i = 0; i < cannibals_right(state); i++)
        s.append("C");
    for (int i = missionaries_right(state) + cannibals_right(state); i < 6; i++)
        s.append(" ");
    return s;
}

// BFS add hoc
void breadth_first_search(string start_state) {
    set<string> closed;
    queue<state_with_path> frontier;
    frontier.push({start_state, {start_state}});
    state_with_path current = frontier.front();
    while (!goal(current.state)) {
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
    cout << "Path: " << endl;
    for (string s : current.path)
        cout << pretty_print(s)  << endl ;
    cout << "GOAL" << endl;
}

void test() {
    for (string state : expand("33000"))
        cout << state << endl;
}

int main() {
    breadth_first_search("33000");
}
