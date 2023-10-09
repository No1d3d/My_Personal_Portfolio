#include "glview.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"
glview::glview(QWidget *parent) : QOpenGLWidget{parent} {
  object = {0, 0, NULL, NULL};
  delta_xyz = {0, 0, 0};
}

glview::~glview() {}
void glview::initializeGL() {
  initializeOpenGLFunctions();
  glOrtho(-120, 120, -120, 120, 100, -100);
}

void glview::paintGL() {
  glClearColor(BackgroundColor.redF(), BackgroundColor.greenF(),
               BackgroundColor.blueF(), 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glVertexPointer(3, GL_DOUBLE, 0, object.vertex_array);
  glEnableClientState(GL_VERTEX_ARRAY);
  projection_processing();
  line_processing();
  vert_processing();
  glDisableClientState(GL_VERTEX_ARRAY);
}

void glview::projection_processing() {
  if (projtype == 0) {
    glFrustum(-1, 1, -1, 1, 1, 15);
    glTranslated(0, 0, -4);
  }
}

void glview::line_processing() {
  if (line_type) {
    glLineStipple(1, 0x3333);
    glEnable(GL_LINE_STIPPLE);
  } else {
    glDisable(GL_LINE_STIPPLE);
  }
  glLineWidth((float)linesize);
  glColor3f(LineColor.redF(), LineColor.greenF(), LineColor.blueF());
  glDrawElements(GL_LINES, 2 * object.facets_count, GL_UNSIGNED_INT,
                 object.facets_array);
}

void glview::vert_processing() {
  glPointSize((float)vertsize);
  glColor3f(VerticesColor.redF(), VerticesColor.greenF(),
            VerticesColor.blueF());
  if (vert_type) {
    if (vert_type == circ_vert) {
      glEnable(GL_POINT_SMOOTH);
      glDrawArrays(GL_POINTS, 0, object.vertex_count);
      glDisable(GL_POINT_SMOOTH);
    } else if (vert_type == sq_vert) {
      glDrawArrays(GL_POINTS, 0, object.vertex_count);
    }
  }
}

void glview::mousePressEvent(QMouseEvent *mo) { mPos = mo->pos(); }

void glview::mouseMoveEvent(QMouseEvent *mo) {
  if (mo->buttons() & Qt::LeftButton) {
    delta_xyz.dx = 0.01 / M_PI * (mo->pos().x() - mPos.x());
    shiftFunction(&object, delta_xyz, 0);
    delta_xyz.dy = 0.01 / M_PI * (mo->pos().y() - mPos.y()) * -1;
    shiftFunction(&object, delta_xyz, 1);
    update();
  } else if (mo->buttons() & Qt::RightButton) {
    rotationFunction(&object, (0.01 / M_PI * (mo->pos().y() - mPos.y())),
                     XAxis);
    rotationFunction(&object, (0.01 / M_PI * (mo->pos().x() - mPos.x())) * -1,
                     YAxis);
    update();
  }
}
