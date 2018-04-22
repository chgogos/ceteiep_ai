/***
 *       ___   ___   _____   ___   ___   ___   ___     ___    __    _   ____
 *      / __| | __| |_   _| | __| |_ _| | __| | _ \   |_  )  /  \  / | |__  |
 *     | (__  | _|    | |   | _|   | |  | _|  |  _/    / /  | () | | |   / /
 *      \___| |___|   |_|   |___| |___| |___| |_|     /___|  \__/  |_|  /_/
 *
 * TEI of Epirus - Department of Computer Engineering
 * Gogos Christos - Arta 2017
 */
#ifndef LAB03_BOARD_HPP_INCLUDED
#define LAB03_BOARD_HPP_INCLUDED

#include <cstdio>
#include <iostream>
#include <utility>
#include <list>
#include <vector>
#include <algorithm>
#include <climits>
#include <iomanip>
#include <random>

using namespace std;

const int ROWS{8};
const int COLS{8};

// αρχικοποίηση ταμπλό παιχνιδιού
char **initialize_board();

// σχεδίαση του ταμπλό στην οθόνη και απεικόνιση του σκορ
void draw_board(char **aboard);

// διάνυσμα με έγκυρες θέσεις στις οποίες μπροούν να τοποθετηθούν πούλια
vector<pair<int, int>> get_valid_positions(char **aboard, char disk);

// ενημέρωση του ταμπλό
void update_board(char **aboard, int r, int c, char disk);

// διαγραφή της μνήμης που καταλαμβάνει ένα ταμπλό
void delete_board(char **aboard);

// λίστα νέων ταμπλό που προκύπτουν αν τοποθετηθεί ένα πούλι τύπου (disk)
list<char **> get_successor_boards(char **aboard, char disk);

// αντιγραφή ενός ταμπλό
char **copy_board(char **aboard);

// πλήθος από πούλια τύπου disk
int get_disks_with_color(char **aboard, char disk);

#endif 