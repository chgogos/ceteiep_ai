/***
 *       ___   ___   _____   ___   ___   ___   ___     ___    __    _   ____
 *      / __| | __| |_   _| | __| |_ _| | __| | _ \   |_  )  /  \  / | |__  |
 *     | (__  | _|    | |   | _|   | |  | _|  |  _/    / /  | () | | |   / /
 *      \___| |___|   |_|   |___| |___| |___| |_|     /___|  \__/  |_|  /_/
 *
 * TEI of Epirus - Department of Computer Engineering
 * Gogos Christos - Arta 2017
 */

#include "lab03_human.hpp"

void human_move(char** board, char disk) {
	if (disk == 'X')
		cout << "Player X turn, valid moves=";
	else
		cout << "Player O turn, valid moves=";
	vector<pair<int, int>> valid_pairs = get_valid_positions(board, disk);
	for (pair<int, int> x : valid_pairs)
		cout << "(" << x.first << " " << x.second << ")";
	int r { }, c { };
	do {
		cout << endl << "Enter move:";
		cin >> r >> c;
	} while (find(valid_pairs.begin(), valid_pairs.end(), make_pair(r, c))
			== valid_pairs.end());
	update_board(board, r, c, disk);
	draw_board(board);
} 