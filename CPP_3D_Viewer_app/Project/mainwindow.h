#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define no_vert 0
#define circ_vert 1
#define sq_vert 2

#include <ui_mainwindow.h>

#include <QColorDialog>
#include <QFileDialog>
#include <QMainWindow>
#include <QOpenGLFunctions>
#include <QSettings>
#include <QTime>
#include <QWidget>
#include <QtOpenGL>
#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QtWidgets/QWidget>

#include "MODEL/gifimage/qgifimage.h"
#include "glview.h"
#include "ubercontroller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  Model *model = nullptr;
  UberController *controller;
  QString path;
  Model::Condition cur_condition;
  QSettings *settings;
  void save_settings();
  void load_settings();

 private slots:
  void on_openfile_clicked();

  void on_rotate_x_valueChanged(double arg1);

  void on_rotate_y_valueChanged(double arg1);

  void on_rotate_z_valueChanged(double arg1);

  void on_mov_x_valueChanged(double arg1);

  void on_mov_y_valueChanged(double arg1);

  void on_mov_z_valueChanged(double arg1);

  void on_screen_bmp_clicked();

  void on_screen_jpeg_clicked();

  void on_gif_clicked();

  void takeFrame();

  void on_background_color_clicked();

  void on_vertices_color_clicked();

  void on_line_color_clicked();

  void on_line_size_valueChanged(int arg1);

  void on_vert_size_valueChanged(int arg1);

  void on_initial_clicked();

  void on_rb_vert_no_clicked();

  void on_rb_vert_circle_clicked();

  void on_rb_vert_square_clicked();

  void on_rb_line_solid_clicked();

  void on_rb_line_dotted_clicked();

  void on_rb_proj_central_clicked();

  void on_rb_proj_parallel_clicked();

  void on_scale_valueChanged(double arg1);

  void on_step_back_clicked();

 private:
  int frames;
  QGifImage *gif;
  QTimer *timer;
  Ui::MainWindow *ui;
  int intshifter;
  int introtator;
  double oldpos_x = 0;
  double oldpos_y = 0;
  double oldpos_z = 0;
  double old_zoom = 1;
  double ex_rot_x = 0;
  double ex_rot_y = 0;
  double ex_rot_z = 0;

  void get_cur_condition();
  void send_param();
  void set_ui_on_condition(Model::Condition current);
};
#endif  // MAINWINDOW_H
