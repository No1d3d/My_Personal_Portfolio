#include "ubercontroller.h"

UberController::UberController(QObject *parent) : QObject{parent} {
  qDebug() << "UberController created\n";
  model = new Model();
}

UberController::~UberController() {
  settings = new QSettings("21sc", "3dviewer", this);
}

void UberController::save_settings() {
  Model::Condition top = cond_stack.top();
  settings->setValue("projection_type", top.projection_type);
  settings->setValue("line_type", top.line_type);

  settings->setValue("line_width", top.line_size);

  settings->setValue("points_type", top.points_type);
  settings->setValue("points_size", top.points_size);

  settings->setValue("back_color", top.backColor);
  settings->setValue("line_color", top.edgeColor);
  settings->setValue("vertex_color", top.vertexColor);

  settings->setValue("fullname", top.fullname);
}

void UberController::load_settings() {
  //    Model::Condition top;
  //    top.projection_type = settings->value("projection_type").toInt();
  //    top.line_type = settings->value("line_type").toInt();
  //    top.line_size = settings->value("line_width").toInt();

  //    top.points_type = settings->value("points_type").toInt();
  //    top.points_size = settings->value("points_size").toInt();

  //    top.backColor = settings->value("back_color").value<QColor>();
  //    top.edgeColor = settings->value("line_color").value<QColor>();
  //    top.vertexColor = settings->value("vertex_color").value<QColor>();

  //    top.fullname = settings->value("fullname").toString();

  //    cond_stack.push(top);
  Model::Condition top;
  if (settings != nullptr) {
    top.projection_type = settings->value("projection_type").toInt();
    top.line_type = settings->value("line_type").toInt();
    top.line_size = settings->value("line_width").toInt();

    top.points_type = settings->value("points_type").toInt();
    top.points_size = settings->value("points_size").toInt();

    top.backColor = settings->value("back_color").value<QColor>();
    top.edgeColor = settings->value("line_color").value<QColor>();
    top.vertexColor = settings->value("vertex_color").value<QColor>();

    top.fullname = settings->value("fullname").toString();

    cond_stack.push(top);
    model->GetCondition(cond_stack.top());
  }
}

Model::Condition UberController::step_back() {
  if (cond_stack.size() == 1) return cond_stack.top();
  cond_stack.pop();
  Model::Condition cur_condition = cond_stack.top();
  model->GetCondition(cond_stack.top());
  //    qDebug() << "xshift:" << cur_condition.x_shift << " " << "yshift:" <<
  //    cur_condition.y_shift << " " << "zshift:"
  //                 << cur_condition.z_shift << Qt::endl << "ozrotate:" <<
  //                 cur_condition.oz_rotate << " " << "oyrotate:" <<
  //                 cur_condition.oy_rotate << " "
  //                 << "oxrotate" << cur_condition.ox_rotate << Qt::endl <<
  //                 "scale" << cur_condition.scale << Qt::endl << "pointstype:"
  //                 << cur_condition.points_type
  //                 << " " << "pointssize:" << cur_condition.points_size <<
  //                 Qt::endl << "linetype:" << cur_condition.line_type << " "
  //                 << "linesize:" << cur_condition.line_size << " " <<
  //                 "projectiontype" << cur_condition.projection_type;
  //        qDebug() << "\StepBack is here\n";
  return cur_condition;
}

void UberController::GetCondition(Model::Condition cur_condition) {
  cond_stack.push(cur_condition);
  model->GetCondition(cur_condition);
  //    qDebug() << "xshift:" << cur_condition.x_shift << " " << "yshift:" <<
  //    cur_condition.y_shift << " " << "zshift:"
  //             << cur_condition.z_shift << Qt::endl << "ozrotate:" <<
  //             cur_condition.oz_rotate << " " << "oyrotate:" <<
  //             cur_condition.oy_rotate << " "
  //             << "oxrotate" << cur_condition.ox_rotate << Qt::endl << "scale"
  //             << cur_condition.scale << Qt::endl << "pointstype:" <<
  //             cur_condition.points_type
  //             << " " << "pointssize:" << cur_condition.points_size <<
  //             Qt::endl << "linetype:" << cur_condition.line_type << " " <<
  //             "linesize:" << cur_condition.line_size << " " <<
  //             "projectiontype" << cur_condition.projection_type;
  //    qDebug() << "UberController is here\n";
}
