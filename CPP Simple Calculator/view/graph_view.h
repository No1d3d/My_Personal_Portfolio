#ifndef S21_SMART_CALC_V20_VIEW_GRAPH_VIEW_H_
#define S21_SMART_CALC_V20_VIEW_GRAPH_VIEW_H_

#include <QDialog>

#include "../interfaces/graph_controller_interface.h"
#include "../interfaces/graph_model_public_interface.h"
#include "../interfaces/observer/observer_graph_interfaces.h"

namespace Ui {
class GraphView;
}

namespace s21 {

class GraphView final : public QDialog,
                        public GraphObserverUpdateInterface,
                        public GraphObserverErrorInterface {
  Q_OBJECT

 public:
  explicit GraphView(GraphControllerInterface* controller,
                     GraphModelPublicInterface* model,
                     QWidget* parent = nullptr);
  GraphView(const GraphView& other) = delete;
  GraphView(GraphView&& other) = delete;
  GraphView& operator=(const GraphView& other) = delete;
  GraphView& operator=(GraphView&& other) = delete;
  ~GraphView();

  void UpdateGraphWindow(const QString& math_expression);
  void OnUpdate() override;
  void OnError(const std::pair<std::string, std::string>& error) override;

 private:
  void SetupButtons();
  void GraphPlotConfig(double begin_x, double end_x, double begin_y,
                       double end_y);
  void UpdateInputFieldsFromModel();
  void UpdateResultFromModel();
  void ResetResult();
  void ResetInputFields();
  void Draw();
  void SetXBeginError(const QString& error_text);
  void SetXEndError(const QString& error_text);
  void SetYBeginError(const QString& error_text);
  void SetYEndError(const QString& error_text);
  void ResetXBeginError();
  void ResetXEndError();
  void ResetYBeginError();
  void ResetYEndError();
  void ResetAllErrors();

  Ui::GraphView* ui_;
  GraphControllerInterface* controller_;
  GraphModelPublicInterface* model_;

 private slots:
  void BackButtonHandle();
  void DrawButtonHandle();
  void DefaultSettingsButtonHandle();
};

}  // namespace s21

#endif  // S21_SMART_CALC_V20_VIEW_GRAPH_VIEW_H_
