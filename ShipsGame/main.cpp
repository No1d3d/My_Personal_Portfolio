#include "ships.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

int main() {
  player p1;
  player p2;
  Rules();
  int order = 1;
  char y_ch;
  int y, x;
  int fp[2];
  int sp[2];
  do {
    cin >> y_ch;
  } while (y_ch != 's');
  while (true) {
    system("clear");
    while (true) {
      if (p1.ships == 10 && p2.ships == 10) {
        break;
      }
      system("clear");
      if (order % 2 == 1) {
        DrawField(p1.pl_field);
        AskToPlace(order, p1.ships);
        do {
          cin >> y_ch >> x;
          y = int(y_ch) - 65;
          x -= 1;
          fp[0] = y;
          fp[1] = x;
          sp[0] = y;
          sp[1] = x;
          if (p1.ships > 3) {
            cin >> y_ch >> x;
            y = int(y_ch) - 65;
            x -= 1;
            sp[0] = y;
            sp[1] = x;
          }
        } while (CheckInput(fp, sp) != 1 && CheckAllign(fp, sp) != 1 ||
                 CheckLength(fp, sp, p1.ships) != 1 ||
                 CheckPlacement(p1.pl_field, fp, sp) != 1);
        Place(p1.pl_field, fp, sp);
        p1.ships++;
        order++;
      } else {
        DrawField(p2.pl_field);
        AskToPlace(order, p2.ships);
        do {
          cin >> y_ch >> x;
          y = int(y_ch) - 65;
          x -= 1;
          fp[0] = y;
          fp[1] = x;
          sp[0] = y;
          sp[1] = x;
          if (p2.ships > 3) {
            cin >> y_ch >> x;
            y = int(y_ch) - 65;
            x -= 1;
            sp[0] = y;
            sp[1] = x;
          }
        } while (CheckInput(fp, sp) != 1 || CheckAllign(fp, sp) != 1 ||
                 CheckLength(fp, sp, p2.ships) != 1 ||
                 CheckPlacement(p2.pl_field, fp, sp) != 1);
        Place(p2.pl_field, fp, sp);
        p2.ships++;
        order++;
      }
    }
    system("clear");
    order % 2 == 1 ? DrawField(p1.op_field) : DrawField(p2.op_field);
    Attack(order);
    if (order % 2 == 1) {
      do {
        cin >> y_ch >> x;
        y = int(y_ch) - 65;
        x -= 1;
        fp[0] = y;
        fp[1] = x;
        if (CheckHit(p2.pl_field, p1.op_field, fp) == 1) {
          p1.hits++;
        }
        if (CheckWin(p1.hits, order) == 1) {
          break;
        }
      } while (CheckHit(p2.pl_field, p1.op_field, fp) == 1);
    } else {
      do {
        cin >> y_ch >> x;
        y = int(y_ch) - 65;
        x -= 1;
        fp[0] = y;
        fp[1] = x;
        if (CheckHit(p1.pl_field, p2.op_field, fp) == 1) {
          p2.hits++;
        }
        if (CheckWin(p2.hits, order) == 1) {
          break;
        }
      } while (CheckHit(p1.pl_field, p2.op_field, fp) == 1);
    }
    order++;
  }
}
