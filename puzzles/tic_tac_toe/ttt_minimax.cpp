/***
 * TEI of Epirus - Department of Computer Engineering
 * Gogos Christos - Arta 2018
 */

#include <algorithm> // find
#include <climits>   // INT_MIN
#include <iomanip>
#include <iostream>
#include <list>
#include <random>  // default_random_engine
#include <utility> // pair
#include <vector>

using namespace std;

default_random_engine gen;

char **initialize_board() {
  char **board = new char *[3]{};
  for (int i = 0; i < 3; i++) {
    board[i] = new char[3]{};
    for (int j = 0; j < 3; j++)
      board[i][j] = ' ';
  }
  return board;
}

char **copy_board(char **aboard) {
  char **duplicated_board = new char *[3];
  for (int i = 0; i < 3; i++)
    duplicated_board[i] = new char[3];
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      duplicated_board[i][j] = aboard[i][j];
  return duplicated_board;
}

void delete_board(char **aboard) {
  for (int i = 0; i < 3; i++)
    delete[] aboard[i];
  delete[] aboard;
}

void draw_board(char **aboard) {
  cout << "  ";
  for (int j = 0; j < 3; j++)
    cout << setw(2) << right << j;
  cout << endl;
  for (int i = 0; i < 3; i++) {
    cout << setw(2) << right << i << "|";
    for (int j = 0; j < 3; j++)
      cout << setw(1) << aboard[i][j] << "|";
    cout << endl;
  }
}

// returns 'X' if X wins, 'O' if O wins, 'D' if draw, 'N' if the game is not
// finished
char game_status(char **board) {
  for (int i = 0; i < 3; i++) {
    if (board[i][0] == board[i][1] && board[i][1] == board[i][2] &&
        board[i][0] != ' ')
      return board[i][0];
  }
  for (int j = 0; j < 3; j++) {
    if (board[0][j] == board[1][j] && board[1][j] == board[2][j] &&
        board[0][j] != ' ')
      return board[0][j];
  }
  if (board[0][0] == board[1][1] && board[1][1] == board[2][2] &&
      board[0][0] != ' ')
    return board[0][0];
  if (board[0][2] == board[1][1] && board[1][1] == board[2][0] &&
      board[0][2] != ' ')
    return board[0][2];
  int c = 0;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      if (board[i][j] != ' ')
        c++;
  if (c == 9)
    return 'D'; // DRAW
  return 'N';   // NOT FINISHED
}

void update_board(char **board, int r, int c, char symbol) {
  board[r][c] = symbol;
}

vector<pair<int, int>> get_valid_positions(char **aboard) {
  vector<pair<int, int>> valid_moves{};
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      if (aboard[i][j] == ' ') {
        valid_moves.push_back(make_pair(i, j));
      }
  return valid_moves;
}

void human_move(char **board, char symbol) {
  vector<pair<int, int>> valid_pairs = get_valid_positions(board);
  for (pair<int, int> x : valid_pairs)
    cout << "(" << x.first << " " << x.second << ")";
  int r{}, c{};
  do {
    cout << endl << "Enter move:";
    cin >> r >> c;
  } while (find(valid_pairs.begin(), valid_pairs.end(), make_pair(r, c)) ==
           valid_pairs.end());
  update_board(board, r, c, symbol);
}

void random_move(char **board, char symbol) {
  vector<pair<int, int>> valid_pairs = get_valid_positions(board);
  shuffle(valid_pairs.begin(), valid_pairs.end(), gen);
  update_board(board, valid_pairs[0].first, valid_pairs[0].second, symbol);
}

bool is_complete(char **aboard) {
  int c{0};
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      if ((aboard[i][j] == 'X') || (aboard[i][j] == 'O'))
        c++;
  if (c == 9)
    return true;
  else
    return false;
}

list<char **> get_successor_boards(char **aboard, char disk) {
  list<char **> successors{};
  for (pair<int, int> p : get_valid_positions(aboard)) {
    char **b = copy_board(aboard);
    update_board(b, p.first, p.second, disk);
    successors.push_back(b);
  }
  return successors;
}

