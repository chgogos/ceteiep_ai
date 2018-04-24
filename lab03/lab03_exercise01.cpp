/***
 *       ___   ___   _____   ___   ___   ___   ___     ___    __    _   ____
 *      / __| | __| |_   _| | __| |_ _| | __| | _ \   |_  )  /  \  / | |__  |
 *     | (__  | _|    | |   | _|   | |  | _|  |  _/    / /  | () | | |   / /
 *      \___| |___|   |_|   |___| |___| |___| |_|     /___|  \__/  |_|  /_/
 *
 * TEI of Epirus - Department of Computer Engineering
 * Gogos Christos - Arta 2017
 */

#include "lab03_board.hpp"

int main() {
  default_random_engine gen;
  gen.seed(time(NULL));
  char **board = initialize_board();
  bool flag{false};
  int moves{0};
  draw_board(board);
  while (!flag) {
    bool player1_moved{false};
    bool player2_moved{false};
    vector<pair<int, int>> valid_pairs_x = get_valid_positions(board, 'X');
    if (!(valid_pairs_x.empty())) {
      shuffle(valid_pairs_x.begin(), valid_pairs_x.end(), gen);
      pair<int, int> p = valid_pairs_x.front();
      update_board(board, p.first, p.second, 'X');
      player1_moved = true;
      moves++;
    }
    vector<pair<int, int>> valid_pairs_o = get_valid_positions(board, 'O');
    if (!(valid_pairs_o.empty())) {
      shuffle(valid_pairs_o.begin(), valid_pairs_o.end(), gen);
      pair<int, int> p = valid_pairs_o.front();
      update_board(board, p.first, p.second, 'O');
      player2_moved = true;
      moves++;
    }
    if ((moves == ROWS * COLS - 4) || (!player1_moved && !player2_moved))
      flag = true;
  }
  draw_board(board);
  delete_board(board);
}