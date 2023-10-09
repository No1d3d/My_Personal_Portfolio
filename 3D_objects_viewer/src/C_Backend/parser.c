#include "3dviewer.h"

object_s parser(char *str, object_s *object) {
  vrx_fsts_counter(str, object);
  vrx_fsts_parser(str, object);

  // free(object->vertex_array);
  // free(object->facets_array);
  return *object;
}
