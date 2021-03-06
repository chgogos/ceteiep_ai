/***
 *       ___   ___   _____   ___   ___   ___   ___     ___    __    _   ____
 *      / __| | __| |_   _| | __| |_ _| | __| | _ \   |_  )  /  \  / | |__  |
 *     | (__  | _|    | |   | _|   | |  | _|  |  _/    / /  | () | | |   / /
 *      \___| |___|   |_|   |___| |___| |___| |_|     /___|  \__/  |_|  /_/
 *
 * TEI of Epirus - Department of Computer Engineering
 * Gogos Christos - Arta 2017
 */

#ifndef __LAB03_SOLVERS_HPP__
#define __LAB03_SOLVERS_HPP__

#include "lab03_board.hpp"

// η κίνηση που θα γίνει αποφασίζεται από μια απλή ευρετική συνάρτηση που
// μετρά για κάθε έγκυρη θέση τον αριθμό από πούλια που θα προκύψει
// και επιλέγει την κίνηση με τη μεγαλύτερη τιμή
void computer_move_using_simple_heuristic(char **board, char disk);

void computer_move_using_min_max(char **board, int plies, char disk);

void computer_move_using_alpha_beta(char **board, int plies, char disk);

#endif