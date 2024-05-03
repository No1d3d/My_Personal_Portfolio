#include "mainwindow.h"

//#include "ui_mainwindow.h"
//#include "model.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      gif(nullptr),
      timer(new QTimer),
      ui(new Ui::MainWindow)

{
  ui->setupUi(this);
  controller = new UberController();
  model = controller->model;
  settings = new QSettings("21sc", "3dviewer", this);
  load_settings();
}

MainWindow::~MainWindow() {
  save_settings();
  delete ui;
}

void MainWindow::on_openfile_clicked() {
  // on_initial_clicked();
  QString temp = "~/Desktop";
  QString path;
  path = QFileDialog::getOpenFileName(this, "open a file", "~/Desktop",
                                      tr("Objects Files (*.obj)"), 0,
                                      QFileDialog::DontUseNativeDialog);
  ui->Path_to_file->setText(path);
  model->parser(path);
  ui->display_widget->object = model->our_object;
  ui->display_widget->object->condition = &cur_condition;
  model->normalizationFunction(ui->display_widget->object);
  ui->display_widget->update();
  ui->Filename->setText(path);
}

void MainWindow::on_rotate_x_valueChanged(double arg1) {
  introtator = 0;
  model->rotationFunction(ui->display_widget->object, arg1 - ex_rot_x,
                          introtator);
  ui->display_widget->object = model->our_object;
  ui->display_widget->update();
  get_cur_condition();
  send_param();
  ex_rot_x = arg1;
}

void MainWindow::on_rotate_y_valueChanged(double arg1) {
  introtator = 1;
  model->rotationFunction(ui->display_widget->object, arg1 - ex_rot_y,
                          introtator);
  ui->display_widget->update();
  ex_rot_y = arg1;
  get_cur_condition();
  send_param();
}

void MainWindow::on_rotate_z_valueChanged(double arg1) {
  introtator = 2;
  model->rotationFunction(ui->display_widget->object, arg1 - ex_rot_z,
                          introtator);
  ui->display_widget->update();
  ex_rot_z = arg1;
  get_cur_condition();
  send_param();
}

void MainWindow::on_mov_x_valueChanged(double arg1) {
  intshifter = 0;
  ui->display_widget->delta_xyz.dx = arg1 - oldpos_x;
  model->shiftFunction(ui->display_widget->object,
                       ui->display_widget->delta_xyz, intshifter);
  ui->display_widget->update();
  oldpos_x = arg1;
  get_cur_condition();
  send_param();
}

void MainWindow::on_mov_y_valueChanged(double arg1) {
  intshifter = 1;
  ui->display_widget->delta_xyz.dy = arg1 - oldpos_y;
  model->shiftFunction(ui->display_widget->object,
                       ui->display_widget->delta_xyz, intshifter);
  ui->display_widget->update();
  oldpos_y = arg1;
  get_cur_condition();
  send_param();
}

void MainWindow::on_mov_z_valueChanged(double arg1) {
  intshifter = 2;
  ui->display_widget->delta_xyz.dz = arg1 - oldpos_z;
  model->shiftFunction(ui->display_widget->object,
                       ui->display_widget->delta_xyz, intshifter);
  ui->display_widget->update();
  oldpos_z = arg1;
  get_cur_condition();
  send_param();
}

//##########################        p2
//#################################################################

void MainWindow::on_background_color_clicked() {
  ui->display_widget->BackgroundColor = QColorDialog::getColor();
  cur_condition.backColor = QColorDialog::getColor();
  get_cur_condition();
  send_param();
}

void MainWindow::on_line_color_clicked() {
  ui->display_widget->LineColor = QColorDialog::getColor();
  cur_condition.edgeColor = QColorDialog::getColor();
  get_cur_condition();
  send_param();
}

void MainWindow::on_vertices_color_clicked() {
  ui->display_widget->VerticesColor = QColorDialog::getColor();
  cur_condition.vertexColor = QColorDialog::getColor();
  get_cur_condition();
  send_param();
}

void MainWindow::on_line_size_valueChanged(int arg1) {
  ui->display_widget->linesize = arg1;
  ui->display_widget->update();
}

void MainWindow::on_vert_size_valueChanged(int arg1) {
  ui->display_widget->vertsize = arg1;
  ui->display_widget->update();
}

