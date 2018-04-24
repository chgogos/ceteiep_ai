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
#include "lab03_human.hpp"
#include "lab03_solvers.hpp"

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
    if (!(get_valid_positions(board, 'X').empty())) {
      computer_move_using_simple_heuristic(board, 'X');
      player1_moved = true;
      moves++;
    }
    if (!(get_valid_positions(board, 'O').empty())) {
      computer_move_using_alpha_beta(board, 5, 'O');
      player2_moved = true;
      moves++;
    }
    if ((moves == ROWS * COLS - 4) || (!player1_moved && !player2_moved))
      flag = true;
  }
  delete_board(board);
}
