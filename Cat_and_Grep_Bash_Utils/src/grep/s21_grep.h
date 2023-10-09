#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR_01 "s21_grep: %s: No such file or directory\n"

typedef struct {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
  int countFiles;
  int numberLine;
  int countMatches;
} options;

void s21_grep_operator(int argc, char **argv);
int optionsChoice(int argc, char **argv, options *config, char **template);
void dataOutput(char *str, options *options, char *tmpl, char *name);
void flagF(options *config, char **template, char *optarg);
void flagE(options *config, char **template, char *optarg);
void printO(regex_t my_regex, char *str, options config);
void s21_grep(char *name, options config, char *tmpl);
void printExtraData(options config, char *path);
void *increaseLengthStr(void *str, int size);
int templateCompile(char **str, char *optarg);
void setOptions(options *config, int argc);
void templateAdd(char **str, char *optarg);

#endif  // SRC_GREP_S21_GREP_H_