void MainWindow::save_settings() {
  settings->setValue("bckg_color_R",
                     ui->display_widget->BackgroundColor.redF());
  settings->setValue("bckg_color_G",
                     ui->display_widget->BackgroundColor.greenF());
  settings->setValue("bckg_color_B",
                     ui->display_widget->BackgroundColor.blueF());

  settings->setValue("vert_color_R", ui->display_widget->VerticesColor.redF());
  settings->setValue("vert_color_G",
                     ui->display_widget->VerticesColor.greenF());
  settings->setValue("vert_color_B", ui->display_widget->VerticesColor.blueF());

  settings->setValue("line_color_R", ui->display_widget->LineColor.redF());
  settings->setValue("line_color_G", ui->display_widget->LineColor.greenF());
  settings->setValue("line_color_B", ui->display_widget->LineColor.blueF());

  settings->setValue("vert_size", ui->display_widget->vertsize);
  settings->setValue("line_size", ui->display_widget->linesize);
  settings->setValue("vert_type", ui->display_widget->vert_type);
  settings->setValue("line_type", ui->display_widget->line_type);
  settings->setValue("proj_type", ui->display_widget->projtype);
}

void MainWindow::load_settings() {
  ui->display_widget->BackgroundColor.setRgbF(
      settings->value("bckg_color_R", 0).toFloat(),
      settings->value("bckg_color_G", 0).toFloat(),
      settings->value("bckg_color_B", 0).toFloat());
  ui->display_widget->LineColor.setRgbF(
      settings->value("line_color_R", 255).toFloat(),
      settings->value("line_color_G", 255).toFloat(),
      settings->value("line_color_B", 255).toFloat());
  ui->display_widget->VerticesColor.setRgbF(
      settings->value("vert_color_R", 255).toFloat(),
      settings->value("vert_color_G", 255).toFloat(),
      settings->value("vert_color_B", 255).toFloat());

  ui->vert_size->setValue(settings->value("vert_size", 1).toInt());
  ui->line_size->setValue(settings->value("line_size", 1).toInt());

  cur_condition.points_size = settings->value("vert_size", 1).toInt();
  cur_condition.line_size = settings->value("line_size", 1).toInt();
  cur_condition.points_type = settings->value("vert_type", 1).toInt();
  cur_condition.projection_type = settings->value("proj_type", 0).toInt();
  cur_condition.line_type = settings->value("line_type", 0).toInt();
}

//##########################        p3
//#############################################################

void MainWindow::on_screen_bmp_clicked() {
  QString file = QFileDialog::getSaveFileName(this, "Save as...", "name.bmp",
                                              "BMP (*.bmp)", 0,
                                              QFileDialog::DontUseNativeDialog);
  ui->display_widget->grabFramebuffer().save(file, NULL, 100);
}

void MainWindow::on_screen_jpeg_clicked() {
  QString file = QFileDialog::getSaveFileName(
      this, tr("Save as..."), tr("../name.jpeg"), tr("JPEG (*.jpeg)"), 0,
      QFileDialog::DontUseNativeDialog);
  ui->display_widget->grabFramebuffer().save(file, NULL, 100);
}

void MainWindow::on_gif_clicked() {
  ui->gif->setDisabled(true);
  gif = new QGifImage;
  timer = new QTimer(this);
  gif->setDefaultDelay(100);
  timer->start(100);
  connect(timer, SIGNAL(timeout()), this, SLOT(takeFrame()));
}

void MainWindow::takeFrame() {
  QImage frame = ui->display_widget->grabFramebuffer();
  gif->addFrame(frame.scaled(640, 480), 0);
  if (gif->frameCount() == 50) {
    timer->stop();
    QString pathGIF = QFileDialog::getSaveFileName(
        this, ("Save as GIF"), "image.gif", "GIF Image Files (*.gif)", 0,
        QFileDialog::DontUseNativeDialog);
    gif->save(pathGIF);
    delete timer;
    delete gif;
    ui->gif->setEnabled(true);
  }
}

