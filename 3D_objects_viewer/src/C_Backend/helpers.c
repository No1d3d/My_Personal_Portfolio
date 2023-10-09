#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "3dviewer.h"

void vrx_fsts_counter(char *filename, object_s *object) {  // vrx_fsts_counter
  FILE *f_path = NULL;
  f_path = fopen(filename, "r");
  char *line = NULL;
  size_t line_len = 0;
  if (f_path) {
    while (getline(&line, &line_len, f_path) != EOF) {
      if (line[0] == 'v' && line[1] == ' ') object->vertex_count += 1;
      if (line[0] == 'f' && line[1] == ' ') {
        int len = (int)strlen(line);
        for (int i = 1; i < len; i++) {
          if (isdigit(line[i]) && line[i - 1] == ' ') object->facets_count += 1;
        }
      }
    }
    fclose(f_path);
    free(line);
  }
}

int look_through_fsts_str(char *line) {  // look_through_fsts_str
  int res = 0;
  for (int i = 1; i < (int)strlen(line); i++) {
    if (isdigit(line[i]) && !(isdigit(line[i - 1])) && line[i - 1] != '/')
      res += 1;
  }
  return res;
}