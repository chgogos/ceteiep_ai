/***
 * TEI of Epirus - Department of Computer Engineering
 * Gogos Christos - Arta 2018
 */

#include "lab03_solvers.hpp"

void computer_move_using_simple_heuristic(char **board, char disk) {
  cout << "Computer using heuristic plays with disk " << disk << endl;
  int best_r{-1};
  int best_c{-1};
  int best_value{-1};
  vector<pair<int,int>> valid_moves = get_valid_positions(board, disk);
  default_random_engine gen;
  gen.seed(time(NULL));
  shuffle(valid_moves.begin(), valid_moves.end(), gen);
  for (pair<int, int> x : valid_moves) {
    char **duplicated_board = copy_board(board);
    int r{x.first};
    int c{x.second};
    update_board(duplicated_board, r, c, disk);
    int value = get_disks_with_color(duplicated_board, disk);
    if (value > best_value) {
      best_r = r;
      best_c = c;
      best_value = value;
    }
    cout << "(" << x.first << " " << x.second << ")->" << value << " ";
    delete_board(duplicated_board);
  }
  cout << endl;
  update_board(board, best_r, best_c, disk);
  draw_board(board);
}

// MINIMAX & ALPHA-BETA

// ευρετική συνάρτηση για την αριθμητική σχέση στα πούλια των δύο αντιπάλων
int parity(char **aboard) {
  int max_player_disks = get_disks_with_color(aboard, 'X');
  int min_player_disks = get_disks_with_color(aboard, 'O');
  return 100 * (max_player_disks - min_player_disks) /
         (max_player_disks + min_player_disks);
}

// ευρετική συνάρτηση για τη σχέση κινητικότητας ανάμεσα στους δύο αντιπάλους
int mobility(char **aboard) {
  int max_player_moves = get_valid_positions(aboard, 'X').size();
  int min_player_moves = get_valid_positions(aboard, 'O').size();
  if (max_player_moves + min_player_moves == 0)
    return 0;
  else
    return 100 * (max_player_moves - min_player_moves) /
           (max_player_moves + min_player_moves);
}

// αριθμός από γωνίες στις οποίες βρίσκεται πούλι τύπου disk
int player_corners(char **aboard, char disk) {
  int c{0};
  if (aboard[0][0] == disk)
    c++;
  if (aboard[0][COLS - 1] == disk)
    c++;
  if (aboard[ROWS - 1][0] == disk)
    c++;
  if (aboard[ROWS - 1][COLS - 1] == disk)
    c++;
  return c;
}

// ευρετική συνάρτηση για τη σχέση κατειλημμένων γωνιών από τους δύο αντιπάλους
int corners(char **aboard) {
  int max_player_corners = player_corners(aboard, 'X');
  int min_player_corners = player_corners(aboard, 'O');
  if (max_player_corners + min_player_corners == 0)
    return 0;
  else
    return 100 * (max_player_corners - min_player_corners) /
           (max_player_corners + min_player_corners);
}

// συνάρτηση χρησιμότητας
int utility(char **aboard) {
  return parity(aboard) + mobility(aboard) + corners(aboard);
}

bool is_complete(char **aboard) {
  int c{0};
  for (int i = 0; i < ROWS; i++)
    for (int j = 0; j < COLS; j++)
      if ((aboard[i][j] == 'X') || (aboard[i][j] == 'O'))
        c++;
  if (c == ROWS * COLS)
    return true;
  else
    return false;
}

int min_value(char **aboard, int plies);

int max_value(char **aboard, int plies) {
  if (is_complete(aboard) || plies == 0 ||
      get_valid_positions(aboard, 'O').empty())
    return utility(aboard);
  list<char **> succ_boards = get_successor_boards(aboard, 'O');
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
  if (is_complete(aboard) || plies == 0 ||
      get_valid_positions(aboard, 'X').empty())
    return utility(aboard);
  list<char **> succ_boards = get_successor_boards(aboard, 'X');
  int v = INT_MAX;
  for (char **b : succ_boards) {
    int v2 = max_value(b, plies - 1);
    if (v2 < v)
      v = v2;
    delete_board(b);
  }
  return v;
}

pair<int, int> minimax_decision(char **aboard, int plies, char disk) {
  if (disk == 'X') {
    int max = INT_MIN;
    pair<int, int> move;
    for (pair<int, int> p : get_valid_positions(aboard, disk)) {
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
    for (pair<int, int> p : get_valid_positions(aboard, disk)) {
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

void computer_move_using_min_max(char **board, int plies, char disk) {
  cout << "Computer using min-max plays with disk " << disk << endl;
  pair<int, int> p = minimax_decision(board, plies, disk);
  update_board(board, p.first, p.second, disk);
  draw_board(board);
}

int ab_min_value(char **aboard, int alpha, int beta, int plies);

int ab_max_value(char **aboard, int alpha, int beta, int plies) {
  if (is_complete(aboard) || plies == 0 ||
      get_valid_positions(aboard, 'O').empty())
    return utility(aboard);
  list<char **> succ_boards = get_successor_boards(aboard, 'O');
  int v = INT_MIN;
  for (char **b : succ_boards) {
    int v2 = ab_min_value(b, alpha, beta, plies - 1);
    if (v2 > v)
      v = v2;
    if (v >= beta) {
      delete_board(b);
      return v;
    }
    if (v > alpha)
      alpha = v;
    delete_board(b);
  }
  return v;
}

int ab_min_value(char **aboard, int alpha, int beta, int plies) {
  if (is_complete(aboard) || plies == 0 ||
      get_valid_positions(aboard, 'X').empty())
    return utility(aboard);
  list<char **> succ_boards = get_successor_boards(aboard, 'X');
  int v = INT_MAX;
  for (char **b : succ_boards) {
    int v2 = ab_max_value(b, alpha, beta, plies - 1);
    if (v2 < v)
      v = v2;
    if (v <= alpha) {
      delete_board(b);
      return v;
    }
    if (v < beta)
      beta = v;
    delete_board(b);
  }
  return v;
}

pair<int, int> ab_minimax_decision(char **aboard, int plies, char disk) {
  if (disk == 'X') {
    int max = INT_MIN;
    pair<int, int> move;
    for (pair<int, int> p : get_valid_positions(aboard, disk)) {
      char **b = copy_board(aboard);
      update_board(b, p.first, p.second, 'X');
      int v = ab_min_value(b, INT_MIN, INT_MAX, plies - 1);
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
    for (pair<int, int> p : get_valid_positions(aboard, disk)) {
      char **b = copy_board(aboard);
      update_board(b, p.first, p.second, 'O');
      int v = ab_max_value(b, INT_MIN, INT_MAX, plies - 1);
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

void computer_move_using_alpha_beta(char **board, int plies, char disk) {
  cout << "Computer using alpha-beta plays with disk " << disk << endl;
  pair<int, int> p = ab_minimax_decision(board, plies, disk);
  update_board(board, p.first, p.second, disk);
  draw_board(board);
}
