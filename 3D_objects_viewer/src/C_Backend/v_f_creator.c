#include "3dviewer.h"

void vrx_fsts_parser(char *filename, object_s *object) {
  object->vertex_array =
      (double *)calloc(object->vertex_count * 3, sizeof(double));
  object->facets_array = calloc(2 * object->facets_count, sizeof(int));
  FILE *f_path = NULL;
  f_path = fopen(filename, "r");
  char *line = NULL;
  size_t line_len = 0;
  int counter = 0;
  int array_ctr = 0;
  if (f_path) {
    while (getline(&line, &line_len, f_path) != EOF) {
      if (line[0] == 'v' && line[1] == ' ') {
        line++;
        sscanf(line, "%lf %lf %lf\n", &object->vertex_array[counter],
               &object->vertex_array[counter + 1],
               &object->vertex_array[counter + 2]);
        line--;
        counter += 3;
      } else if (line[0] == 'f' && line[1] == ' ') {
        int cur_dig_num = 0, freeer = 0;
        line++, freeer++;
        int dig_amount = look_through_fsts_str(line);
        while (*line != '\0' && *line != EOF) {
          if (*(line - 1) == ' ' && isdigit(*line)) {
            int dig = 0;
            while (isdigit(*line)) {
              dig = dig * 10 + (*line - '0');
              line++, freeer++;
            }
            if (cur_dig_num == 0) {
              object->facets_array[array_ctr++] = dig - 1;
            } else if (cur_dig_num > 0 && (cur_dig_num < dig_amount - 1)) {
              object->facets_array[array_ctr++] = dig - 1;
              object->facets_array[array_ctr++] = dig - 1;
            } else if (cur_dig_num == dig_amount - 1) {
              object->facets_array[array_ctr++] = dig - 1;
              object->facets_array[array_ctr++] = dig - 1;
              object->facets_array[array_ctr] =
                  object->facets_array[array_ctr + 1 - dig_amount * 2];
              if (array_ctr < object->facets_count * 2) array_ctr++;
            }
            cur_dig_num++;
          }
          line++, freeer++;
        }
        line -= freeer;
      }
    }
    free(line);
    fclose(f_path);
  }
}

void datadestr(object_s *object) {
  if (object != NULL) {
    if (object->facets_array != NULL) {
      free(object->facets_array);
      object->facets_array = NULL;
    }
    if (object->vertex_array != NULL) {
      free(object->vertex_array);
      object->vertex_array = NULL;
    }
  }
}