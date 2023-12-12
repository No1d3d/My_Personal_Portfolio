#include "graph_controller.h"

namespace s21 {

GraphController::GraphController(GraphModelInterface* model) : model_(model) {}

void GraphController::SetGraphExpression(const QString& str) {
  model_->SetGraphExpression(str.toStdString());
}

void GraphController::CalculateGraph() { model_->CalculateGraph(); }

void GraphController::SetGraphBeginX(double new_x) {
  model_->SetGraphBeginX(new_x);
}

void GraphController::SetGraphEndX(double new_x) {
  model_->SetGraphEndX(new_x);
}

void GraphController::SetGraphBeginY(double new_y) {
  model_->SetGraphBeginY(new_y);
}

void GraphController::SetGraphEndY(double new_y) {
  model_->SetGraphEndY(new_y);
}

void GraphController::SetGraphYScaleAuto(bool flag) {
  model_->SetGraphYScaleAuto(flag);
}

}  // namespace s21