int heuristic(char **aboard) {
  vector<pair<int, int>> v;
  for (int i = 0; i < 3; i++) {
    int x = 0, o = 0;
    for (int j = 0; j < 3; j++) {
      if (aboard[i][j] == 'X')
        x++;
      else if (aboard[i][j] == 'O')
        o++;
    }
    v.push_back(make_pair(x, o));
  }
  for (int j = 0; j < 3; j++) {
    int x = 0, o = 0;
    for (int i = 0; i < 3; i++) {
      if (aboard[i][j] == 'X')
        x++;
      else if (aboard[i][j] == 'O')
        o++;
    }
    v.push_back(make_pair(x, o));
  }
  int x = 0, o = 0;
  for (int i = 0; i < 3; i++) {
    if (aboard[i][i] == 'X')
      x++;
    if (aboard[i][i] == 'O')
      o++;
  }
  v.push_back(make_pair(x, o));
  x = 0;
  o = 0;
  for (int i = 0; i < 3; i++) {
    if (aboard[i][2 - i] == 'X')
      x++;
    if (aboard[i][2 - i] == 'O')
      o++;
  }
  v.push_back(make_pair(x, o));
  int score = 0;
  for (pair<int, int> p : v) {
    if (p.first == 2 && p.second == 0)
      score += 3;
    if (p.first == 1 && p.second == 0)
      score += 1;
    if (p.second == 2 && p.first == 0)
      score -= 3;
    if (p.second == 1 && p.first == 0)
      score -= 1;
  }
  return score;
}

int utility(char **aboard) {
  int score = 0;
  if (game_status(aboard) == 'X')
    score = 100;
  else if (game_status(aboard) == 'O')
    score = -100;
  else if (game_status(aboard) == 'D')
    score = 0;
  else {
    score = heuristic(aboard);
  }
  return score;
}

int min_value(char **aboard, int plies);

int max_value(char **aboard, int plies) {
  if (is_complete(aboard) || plies == 0 || game_status(aboard) == 'X' ||
      game_status(aboard) == 'O')
    return utility(aboard);
  list<char **> succ_boards = get_successor_boards(aboard, 'X');
  int v = INT_MIN;
  for (char **b : succ_boards) {
    int v2 = min_value(b, plies - 1);
    if (v2 > v)
      v = v2;
    delete_board(b);
  }
  return v;
}

int min_value(char **aboard, int plies) {
  if (is_complete(aboard) || plies == 0 || game_status(aboard) == 'X' ||
      game_status(aboard) == 'O')
    return utility(aboard);
  list<char **> succ_boards = get_successor_boards(aboard, 'O');
  int v = INT_MAX;
  for (char **b : succ_boards) {
    int v2 = max_value(b, plies - 1);
    if (v2 < v)
      v = v2;
    delete_board(b);
  }
  return v;
}

pair<int, int> minimax_decision(char **aboard, int plies, char symbol) {
  if (symbol == 'X') {
    int max = INT_MIN;
    pair<int, int> move;
    for (pair<int, int> p : get_valid_positions(aboard)) {
      char **b = copy_board(aboard);
      update_board(b, p.first, p.second, 'X');
      int v = min_value(b, plies - 1);
      if (v > max) {
        max = v;
        move.first = p.first;
        move.second = p.second;
      }
      delete_board(b);
    }
    return move;
  } else {
    int min = INT_MAX;
    pair<int, int> move;
    for (pair<int, int> p : get_valid_positions(aboard)) {
      char **b = copy_board(aboard);
      update_board(b, p.first, p.second, 'O');
      int v = max_value(b, plies - 1);
      if (v < min) {
        min = v;
        move.first = p.first;
        move.second = p.second;
      }
      delete_board(b);
    }
    return move;
  }
}

void computer_move_using_min_max(char **board, int plies, char symbol) {
  pair<int, int> p = minimax_decision(board, plies, symbol);
  update_board(board, p.first, p.second, symbol);
}

// random move automatic player vs minimax
void game1(int plies) {
  char **board = initialize_board();
  gen.seed(time(NULL));

  // draw_board(board);
  while (1) {
    random_move(board, 'X');
    // draw_board(board);
    if (game_status(board) != 'N') {
      break;
    }
    computer_move_using_min_max(board, plies, 'O');
    // draw_board(board);
    if (game_status(board) != 'N') {
      break;
    }
  }
  cout << "Τhe winner is " << game_status(board) << endl;
  delete_board(board);
}

// human player vs minimax
void game2(int plies) {
  char **board = initialize_board();
  gen.seed(time(NULL));

  draw_board(board);
  while (1) {
    human_move(board, 'X');
    draw_board(board);
    if (game_status(board) != 'N') {
      break;
    }
    computer_move_using_min_max(board, plies, 'O');
    draw_board(board);
    if (game_status(board) != 'N') {
      break;
    }
  }
  cout << "Τhe winner is " << game_status(board) << endl;
  delete_board(board);
}

int main() {
  // for (int i = 0; i < 80; i++)
  //   game1(8);

  game2(8);
}
