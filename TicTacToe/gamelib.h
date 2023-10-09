#ifndef GAMELIB_H_
#define GAMELIB_H_

#include <iostream>

void Rules();
void Display(char playField[3][3]);
int CheckForWin(char playField[3][3], int player);
int CheckPlacement(int cell, char playField[3][3]);
void AskForInput(int player);
void PlaceSign(int player, int cell, char playField[3][3]);

#endif //GAMELIB_H_
