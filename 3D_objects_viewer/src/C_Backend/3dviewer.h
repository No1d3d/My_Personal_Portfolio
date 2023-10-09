#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// setlocale(LC_ALL, "en-US");
// setlocale(LC_NUMERIC, "C");

typedef struct {
  int facets_count;
  int vertex_count;
  int* facets_array;
  double* vertex_array;
} object_s;

typedef struct {
  double dx;  // delta_x
  double dy;  // delta_y
  double dz;  // delts_z
} delta;

enum { XAxis, YAxis, ZAxis };

object_s parser(char* str, object_s* object);
void vrx_fsts_counter(char* filename, object_s* object);
void vrx_fsts_parser(char* filename, object_s* object);
int look_through_fsts_str(char* line);  // look_through_fsts_str

void rotationFunction(object_s* object, double deg, int rotationAxis);
void shiftFunction(object_s* object, delta delta, int shiftFlag);
void scaleFunction(object_s* object, double scale);
void normalizationFunction(object_s* object);

void datadestr(object_s* object);