void MainWindow::on_initial_clicked() {
  QByteArray tmp = (ui->Path_to_file->text()).toLocal8Bit();
  char *charpath = tmp.data();
  if (charpath != 0) {
    ui->mov_x->setValue(0.00);
    ui->mov_y->setValue(0.00);
    ui->mov_z->setValue(0.00);
    ui->rotate_x->setValue(0.00);
    ui->rotate_y->setValue(0.00);
    ui->rotate_z->setValue(0.00);
    ui->scale->setValue(1.00);
    ui->vert_size->setValue(1);
    ui->line_size->setValue(1);
    model->parser(tmp);
    ui->display_widget->object = model->our_object;
    ui->display_widget->object->condition = &cur_condition;
    model->normalizationFunction(ui->display_widget->object);
    ui->display_widget->update();
  }
}

void MainWindow::get_cur_condition() {
  cur_condition.fullname = ui->Path_to_file->text();

  cur_condition.ox_rotate = ui->rotate_x->value() * 2;
  cur_condition.oy_rotate = ui->rotate_y->value() * 2;
  cur_condition.oz_rotate = ui->rotate_z->value() * 2;

  cur_condition.scale = ui->scale->value();

  cur_condition.x_shift = ui->mov_x->value() * 2;
  cur_condition.y_shift = ui->mov_y->value() * 2;
  cur_condition.z_shift = ui->mov_z->value() * 2;
}

void MainWindow::send_param() { controller->GetCondition(cur_condition); }

void MainWindow::on_rb_vert_no_clicked() {
  cur_condition.points_type = 0;
  ui->display_widget->object->condition->points_type = 0;
  ui->display_widget->update();
  send_param();
}

void MainWindow::on_rb_vert_circle_clicked() {
  cur_condition.points_type = 1;
  ui->display_widget->object->condition->points_type = 1;
  ui->display_widget->update();
  send_param();
}

void MainWindow::on_rb_vert_square_clicked() {
  cur_condition.points_type = 2;
  ui->display_widget->object->condition->points_type = 2;
  ui->display_widget->update();
  send_param();
}

void MainWindow::on_rb_line_solid_clicked() {
  cur_condition.line_type = 0;
  ui->display_widget->object->condition->line_type = 0;
  ui->display_widget->update();
  send_param();
}

void MainWindow::on_rb_line_dotted_clicked() {
  cur_condition.line_type = 1;
  ui->display_widget->object->condition->line_type = 1;
  ui->display_widget->update();
  send_param();
}

void MainWindow::on_rb_proj_central_clicked() {
  cur_condition.projection_type = 0;
  ui->display_widget->object->condition->projection_type = 0;
  ui->display_widget->update();
  send_param();
}

void MainWindow::on_rb_proj_parallel_clicked() {
  cur_condition.projection_type = 1;
  ui->display_widget->object->condition->projection_type = 1;
  ui->display_widget->update();
  send_param();
}

void MainWindow::on_scale_valueChanged(double arg1) {
  get_cur_condition();
  send_param();
  model->scaleFunction(ui->display_widget->object, 1 / old_zoom);
  model->scaleFunction(ui->display_widget->object, arg1);
  old_zoom = arg1;
  ui->display_widget->update();
}

void MainWindow::on_step_back_clicked() {
  Model::Condition current = controller->step_back();
  set_ui_on_condition(current);
}

void MainWindow::set_ui_on_condition(Model::Condition current) {
  ui->mov_x->setValue(current.x_shift);
  ui->mov_y->setValue(current.y_shift);
  ui->mov_z->setValue(current.z_shift);

  ui->scale->setValue(current.scale);

  ui->rotate_x->setValue(current.ox_rotate);
  ui->rotate_y->setValue(current.oy_rotate);
  ui->rotate_z->setValue(current.oz_rotate);

  ui->line_size->setValue(current.line_size);
  ui->vert_size->setValue(current.points_size);

  switch (current.line_type) {
    case 0:
      ui->rb_line_solid->setChecked(true);
      break;

    case 1:
      ui->rb_line_dotted->setChecked(true);
      break;
  }

  switch (current.points_type) {
    case 0:
      ui->rb_vert_no->setChecked(true);
      break;
    case 1:
      ui->rb_vert_circle->setChecked(true);
      break;
    case 2:
      ui->rb_vert_square->setChecked(true);
      break;
  }

  switch (current.projection_type) {
    case 0:
      ui->rb_proj_central->setChecked(true);
      break;

    case 1:
      ui->rb_proj_parallel->setChecked(true);
      break;
  }
}
