#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// setlocale(LC_ALL, "en-US");
// setlocale(LC_NUMERIC, "C");
//#include "ubercontroller.h"
#include <QColor>
#include <QColorDialog>
#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QVector>

#ifndef MODEL_H
#define MODEL_H
class Model {
 public:
  struct Condition {
    double x_shift;
    double y_shift;
    double z_shift;
    double oz_rotate;
    double oy_rotate;
    double ox_rotate;
    double scale = 1;
    int points_type = 0;
    int points_size = 0;
    int line_type = 0;
    int line_size = 0;
    int projection_type = 0;

    QColor vertexColor;
    QColor edgeColor;
    QColor backColor;

    QString fullname;
  };
  enum { XAxis, YAxis, ZAxis };
  typedef struct {
    double dx;  // delta_x
    double dy;  // delta_y
    double dz;  // delts_z
  } delta;

  typedef struct object_s {
    int facets_count = 0;
    int vertex_count = 0;
    int* facets_array = nullptr;
    double* vertex_array = nullptr;
    Condition* condition;
  } object_s;

  Model();
  void parser(QString str);
  void vrx_fsts_counter(QString filename, object_s* object);
  void vrx_fsts_parser(QString filename, object_s* object);

  void rotationFunction(object_s* object, double deg, int rotationAxis);
  void shiftFunction(object_s* object, delta delta, int shiftFlag);
  void scaleFunction(object_s* object, double scale);
  void normalizationFunction(object_s* object);
  void GetCondition(Condition con);
  // void show_obj();

  ~Model();
  delta* delta_;
  object_s* our_object;
  // void datadestr(object_s* object);
};
#endif  // MODEL_H
