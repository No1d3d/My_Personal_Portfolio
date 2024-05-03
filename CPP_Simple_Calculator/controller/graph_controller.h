#ifndef S21_SMART_CALC_V20_CONTROLLER_GRAPH_CONTROLLER_H_
#define S21_SMART_CALC_V20_CONTROLLER_GRAPH_CONTROLLER_H_

#include <QString>

#include "../interfaces/graph_controller_interface.h"
#include "../interfaces/graph_model_interface.h"

namespace s21 {

class GraphController final : public GraphControllerInterface {
 public:
  GraphController() = delete;
  explicit GraphController(GraphModelInterface* model);
  GraphController(const GraphController& other) = delete;
  GraphController(GraphController&& other) = delete;
  GraphController& operator=(const GraphController& other) = delete;
  GraphController& operator=(GraphController&& other) = delete;
  ~GraphController() = default;

  void SetGraphExpression(const QString& str) override;
  void SetGraphBeginX(double new_x) override;
  void SetGraphEndX(double new_x) override;
  void SetGraphBeginY(double new_y) override;
  void SetGraphEndY(double new_y) override;
  void SetGraphYScaleAuto(bool flag) override;
  void CalculateGraph() override;

 private:
  GraphModelInterface* model_;
};

}  // namespace s21

#endif  // S21_SMART_CALC_V20_CONTROLLER_GRAPH_CONTROLLER_H_
