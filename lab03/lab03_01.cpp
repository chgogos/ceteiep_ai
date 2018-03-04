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
  draw_board(board);
  vector<pair<int, int>> valid_pairs_x = get_valid_positions(board, 'X');
  cout << "Valid moves for X: ";
  for (pair<int, int> p : valid_pairs_x)
    cout << "(" << p.first << "," << p.second << ") ";
  shuffle(valid_pairs_x.begin(), valid_pairs_x.end(), gen);
  pair<int, int> p = valid_pairs_x.front();
  cout << "Move selected: (" << p.first << "," << p.second << ")" << endl;
  update_board(board, p.first, p.second, 'X');
  draw_board(board);
  int c = 0;
  for (char **b : get_successor_boards(board, 'O')) {
    cout << "\nPossible next board " << ++c << endl;
    draw_board(b);
    delete_board(b);
  }
  delete_board(board);
}