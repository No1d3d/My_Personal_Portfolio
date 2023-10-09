#include "s21_cat.h"

void CatOperator(char* usedFile) {
  FILE* myfile;
  myfile = fopen(usedFile, "r");
  char c = getc(myfile);
  while (c != EOF) {
    putchar(c);
    c = getc(myfile);
  }
  fclose(myfile);
}

int CatOperator_b(char* usedFile, int lines) {
  FILE* myfile;
  myfile = fopen(usedFile, "r");
  char c = getc(myfile);
  lines = 1;
  int lineNumber = lines;
  int startOfLine = 1;
  while (c != EOF) {
    if (startOfLine == 1 && c != '\n') {
      printf("%6d\t", lineNumber);
      lineNumber++;
      startOfLine = 0;
    }
    if (c == '\n') {
      startOfLine = 1;
    }
    putchar(c);
    c = getc(myfile);
  }
  fclose(myfile);
  return (lineNumber);
}

void CatOperator_E(char* usedFile) {
  FILE* myfile;
  myfile = fopen(usedFile, "r");
  char c = getc(myfile);
  while (c != EOF) {
    if (c == '\n') {
      printf("$\n");
    } else {
      putchar(c);
    }
    c = getc(myfile);
  }
  fclose(myfile);
}

void CatOperator_e(char* usedFile) {
  FILE* myfile;
  myfile = fopen(usedFile, "r");
  char c = getc(myfile);
  while (c != EOF) {
    if (c == '\n' || c == '\0') {
      printf("$\n");
    } else if (c < 32 && c != '\t' && c != '\n') {
      printf("^%c", c + 64);
    } else if (c == 127) {
      printf("%c", 127);
    } else {
      putchar(c);
    }
    c = getc(myfile);
  }
  fclose(myfile);
}

int CatOperator_n(char* usedFile, int lines) {
  FILE* myfile;
  myfile = fopen(usedFile, "r");
  char c = getc(myfile);
  int lineNumber = lines;
  int startOfLine = 1;
  while (c != EOF) {
    if (startOfLine == 1) {
      printf("%6d\t", lineNumber);
      lineNumber++;
      startOfLine = 0;
    }
    if (c == '\n') {
      startOfLine = 1;
    }
    putchar(c);
    c = getc(myfile);
  }
  fclose(myfile);
  return (1);
}

void CatOperator_s(char* usedFile) {
  FILE* myfile;
  myfile = fopen(usedFile, "r");
  int nlcount = 0;
  char c = getc(myfile);
  while (c != EOF) {
    if (c == '\n') {
      putchar('\n');
      c = getc(myfile);
      while (c == '\n') {
        nlcount++;
        c = getc(myfile);
      }
      if (nlcount >= 1) {
        putchar('\n');
        nlcount = 0;
      }
    }
    if (c == EOF) {
      break;
    }
    putchar(c);
    c = getc(myfile);
  }
  fclose(myfile);
}

void CatOperator_T(char* usedFile) {
  FILE* myfile;
  myfile = fopen(usedFile, "r");
  char c = getc(myfile);
  while (c != EOF) {
    if (c == '\t') {
      printf("^I");
    } else {
      putchar(c);
    }
    c = getc(myfile);
  }
  fclose(myfile);
}

void CatOperator_t(char* usedFile) {
  FILE* myfile;
  myfile = fopen(usedFile, "r");
  char c = getc(myfile);
  while (c != EOF) {
    if (c == '\t') {
      printf("^I");
    } else if (c == '\n') {
      printf("\n");
    } else if (c < 32 && (c != '\n' || c != '\t')) {
      printf("^%c", c + 64);
    } else if (c == 127) {
      printf("%c", 127);
    } else {
      putchar(c);
    }
    c = getc(myfile);
  }
  fclose(myfile);
}

int CheckFilePresenceCat(char* filePath) {
  int presence = 0;
  FILE* myfile;
  myfile = fopen(filePath, "r");
  if (myfile == NULL) {
    presence = 0;
  } else {
    presence = 1;
    fclose(myfile);
  }
  return (presence);
}

void FileErrorCat(char* filePath) {
  printf("cat: %s: No such file or directory\n", filePath);
}

void WorkWithFileCat(char* fileName) {
  if (CheckFilePresenceCat(fileName) == 1) {
    CatOperator(fileName);
  } else {
    FileErrorCat(fileName);
  }
}

int CheckFlagCat(char* flagName) {
  char* array[10] = {"-b", "--number-nonblank", "-e", "-E", "-n", "--number",
                     "-s", "--squeeze-blank",   "-t", "-T"};
  int flagNumber = -1;
  for (int i = 0; i < 10; i++) {
    if (strcmp(flagName, array[i]) == 0) {
      flagNumber = i;
      break;
    }
  }
  return (flagNumber);
}

void FlagErrorCat(char* flagName) {
  printf("cat: illegal option %s\nusage: cat [flag], [target]\n", flagName);
}

int FlagCat(int flagOption, char* usedFile, int storage) {
  int workLog = 0;
  if (CheckFilePresenceCat(usedFile) == 0) {
    FileErrorCat(usedFile);
  } else {
    switch (flagOption) {
      case 0:
        workLog = CatOperator_b(usedFile, storage);
        break;
      case 1:
        workLog = CatOperator_b(usedFile, storage);
        break;
      case 2:
        CatOperator_e(usedFile);
        workLog = 1;
        break;
      case 3:
        CatOperator_E(usedFile);
        workLog = 1;
        break;
      case 4:
        workLog = CatOperator_n(usedFile, storage);
        break;
      case 5:
        workLog = CatOperator_n(usedFile, storage);
        break;
      case 6:
        CatOperator_s(usedFile);
        workLog = 1;
        break;
      case 7:
        CatOperator_s(usedFile);
        workLog = 1;
        break;
      case 8:
        CatOperator_t(usedFile);
        workLog = 1;
        break;
      case 9:
        CatOperator_T(usedFile);
        workLog = 1;
        break;
    }
  }
  return (workLog);
}
