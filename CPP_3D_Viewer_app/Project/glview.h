#ifndef GLVIEW_H
#define GLVIEW_H
#define GL_SILENCE_DEPRECATION
#include <qcolor.h>

#include "model.h"

//#include "mainwindow.h"
//#include "ui_mainwindow.h"

#include <QColorDialog>
#include <QFileDialog>
//#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QSettings>
#include <QtOpenGL>
#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QtWidgets/QWidget>

#define no_vert 0
#define circ_vert 1
#define sq_vert 2

class glview : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT
 public:
  glview(QWidget *parent = nullptr);
  ~glview();
  void initializeGL() override;
  void paintGL() override;
  // void mousePressEvent(QMouseEvent *) override;
  // void mouseMoveEvent(QMouseEvent *) override;
  void projection_processing();
  void vert_processing();
  void line_processing();
  QColor BackgroundColor;
  QColor LineColor;
  QColor VerticesColor;
  Model::object_s *object;
  Model::delta delta_xyz;
  int projtype = 0;
  int linesize = 1;
  int vertsize = 1;
  int vert_type = 1;
  int line_type = 1;

 private:
  QPoint mPos;
  float Xroad;
  float Yroad;
  float Zroad;
  double x, y;
};

#endif  // GLVIEW_H
