/***
 * TEI of Epirus - Department of Computer Engineering
 * Gogos Christos - Arta 2018
 */

#include <cstdlib> // abs, rand
#include <ctime>
#include <iostream>

// αν η διαφορά ανάμεσα στις γραμμές δύο βασιλισσών είναι ίση κατ' απόλυτη τιμή
// με τη διαφορά ανάμεσα στις στήλες για τις ίδιες βασίλισσες τότε η μια απειλεί
// την άλλη μέσω της διαγωνίου

using namespace std;

const int N = 8;

// για κάθε γραμμή αποθηκεύεται η στήλη στην οποία βρίσκεται η βασίλισσά της
int collisions(int board[N]) {
  int c = 0;
  for (int q1_row = 0; q1_row < N; q1_row++) {
    int q1_col = board[q1_row];
    for (int q2_row = q1_row + 1; q2_row < N; q2_row++) {
      int q2_col = board[q2_row];
      int delta_row = q1_row - q2_row;
      int delta_col = q1_col - q2_col;
      if (q1_col == q2_col)
        c++;
      else if (abs(delta_row) == abs(delta_col))
        c++;
    }
  }
  return c;
}

void print_board(int board[N]) {
  for (int i = 0; i < N; i++) {
    cout << "|";
    for (int j = 0; j < N; j++) {
      if (j == board[i])
        cout << "X|";
      else
        cout << " |";
    }
    cout << endl;
  }
  cout << collisions(board) << endl;
}

void copy(int source[N], int target[N]) {
  for (int i = 0; i < N; i++)
    target[i] = source[i];
}

void hc() {
  srand(time(NULL));
  int best_board[N];
  int next_board[N];
  int current_board[N];
  int tries = 0;
  do {
    tries++;
    cout << "TRY " << tries << endl;
    // δημιουργία τυχαίου ταμπλό με μια βασίλισσα ανά στήλη
    for (int i = 0; i < N; i++) {
      current_board[i] = rand() % N;
    }
    // Αναρρίχηση λόφου
    print_board(current_board);
    int min = collisions(current_board);
    copy(current_board, best_board);
    while (min > 0) {
      bool flag = false;
      for (int row = 0; row < N; row++) {
        for (int k = 1; k < N; k++) {
          copy(current_board, next_board);
          next_board[row] = (next_board[row] + k) % N;
          if (collisions(next_board) < min) {
            min = collisions(next_board);
            copy(next_board, best_board);
            flag = true;
          }
        }
      }
      if (flag) {
        // print_board(best_board);
        copy(best_board, current_board);
      } else {
        print_board(best_board);
        cout << "Deadend, best number of collisions achieved " << min << endl;
        break;
      }
    }
  } while (collisions(best_board) > 0 && tries < 100);
  print_board(best_board);
}

int main() { hc(); }
