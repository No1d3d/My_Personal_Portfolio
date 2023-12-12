#include "graph_view.h"

#include <vector>

#include "../ui/ui_graph_view.h"
#include "view_helpers.h"
#include "widgets/qcustomplot.h"

namespace s21 {

GraphView::GraphView(GraphControllerInterface* controller,
                     GraphModelPublicInterface* model, QWidget* parent)
    : QDialog(parent),
      ui_(new Ui::GraphView),
      controller_(controller),
      model_(model) {
  ui_->setupUi(this);
  SetupButtons();
  ResetResult();
  model_->RegisterObserver(static_cast<GraphObserverUpdateInterface*>(this));
  model_->RegisterObserver(static_cast<GraphObserverErrorInterface*>(this));
}

GraphView::~GraphView() {
  model_->RemoveObserver(static_cast<GraphObserverUpdateInterface*>(this));
  model_->RemoveObserver(static_cast<GraphObserverErrorInterface*>(this));
  delete ui_;
}

void GraphView::UpdateGraphWindow(const QString& math_expression) {
  controller_->SetGraphExpression(math_expression);
  if (!isVisible()) {
    move(0, 0);
    show();
  }

  setWindowState(windowState() & (~Qt::WindowMinimized | Qt::WindowActive));
  raise();
  Draw();
}

void GraphView::OnUpdate() {
  UpdateInputFieldsFromModel();
  UpdateResultFromModel();
}

void GraphView::OnError(const std::pair<std::string, std::string>& error) {
  ResetResult();
  UpdateInputFieldsFromModel();

  auto error_text = QString::fromStdString(error.second);
  if (error.first == "x_graph") {
    SetXBeginError("");
    SetXEndError(error_text);
  } else if (error.first == "y_graph") {
    SetYBeginError("");
    SetYEndError(error_text);
  } else if (error.first == "graph_calculation") {
    // ничего не делаем
  } else {
    QMessageBox::critical(0, "Graph output error!", error_text);
  }
}

void GraphView::SetupButtons() {
  connect(ui_->back_button, SIGNAL(clicked()), this, SLOT(BackButtonHandle()));
  connect(ui_->draw_button, SIGNAL(clicked()), this, SLOT(DrawButtonHandle()));
  connect(ui_->default_settings_button, SIGNAL(clicked()), this,
          SLOT(DefaultSettingsButtonHandle()));
}

void GraphView::GraphPlotConfig(double begin_x, double end_x, double begin_y,
                                double end_y) {
  ui_->graph_plot->xAxis->setRange(begin_x, end_x);
  ui_->graph_plot->yAxis->setRange(begin_y, end_y);
  ui_->graph_plot->xAxis->setLabel("X");
  ui_->graph_plot->yAxis->setLabel("Y");
}

void GraphView::UpdateInputFieldsFromModel() {
  // Обновляем данные для расчета по данным модели
  double begin_x = model_->GetGraphXBegin();
  double end_x = model_->GetGraphXEnd();
  double begin_y = model_->GetGraphYBegin();
  double end_y = model_->GetGraphYEnd();

  ui_->graph_plot->clearGraphs();
  GraphPlotConfig(begin_x, end_x, begin_y, end_y);
  ui_->graph_plot->replot();

  ui_->x_min_edit->setText(view_helpers::DoubleToQString(begin_x, 7));
  ui_->x_max_edit->setText(view_helpers::DoubleToQString(end_x, 7));
  if (model_->GetGraphYScaleAuto() == true) {
    ui_->y_min_edit->setText("");
    ui_->y_max_edit->setText("");
  } else {
    ui_->y_min_edit->setText(view_helpers::DoubleToQString(begin_y, 7));
    ui_->y_max_edit->setText(view_helpers::DoubleToQString(end_y, 7));
  }
}

void GraphView::UpdateResultFromModel() {
  const std::vector<std::pair<double, double>>& points =
      model_->GetGraphPoints();

  QVector<double> x_vector, y_vector;

  for (auto& item : points) {
    if (std::isnan(item.second) || std::isinf(item.second)) {
      if (x_vector.size() > 0) {
        QCPGraph* graph = ui_->graph_plot->addGraph();
        graph->setData(x_vector, y_vector);
        ui_->graph_plot->replot();
        x_vector.clear();
        y_vector.clear();
      }
      continue;
    }

    x_vector.push_back(item.first);
    y_vector.push_back(item.second);
  }

  QCPGraph* graph = ui_->graph_plot->addGraph();
  graph->setData(x_vector, y_vector);

  ui_->graph_plot->replot();
}

void GraphView::ResetResult() {
  ui_->graph_plot->clearGraphs();
  ui_->graph_plot->replot();
}

void GraphView::ResetInputFields() {
  ui_->x_min_edit->setText(view_helpers::DoubleToQString(-100.0, 7));
  ui_->x_max_edit->setText(view_helpers::DoubleToQString(100, 7));
  ui_->y_min_edit->setText("");
  ui_->y_max_edit->setText("");
}

void GraphView::Draw() {
  ResetAllErrors();

  bool input_correct;
  double x_begin =
      ui_->x_min_edit->text().replace(",", ".").toDouble(&input_correct);

  if (!input_correct) {
    SetXBeginError("Field \"X min\" contains incorrect value!");
    return;
  }

  double x_end =
      ui_->x_max_edit->text().replace(",", ".").toDouble(&input_correct);

  if (!input_correct) {
    SetXEndError("Field \"X max\" contains incorrect value!");
    return;
  }

  double y_begin =
      ui_->y_min_edit->text().replace(",", ".").toDouble(&input_correct);

  if (ui_->y_min_edit->text().length() > 0 && !input_correct) {
    SetYBeginError("Field \"Y min\" contains incorrect value!");
    return;
  }

  double y_end =
      ui_->y_max_edit->text().replace(",", ".").toDouble(&input_correct);

  if (ui_->y_max_edit->text().length() > 0 && !input_correct) {
    SetYEndError("Field \"Y max\" contains incorrect value!");
    return;
  }

  x_begin = QString::number(x_begin, 'f', 7).toDouble();
  x_end = QString::number(x_end, 'f', 7).toDouble();
  y_begin = QString::number(y_begin, 'f', 7).toDouble();
  y_end = QString::number(y_end, 'f', 7).toDouble();

  if (y_begin == y_end) {
    controller_->SetGraphYScaleAuto(true);
  } else {
    controller_->SetGraphYScaleAuto(false);
  }

  controller_->SetGraphBeginX(x_begin);
  controller_->SetGraphEndX(x_end);
  controller_->SetGraphBeginY(y_begin);
  controller_->SetGraphEndY(y_end);

  controller_->CalculateGraph();
}

void GraphView::SetXBeginError(const QString& error_text) {
  ResetResult();
  ui_->x_min_edit->setStyleSheet("border: 1px solid red; color: red;");
  if (error_text.length() > 0) {
    QMessageBox::critical(0, "Graph output error!", error_text);
  }
}

void GraphView::SetXEndError(const QString& error_text) {
  ResetResult();
  ui_->x_max_edit->setStyleSheet("border: 1px solid red; color: red;");
  if (error_text.length() > 0) {
    QMessageBox::critical(0, "Graph output error!", error_text);
  }
}

void GraphView::SetYBeginError(const QString& error_text) {
  ResetResult();
  ui_->y_min_edit->setStyleSheet("border: 1px solid red; color: red;");
  if (error_text.length() > 0) {
    QMessageBox::critical(0, "Graph output error!", error_text);
  }
}

void GraphView::SetYEndError(const QString& error_text) {
  ResetResult();
  ui_->y_max_edit->setStyleSheet("border: 1px solid red; color: red;");
  if (error_text.length() > 0) {
    QMessageBox::critical(0, "Graph output error!", error_text);
  }
}

void GraphView::ResetXBeginError() { ui_->x_min_edit->setStyleSheet(""); }

void GraphView::ResetXEndError() { ui_->x_max_edit->setStyleSheet(""); }

void GraphView::ResetYBeginError() { ui_->y_min_edit->setStyleSheet(""); }

void GraphView::ResetYEndError() { ui_->y_max_edit->setStyleSheet(""); }

void GraphView::ResetAllErrors() {
  ResetXBeginError();
  ResetXEndError();
  ResetYBeginError();
  ResetYEndError();
}

void GraphView::BackButtonHandle() { close(); }

void GraphView::DrawButtonHandle() { Draw(); }

void GraphView::DefaultSettingsButtonHandle() {
  ResetInputFields();
  Draw();
}

}  // namespace s21
