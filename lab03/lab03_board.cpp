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

// αντιγραφή ενός ταμπλό
char **copy_board(char **aboard) {
  char **duplicated_board = new char *[ROWS];
  for (int i = 0; i < ROWS; i++)
    duplicated_board[i] = new char[COLS];
  for (int i = 0; i < ROWS; i++)
    for (int j = 0; j < COLS; j++)
      duplicated_board[i][j] = aboard[i][j];
  return duplicated_board;
}

// είναι οι συντεταγμένες r, c (γραμμή και στήλη) εντός των ορίων του ταμπλό;
bool in_bounds(int r, int c) {
  return (r >= 0 && r < ROWS && c >= 0 && c < COLS);
}

// λίστα με πούλια που θα άλλάξουν χρώμα στην κατεύθυνση που υποδηλώνεται από τα
// xdir, ydir
list<pair<int, int>> disks_to_flip(char **aboard, int r, int c, char disk,
                                   int xdir, int ydir) {
  aboard[r][c] = disk;
  char opposite_disk;
  if (disk == 'X')
    opposite_disk = 'O';
  else
    opposite_disk = 'X';
  int x = r, y = c;
  x += xdir;
  y += ydir;
  list<pair<int, int>> disks_to_flip{};
  if (in_bounds(x, y) && aboard[x][y] == opposite_disk) {
    x += xdir;
    y += ydir;
    if (in_bounds(x, y)) {
      while (aboard[x][y] == opposite_disk) {
        x += xdir;
        y += ydir;
        if (!in_bounds(x, y)) {
          break;
        }
      }
      if (in_bounds(x, y))
        if (aboard[x][y] == disk)
          while (true) {
            x -= xdir;
            y -= ydir;
            if ((x == r) && (y == c))
              break;
            disks_to_flip.push_back(make_pair(x, y));
          }
    }
  }
  aboard[r][c] = ' ';
  return disks_to_flip;
}

// λίστα με πούλια που θα αλλάξουν χρώμα σε όλες τις κατευθύνσεις
list<pair<int, int>> all_directions_disks_to_flip(char **aboard, int r, int c,
                                                  char disk) {
  list<pair<int, int>> list_of_disks_to_flip{};
  int directions[8][2] = {{0, 1},  {1, 1},   {1, 0},  {1, -1},
                          {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};
  for (int i = 0; i < 8; i++) {
    list<pair<int, int>> l =
        disks_to_flip(aboard, r, c, disk, directions[i][0], directions[i][1]);
    list_of_disks_to_flip.insert(list_of_disks_to_flip.end(), l.begin(),
                                 l.end());
  }
  return list_of_disks_to_flip;
}

char **initialize_board() {
  char **board = new char *[ROWS] {};
  for (int i = 0; i < ROWS; i++) {
    board[i] = new char[COLS]{};
    for (int j = 0; j < COLS; j++)
      board[i][j] = ' ';
  }
  board[ROWS / 2 - 1][COLS / 2 - 1] = 'X';
  board[ROWS / 2 - 1][COLS / 2] = 'O';
  board[ROWS / 2][COLS / 2] = 'X';
  board[ROWS / 2][COLS / 2 - 1] = 'O';
  return board;
}

int get_disks_with_color(char **aboard, char disk) {
  int c{0};
  for (int i = 0; i < ROWS; i++)
    for (int j = 0; j < COLS; j++)
      if (aboard[i][j] == disk)
        c++;
  return c;
}

void display_score(char **aboard) {
  cout << "Score X=" << get_disks_with_color(aboard, 'X')
       << " O=" << get_disks_with_color(aboard, 'O') << endl;
}

void draw_board(char **aboard) {
  cout << "  ";
  for (int j = 0; j < COLS; j++)
    cout << setw(2) << right << j;
  cout << endl;
  for (int i = 0; i < ROWS; i++) {
    cout << setw(2) << right << i << "|";
    for (int j = 0; j < ROWS; j++)
      cout << setw(1) << aboard[i][j] << "|";
    cout << endl;
  }
  display_score(aboard);
}

vector<pair<int, int>> get_valid_positions(char **aboard, char disk) {
  vector<pair<int, int>> valid_moves{};
  for (int i = 0; i < ROWS; i++)
    for (int j = 0; j < COLS; j++)
      if (aboard[i][j] == ' ') {
        if (!all_directions_disks_to_flip(aboard, i, j, disk).empty())
          valid_moves.push_back(make_pair(i, j));
      }
  return valid_moves;
}

void update_board(char **aboard, int r, int c, char disk) {
  for (pair<int, int> p : all_directions_disks_to_flip(aboard, r, c, disk)) {
    aboard[p.first][p.second] = disk;
  }
  aboard[r][c] = disk;
}

void delete_board(char **aboard) {
  for (int i = 0; i < ROWS; i++)
    delete[] aboard[i];
  delete[] aboard;
}

list<char **> get_successor_boards(char **aboard, char disk) {
  list<char **> successors{};
  for (pair<int, int> p : get_valid_positions(aboard, disk)) {
    char **b = copy_board(aboard);
    update_board(b, p.first, p.second, disk);
    successors.push_back(b);
  }
  return successors;
}