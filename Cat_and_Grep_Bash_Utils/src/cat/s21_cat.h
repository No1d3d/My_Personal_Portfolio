#ifndef CAT_H
#define CAT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void CatOperator(char* usedFile);

int CatOperator_b(char* usedFile, int lines);

void CatOperator_E(char* usedFile);

void CatOperator_e(char* usedFile);

int CatOperator_n(char* usedFile, int lines);

void CatOperator_s(char* usedFile);

void CatOperator_T(char* usedFile);

void CatOperator_t(char* usedFile);

int CheckFilePresenceCat(char* filePath);

void FileErrorCat(char* filePath);

void WorkWithFileCat(char* fileName);

int CheckFlagCat(char* flagName);

void FlagErrorCat(char* flagName);

int FlagCat(int flagOption, char* usedFile, int storage);

#endif  // CAT_H
