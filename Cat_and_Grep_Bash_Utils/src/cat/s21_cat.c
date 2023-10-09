#include "s21_cat.h"

int main(int argc, char* argv[]) {
  if (argc == 1) {
    printf("Input Error\n");
  } else {
    if (strncmp(argv[1], "-*", 1) == 0) {
      if (CheckFlagCat(argv[1]) != -1) {
        int option = CheckFlagCat(argv[1]);
        if (argc == 2) {
          printf("No target to cat\n");
        } else {
          int linesCount = 1;
          for (int i = 2; i < argc; i++) {
            linesCount = FlagCat(option, argv[i], linesCount);
          }
        }
      } else {
        FlagErrorCat(argv[1]);
      }
    } else {
      for (int j = 1; j < argc; j++) {
        WorkWithFileCat(argv[j]);
      }
    }
  }
  return (0);
}
