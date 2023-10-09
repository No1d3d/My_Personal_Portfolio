#include <iostream>
#include "gamelib.h"

using namespace std;

int main() {
  int turns = 1;
  int inp;
  char field[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
  Rules();
  while (true) {
    Display(field);
    AskForInput(turns % 2);
    cin >> inp;
    while (inp < 1 || inp > 9 || CheckPlacement(inp, field) == 0) {
      cout << "PLACEMENT ERROR! TRY AGAIN!\n";
      AskForInput(turns % 2);
      cin >> inp;
    }
    PlaceSign(turns % 2, inp, field);
    if (CheckForWin(field, turns % 2) == 1) {
      break;
    }
    turns++;
  }
}
