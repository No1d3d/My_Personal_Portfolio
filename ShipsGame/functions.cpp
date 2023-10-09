#include "ships.h"
#include <iostream>
using namespace std;
void Rules() {
  cout << "Первый ход определяется при помощи жребия.\nНа поле ставится 1 "
          "четырёхпалубный, 2 трёхпалубных,\n3 двухпалубных и 4 однопалубных "
          "корабля.\nВсе корабли ставятся строго по вертикали или горизонтали. "
          "\n"
          "Также, корабли нельзя ставить вплотную друг к другу.\nЧтобы "
          "расположить корабль, введите сначала координату\nначала корабля, а "
          "после - конца\n(по правилу - слева направо, сверху вниз).\nИгроки "
          "ходят по очереди.\n Введите букву s в консль для начала игры\n\n\n";
}

void AskToPlace(int player, int ships) {
  int count;
  cout << "Игрок " << 2 - (player % 2) << ", ставьте свой ";
  if (ships == 9) {
    count = 4;
  } else if (ships == 8 || ships == 7) {
    count = 3;
  } else if (ships == 6 || ships == 5 || ships == 4) {
    count = 2;
  } else {
    count = 1;
  }
  cout << count << "-палубный корабль!\n";
}

void Attack(int player) {
  cout << "Игрок " << 2 - (player % 2) << ", ходите!\n\n\n";
}

void DrawField(char field[10][10]) {
  cout << "  1 2 3 4 5 6 7 8 9 10\n";
  for (int i = 0; i < 10; i++) {
    cout << char(65 + i) << " ";
    for (int j = 0; j < 10; j++) {
      cout << field[i][j] << " ";
    }
    cout << endl;
  }
}

int CheckInput(int f_p[2], int s_p[2]) {
  if (f_p[0] < 0 || f_p[0] > 9 || f_p[1] < 0 || f_p[1] > 10 || s_p[0] < 0 ||
      s_p[0] > 9 || s_p[1] < 0 || s_p[1] > 10 || (f_p[0] > s_p[0]) ||
      (f_p[1] > s_p[1])) {
    cout << "Введены неправильные координаты! Попробуйте еще раз!\n";
    return (0);
  }
  return (1);
}

int CheckAllign(int f_p[2], int s_p[2]) {
  if (f_p[0] == s_p[0] && f_p[1] == s_p[1]) {
    return (1);
  } else if ((s_p[0] == f_p[0] && s_p[1] != f_p[1]) ||
             (s_p[1] == f_p[1] && s_p[0] != f_p[0])) {
    return (1);
  } else {
    cout << "Корабль не может быть установлен по диагонали!\nПопробуйте еще "
            "раз!\n";
  }
  return (0);
}

int CheckLength(int f_p[2], int s_p[2], int ships) {
  if (ships <= 3) {
    return (1);
  } else if (ships > 3) {
    if (f_p[0] == s_p[0]) {
      if ((ships == 4 || ships == 5 || ships == 6) && s_p[1] - f_p[1] == 1) {
        return (1);
      } else if ((ships == 7 || ships == 8) && s_p[1] - f_p[1] == 2) {
        return (1);
      } else if (ships == 9 && s_p[1] - f_p[1] == 3) {
        return (1);
      }
    } else if (f_p[1] == s_p[1]) {
      if ((ships == 4 || ships == 5 || ships == 6) && s_p[0] - f_p[0] == 1) {
        return (1);
      } else if ((ships == 7 || ships == 8) && s_p[0] - f_p[0] == 2) {
        return (1);
      } else if (ships == 9 && s_p[0] - f_p[0] == 3) {
        return (1);
      }
    }
  } else {
    cout << "Неправильный размер корабля!\nПопробуйте еще раз!\n";
  }
  return (0);
}

int CheckPlacement(char field[10][10], int f_p[2], int s_p[2]) {
  int y1 = f_p[0], x1 = f_p[1], y2 = s_p[0], x2 = s_p[1];
  y1 -= 1, x1 -= 1, y2 += 1, x2 += 1;
  if (y1 < 0) {
    y1 = 0;
  }
  if (y1 > 9) {
    y1 = 9;
  }
  if (x1 < 0) {
    x1 = 0;
  }
  if (x1 > 9) {
    x1 = 9;
  }
  if (y2 < 0) {
    y2 = 0;
  }
  if (y2 > 9) {
    y2 = 9;
  }
  if (x2 < 0) {
    x2 = 0;
  }
  if (x2 > 9) {
    x1 = 9;
  }
  for (int i = y1; i <= y2; i++) {
    for (int j = x1; j <= x2; j++) {
      if (field[i][j] != '.') {
        cout << "Корабль не может быть размещен здесь!\nПоробуйте еще раз!\n";
        return (0);
      }
    }
  }
  return (1);
}

void Place(char field[10][10], int f_p[2], int s_p[2]) {
  for (int i = f_p[0]; i <= s_p[0]; i++) {
    for (int j = f_p[1]; j <= s_p[1]; j++) {
      field[i][j] = 'S';
    }
  }
}

int CheckHit(char fieldOp[10][10], char fieldPl[10][10], int p[2]) {
  int y = p[0], x = p[1];
  if (fieldOp[y][x] == 'S') {
    cout << "Попал!\n";
    fieldPl[y][x] = 'X';
    return (1);
  } else {
    cout << "Мимо!\n";
    fieldPl[y][x] = '*';
  }
  return (0);
}

int CheckWin(int hits, int player) {
  if (hits == 20) {
    cout << "Игрок " << 2 - (player % 2) << " победил!";
    return (1);
  }
  return (0);
}
