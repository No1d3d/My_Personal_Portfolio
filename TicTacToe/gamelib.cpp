#include "gamelib.h"
#include <iostream>

using namespace std;

void Rules() {
  cout << "WELCOME TO TIC TAC TOE GAME!\n"
          "CHOOSE A CELL TO PUT YOUR MARK\n"
          "BY TYPING IN A CORRESPONDING NUMBER\n"
          "1 | 2 | 3\n"
          "--+---+--\n"
          "4 | 5 | 6\n"
          "--+---+--\n"
          "7 | 8 | 9\n"
          "X GOES FIRST, O GOES SECOND\n"
          "GOOD LUCK AND HAVE FUN!!!\n\n\n";
}
void Display(char playField[3][3]) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      cout << playField[i][j] << " ";
      if (j == 0 || j == 1) {
        cout << "| ";
      }
    }
    cout << "\n";
    if (i == 0 || i == 1) {
      cout << "--+---+--\n";
    }
  }
}
int CheckForWin(char playField[3][3], int player) {
  player = (player == 0 ? 2 : 1);
  int win = 0;
  char sym = (player == 1 ? 'X' : 'O');
  if ((playField[0][0] == sym && playField[0][1] == sym &&
       playField[0][2] == sym) ||
      (playField[1][0] == sym && playField[1][1] == sym &&
       playField[1][2] == sym) ||
      (playField[2][0] == sym && playField[2][1] == sym &&
       playField[2][2] == sym) ||
      (playField[0][0] == sym && playField[1][0] == sym &&
       playField[2][0] == sym) ||
      (playField[0][1] == sym && playField[1][1] == sym &&
       playField[2][1] == sym) ||
      (playField[0][2] == sym && playField[1][2] == sym &&
       playField[2][2] == sym) ||
      (playField[0][0] == sym && playField[1][1] == sym &&
       playField[2][2] == sym) ||
      (playField[2][0] == sym && playField[1][1] == sym &&
       playField[0][2] == sym)) {
    cout << "PLAYER " << player << " WON!!!\n";
    win = 1;
  } else if (playField[0][0] != ' ' && playField[0][1] != ' ' &&
             playField[0][2] != ' ' && playField[1][0] != ' ' &&
             playField[1][1] != ' ' && playField[1][2] != ' ' &&
             playField[2][0] != ' ' && playField[2][1] != ' ' &&
             playField[2][2] != ' ') {
    cout << "THAT IS A TIE!\n";
    win = 1;
  }
  return (win);
}

int CheckPlacement(int cell, char playField[3][3]) {
  int res = 0;
  switch (cell) {
  case 1:
    res = (playField[0][0] != ' ' ? 0 : 1);
    break;
  case 2:
    res = (playField[0][1] != ' ' ? 0 : 1);
    break;
  case 3:
    res = (playField[0][2] != ' ' ? 0 : 1);
    break;
  case 4:
    res = (playField[1][0] != ' ' ? 0 : 1);
    break;
  case 5:
    res = (playField[1][1] != ' ' ? 0 : 1);
    break;
  case 6:
    res = (playField[1][2] != ' ' ? 0 : 1);
    break;
  case 7:
    res = (playField[2][0] != ' ' ? 0 : 1);
    break;
  case 8:
    res = (playField[2][1] != ' ' ? 0 : 1);
    break;
  case 9:
    res = (playField[2][2] != ' ' ? 0 : 1);
    break;
  }
  return (res);
}

void AskForInput(int player) {
  player = (player == 0 ? 2 : 1);
  cout << "\nPLAYER " << player << " YOUR TURN:   ";
}

void PlaceSign(int player, int cell, char playField[3][3]) {
  char sign = (player % 2 == 1 ? 'X' : 'O');
  switch (cell) {
  case 1:
    playField[0][0] = sign;
    break;
  case 2:
    playField[0][1] = sign;
    break;
  case 3:
    playField[0][2] = sign;
    break;
  case 4:
    playField[1][0] = sign;
    break;
  case 5:
    playField[1][1] = sign;
    break;
  case 6:
    playField[1][2] = sign;
    break;
  case 7:
    playField[2][0] = sign;
    break;
  case 8:
    playField[2][1] = sign;
    break;
  case 9:
    playField[2][2] = sign;
    break;
  }
}
