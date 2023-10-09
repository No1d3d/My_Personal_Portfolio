#include "3dviewer.h"

void rotationFunction(object_s* object, double deg, int rotationAxis) {
  deg *= M_PI / 180;
  int adder1 = 0, adder2 = 0;
  if (rotationAxis == XAxis) {
    adder1 = YAxis;
    adder2 = ZAxis;
  } else if (rotationAxis == YAxis) {
    adder1 = XAxis;
    adder2 = ZAxis;
  } else if (rotationAxis == ZAxis) {
    adder1 = XAxis;
    adder2 = YAxis;
  }
  for (int i = 0; i < 3 * object->vertex_count; i += 3) {
    double tmp1 = object->vertex_array[i + adder1];
    double tmp2 = object->vertex_array[i + adder2];
    object->vertex_array[i + adder1] = tmp1 * cos(deg) - tmp2 * sin(deg);
    object->vertex_array[i + adder2] = tmp1 * sin(deg) + tmp2 * cos(deg);
  }
}

void shiftFunction(object_s* object, delta delta, int shiftFlag) {
  for (int i = 0; i < object->vertex_count * 3; i += 3) {
    if (shiftFlag == XAxis) object->vertex_array[i] += delta.dx;
    if (shiftFlag == YAxis) object->vertex_array[i + 1] += delta.dy;
    if (shiftFlag == ZAxis) object->vertex_array[i + 2] += delta.dz;
  }
}

void scaleFunction(object_s* object, double scale) {
  for (int i = 0; i < object->vertex_count * 3; i++) {
    object->vertex_array[i] *= scale;
  }
}

void normalizationFunction(object_s* object) {
  double xmin = object->vertex_array[0];
  double xmax = object->vertex_array[0];
  double ymin = object->vertex_array[1];
  double ymax = object->vertex_array[1];
  for (int i = 3; i < object->vertex_count * 3; i += 3) {
    if (object->vertex_array[i] < xmin) xmin = object->vertex_array[i];
    if (object->vertex_array[i] > xmax) xmax = object->vertex_array[i];
    if (object->vertex_array[i + 1] < ymin) ymin = object->vertex_array[i + 1];
    if (object->vertex_array[i + 1] > ymax) ymax = object->vertex_array[i + 1];
  }
  double x_ratio = xmax / 100;
  double y_ratio = ymax / 100;
  double scaler = x_ratio > y_ratio ? 1 / x_ratio : 1 / y_ratio;
  for (int i = 0; i < object->vertex_count * 3; i++)
    object->vertex_array[i] *= scaler;
}
